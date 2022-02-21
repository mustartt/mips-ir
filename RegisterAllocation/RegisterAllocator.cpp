//
// Created by henry on 2022-02-20.
//

#include "RegisterAllocator.h"
#include <unordered_set>

namespace mipsir {

RegisterAllocator::RegisterAllocator(Function *function, size_t machineRegisterCount)
    : m_function(function) {
    for (MachineRegister reg = 0; reg < machineRegisterCount; ++reg) {
        m_machineRegisterMapping.push_back(reg);
    }
}

RegisterAllocator::RegisterAllocator(Function *function, std::vector<MachineRegister> machineRegisterMapping)
    : m_function(function),
      m_machineRegisterMapping(std::move(machineRegisterMapping)) {}

void RegisterAllocator::debugAssignment(std::ostream &ostream) {
    ostream << "========== Register Assignment Output ==========" << std::endl;
    auto assignment = LivenessAnalyzer::getVirtualRegisterAssignment(m_function);
    for (auto &[reg, regID]: assignment) {
        if (m_registerAssignment.count(reg)) {
            ostream << " %" << regID << " := $" << m_registerAssignment.at(reg) << std::endl;
        } else {
            ostream << " %" << regID << " := stack(" << m_registerSpill.at(reg) << ")" << std::endl;
        }
    }
}

void RegisterAllocator::assignRegister() {
    InterferenceGraph rig = LivenessAnalyzer::constructRegisterInterferenceGraph(m_function);
    rig.color();
    auto coloring = rig.getColoring();
    std::unordered_set<uint32_t> used;
    for (const auto&[reg, color]: coloring) {
        used.insert(color);
    }
    if (used.size() <= m_machineRegisterMapping.size()) { // check if k-colorable
        std::unordered_map<Value *, MachineRegister> valueMap;
        auto vAssignment = LivenessAnalyzer::getVirtualRegisterAssignment(m_function);
        for (const auto &[reg, vRegId]: vAssignment) {
            auto machineRegisterIndex = coloring[vRegId] - 1;
            valueMap[reg] = m_machineRegisterMapping[machineRegisterIndex];
        }
        m_registerAssignment = valueMap;
    } else {
        throw std::runtime_error("unimplemented: spills to stack!");
    }
}

}
