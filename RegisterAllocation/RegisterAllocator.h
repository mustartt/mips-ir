//
// Created by henry on 2022-02-20.
//

#ifndef MIPS_IR_REGISTERALLOCATION_REGISTERALLOCATOR_H_
#define MIPS_IR_REGISTERALLOCATION_REGISTERALLOCATOR_H_

#include <unordered_map>
#include <vector>
#include <ostream>

namespace mipsir {

using MachineRegister = uint32_t;
using StackOffset = uint32_t;

class Function;
class Value;
class RegisterAllocator {
    Function *m_function;
    std::unordered_map<Value *, MachineRegister> m_registerAssignment;
    std::unordered_map<Value *, StackOffset> m_registerSpill;
    std::vector<MachineRegister> m_machineRegisterMapping;
    size_t m_targetRegisterCount;
  public:
    explicit RegisterAllocator(Function *function, size_t machineRegisterCount)
        : m_function(function),
          m_targetRegisterCount(machineRegisterCount) {
        for (MachineRegister reg = 0; reg < machineRegisterCount; ++reg) {
            m_machineRegisterMapping.push_back(reg);
        }
    }
    explicit RegisterAllocator(Function *function, std::vector<MachineRegister> machineRegisterMapping)
        : m_function(function),
          m_targetRegisterCount(machineRegisterMapping.size()),
          m_machineRegisterMapping(std::move(machineRegisterMapping)) {}

    const std::unordered_map<Value *, MachineRegister> &getRegisterAssignment() { return m_registerAssignment; }
    const std::unordered_map<Value *, StackOffset> &getSpillAssignment() { return m_registerSpill; }

    void debugAssignment(std::ostream &ostream);
  private:
    void assignRegister();
};

}

#endif //MIPS_IR_REGISTERALLOCATION_REGISTERALLOCATOR_H_
