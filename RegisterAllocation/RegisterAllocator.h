//
// Created by henry on 2022-02-20.
//

#ifndef MIPS_IR_REGISTERALLOCATION_REGISTERALLOCATOR_H_
#define MIPS_IR_REGISTERALLOCATION_REGISTERALLOCATOR_H_

#include "LivenessAnalyzer.h"

#include <unordered_map>
#include <vector>
#include <ostream>
#include <unordered_set>

#include "../MemoryIR/Function.h"

namespace mipsir {

class Function;
class Value;

using MachineRegister = uint32_t;
using StackOffset = uint32_t;

using VRegisterAssignment = std::unordered_map<Value *, MachineRegister>;
using SpillStackAssignment = std::unordered_map<Value *, StackOffset>;

class RegisterAllocator {
    Function *m_function;
    std::unordered_map<Value *, MachineRegister> m_registerAssignment;
    std::unordered_map<Value *, StackOffset> m_registerSpill;
    std::vector<MachineRegister> m_machineRegisterMapping;
  public:
    explicit RegisterAllocator(Function *function, size_t machineRegisterCount);
    explicit RegisterAllocator(Function *function, std::vector<MachineRegister> machineRegisterMapping);

    const VRegisterAssignment &getRegisterAssignment() { return m_registerAssignment; }
    const SpillStackAssignment &getSpillAssignment() { return m_registerSpill; }

    static void debugAssignment(Function *function,
                                VRegisterAssignment &va,
                                SpillStackAssignment &sa,
                                std::ostream &ostream);
    void assignRegister();
};

}

#endif //MIPS_IR_REGISTERALLOCATION_REGISTERALLOCATOR_H_
