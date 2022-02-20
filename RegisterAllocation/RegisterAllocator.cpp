//
// Created by henry on 2022-02-20.
//

#include "RegisterAllocator.h"

#include "../MemoryIR/Function.h"
#include "LivenessAnalyzer.h"

#include <unordered_set>

namespace mipsir {

class Value;

void RegisterAllocator::assignRegister() {
    InterferenceGraph rig = LivenessAnalyzer::constructRegisterInterferenceGraph(m_function);
    rig.color();
    auto coloring = rig.getColoring();
    std::unordered_set<uint32_t> used;
    for (const auto&[reg, color]: coloring) {
        used.insert(color);
    }
    if (used.size() <= m_targetRegisterCount) { // check if k-colorable
        std::unordered_map<Value *, MachineRegister> valueMap;
        auto vAssignment = LivenessAnalyzer::getVirtualRegisterAssignment(m_function);
        for (const auto &[reg, vRegId]: vAssignment) {
            valueMap[reg] = m_machineRegisterMapping[coloring[vRegId] - 1];
        }
        m_registerAssignment = valueMap;
    } else {
        throw std::runtime_error("unimplemented: spills to stack!");
    }
}

void RegisterAllocator::debugAssignment(std::ostream &ostream) {
    ostream << "Register Assignment: not implemented yet!" << std::endl;
}

}
