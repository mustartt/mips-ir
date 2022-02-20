//
// Created by henry on 2022-02-20.
//

#include <iostream>
#include <numeric>

#include "LivenessAnalyzer.h"

#include "../MemoryIR/Function.h"
#include "../MemoryIR/Instruction.h"
#include "../MemoryIR/Block.h"

namespace mipsir {

std::unordered_map<Value *, std::pair<LivenessAnalyzer::Line, LivenessAnalyzer::Line>>
mergeLiveRanges(const std::unordered_map<Value *, LivenessAnalyzer::Line> &firstAlive,
                const std::unordered_map<Value *, LivenessAnalyzer::Line> &lastAlive) {
    std::unordered_map<Value *, std::pair<LivenessAnalyzer::Line, LivenessAnalyzer::Line>> merged;
    for (auto &[value, line]: firstAlive) {
        if (lastAlive.count(value) && line <= lastAlive.at(value)) {
            merged[value] = std::make_pair(line, lastAlive.at(value));
        }
    }
    return merged;
}

std::unordered_map<Value *, std::pair<LivenessAnalyzer::Line, LivenessAnalyzer::Line>>
LivenessAnalyzer::analyzeMergedLiveRange(Function *function) {
    const auto blocks = function->getFunctionBlocks();
    std::vector<Instruction *> instrList;
    for (const auto &block: blocks) {
        instrList.insert(instrList.end(), block->getInstructions().begin(), block->getInstructions().end());
    }
    Line line = 0;
    std::unordered_map<Value *, Line> firstAlive;
    std::unordered_map<Value *, Line> lastAlive;

    for (auto &arg: function->getArgs()) {
        firstAlive[arg] = line;
    }
    for (auto &instr: instrList) {
        ++line;
        if (instr->hasReturnValue() && !firstAlive.count(instr))
            firstAlive[instr] = line;
    }
    line = instrList.size();
    for (auto i = instrList.rbegin(); i != instrList.rend(); ++i) {
        for (const auto operand: (*i)->getOperands()) {
            if (!lastAlive.count(operand)) {
                lastAlive[operand] = line;
            }
        }
        --line;
    }
    return mergeLiveRanges(firstAlive, lastAlive);
}

std::unordered_map<Value *, LivenessAnalyzer::Register>
LivenessAnalyzer::getVirtualRegisterAssignment(Function *function) {
    std::unordered_map<Value *, Register> virtualAssignment;
    Register nextAvailable = 1;
    for (const auto &arg: function->getArgs()) {
        virtualAssignment[arg] = nextAvailable++;
    }
    for (const auto &block: function->getFunctionBlocks()) {
        for (const auto &instr: block->getInstructions()) {
            if (instr->hasReturnValue()) virtualAssignment[instr] = nextAvailable++;
        }
    }
    return virtualAssignment;
}

InterferenceGraph LivenessAnalyzer::constructRegisterInterferenceGraph(Function *function) {
    InterferenceGraph rig;
    auto virtualAssignment = getVirtualRegisterAssignment(function);
    auto mergedLiveRanges = analyzeMergedLiveRange(function);
    auto blocks = function->getFunctionBlocks();
    Line lineCount = std::accumulate(blocks.begin(), blocks.end(), 0, [](int sum, Block *block) {
      return sum + block->getInstructions().size();
    });
    for (Line line = 1; line <= lineCount; ++line) {
        std::vector<Value *> live;
        for (const auto &[reg, range]: mergedLiveRanges) {
            if (range.first <= line && line <= range.second) {
                live.push_back(reg);
            }
        }
        for (auto from: live) {
            for (auto to: live) {
                if (to == from) continue;
                rig.addInterference(virtualAssignment[from], virtualAssignment[to]);
            }
        }
    }
    return rig;
}

}

