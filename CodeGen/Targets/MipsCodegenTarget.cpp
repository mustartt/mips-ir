//
// Created by henry on 2022-02-20.
//

#include "MipsCodegenTarget.h"

#include "../../MemoryIR/Block.h"
#include "../../MemoryIR/Module.h"
#include "../../Assembler/Assembler.h"
#include "IRTargetGen.h"

#include <iostream>
#include <string>
#include <unordered_map>

namespace mipsir {

void MipsCodegenTarget::generateAssembly(const Module &module) {
    for (const auto &[name, globalVar]: module.getGlobalTable()) {

    }
    for (const auto &[name, function]: module.getFunctionTable()) {
        if (function->hasBody()) emitFunction(function);
    }
}

void MipsCodegenTarget::emitGlobal(GlobalVariable *globalVariable) {

}

void MipsCodegenTarget::emitFunction(Function *function) {
    std::string functionLabelName = "func_" + function->getName();
    m_assembler->insertLabel(functionLabelName);
    std::unordered_map<Block *, std::string> blockLabelTable;

    RegisterAllocator allocator(function, {8, 9, 10, 11, 12, 13, 14, 15, 24, 25});
    allocator.assignRegister();
    VRegisterAssignment VA = allocator.getRegisterAssignment();
    SpillStackAssignment SA = allocator.getSpillAssignment();

    MachineRegister startingParamRegister = 4;
    for (size_t i = 0; i < std::min(function->getArgs().size(), (size_t)4); ++i) {
        VA[function->getArgs()[i]] = startingParamRegister++;
    }

    RegisterAllocator::debugAssignment(function, VA, SA, std::cout); // debug

    int offset = -4;
    for (size_t i = 4; i < function->getArgs().size(); ++i) {
        m_assembler->emitLw(30, VA.at(function->getArgs()[i]), offset);
        offset -= 4;
    }

    auto bodyBlocks = function->getFunctionBlocks();
    uint32_t blockIndex = 0;
    for (auto block: bodyBlocks) { // precomputes labels
        blockLabelTable[block] = functionLabelName + "__label_" + std::to_string(blockIndex++);
    }
    for (auto block: bodyBlocks) {
        m_assembler->insertLabel(blockLabelTable.at(block));
        for (auto instr: block->getInstructions()) {
            m_targetGen->emitTargetInstruction(instr, VA, SA, blockLabelTable);
        }
    }
}

}
