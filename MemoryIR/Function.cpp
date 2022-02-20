//
// Created by henry on 2022-02-19.
//

#include <unordered_set>
#include <queue>

#include "IRContext.h"

#include "Function.h"
#include "Block.h"
#include "Instruction.h"

namespace mipsir {

Function::Function(IRContext *ctx, std::string name, const std::vector<std::string> &args, bool isVoidType)
    : m_context(ctx), m_name(std::move(name)), isVoidType(isVoidType), m_entryBlock(nullptr) {
    for (const auto &arg: args) {
        m_args.push_back(m_context->createArgument(name, arg));
    }
}

void Function::print(std::ostream &ostream) {
    ostream << "func " << m_name << "(";
    for (size_t i = 0; i < m_args.size(); ++i) {
        ostream << m_args[i]->getArgName() << ": %" << i + 1;
        if (i + 1 != m_args.size()) ostream << ", ";
    }
    if (!hasBody()) {
        ostream << ");" << std::endl;
        return;
    }

    ostream << ") {" << std::endl;
    using Register = uint32_t;
    using Label = uint32_t;

    std::unordered_map<Value *, Register> virtualAssignment;
    std::unordered_map<Block *, std::string> labelAssignment;

    Register nextAvailable = 1;
    Label nextLabel = 0;
    const auto bodyBlocks = getFunctionBlocks();
    for (const auto &arg: m_args) {
        virtualAssignment[arg] = nextAvailable++;
    }
    for (const auto &block: bodyBlocks) {
        for (const auto &instr: block->getInstructions()) {
            if (instr->hasReturnValue()) virtualAssignment[instr] = nextAvailable++;
        }
        labelAssignment[block] = "label_" + std::to_string(nextLabel++);
    }

    const auto printLiteralOrRegister = [&](const auto &operand) {
      if (virtualAssignment.count(operand)) {
          ostream << "%" << virtualAssignment[operand];
      } else {
          operand->print(ostream);
      }
      ostream << " ";
    };

    for (const auto &block: bodyBlocks) {
        ostream << "  " << labelAssignment[block] << ":" << std::endl;
        for (const auto &instr: block->getInstructions()) {
            ostream << "    ";
            if (virtualAssignment.count(instr)) {
                ostream << "%" << virtualAssignment[instr] << " = ";
            }
            instr->print(ostream);
            ostream << " ";
            const auto call = dynamic_cast<CallInstruction *>(instr);
            const auto branch = dynamic_cast<BranchInstruction *>(instr);
            if (!call) {
                for (const auto &operand: instr->getOperands()) {
                    printLiteralOrRegister(operand);
                }
            }
            if (branch) {
                for (const auto &out: branch->getOutbound()) {
                    ostream << labelAssignment[out] << " ";
                }
            }
            if (call) {
                ostream << call->getCalleName() << "( ";
                for (const auto &arg: call->getFunctionArguments()) {
                    printLiteralOrRegister(arg);
                }
                ostream << ")";
            }
            ostream << std::endl;
        }
    }
    ostream << "}" << std::endl;
}

std::vector<Block *> Function::getFunctionBlocks() const {
    if (!m_entryBlock) return {};
    std::vector<Block *> results;
    std::unordered_set<Block *> visited;
    std::queue<Block *> nextBlocks;
    visited.insert(m_entryBlock);
    nextBlocks.push(m_entryBlock);
    while (!nextBlocks.empty()) {
        auto s = nextBlocks.front();
        results.push_back(s);
        nextBlocks.pop();
        for (const auto &out: s->getOutboundingEdge()) {
            if (!visited.count(out)) {
                visited.insert(out);
                nextBlocks.push(out);
            }
        }
    }

    return results;
}

}
