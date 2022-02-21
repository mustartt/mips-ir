//
// Created by henry on 2022-02-20.
//

#include "MipsIRTargetGen.h"
#include "../../MemoryIR/Constant.h"
#include "../../MemoryIR/Instruction.h"
#include "../../Assembler/Assembler.h"

namespace mipsir {

/**
 * MIPS - Register Conventions
 *  2, 3            - function return values
 *  4-7             - function parameters
 *  1, 8-15, 24, 25 - unsaved temporary
 *  16-23           - saved temporary
 *  26-29           - reserved for os
 *  30              - stack pointer
 *  31              - return address
 */

void MipsIRTargetGen::emitCallInstruction(CallInstruction *instr,
                                          const VRegisterAssignment &assignment,
                                          const SpillStackAssignment &stackAssignment,
                                          const SymbolTable &table) {

}
void MipsIRTargetGen::emitBranchUnconditional(BranchUnconditional *instr,
                                              const VRegisterAssignment &assignment,
                                              const SpillStackAssignment &stackAssignment,
                                              const SymbolTable &table) {

}
void MipsIRTargetGen::emitBranchConditional(BranchConditional *instr,
                                            const VRegisterAssignment &assignment,
                                            const SpillStackAssignment &stackAssignment,
                                            const SymbolTable &table) {

}
void MipsIRTargetGen::emitStoreInstruction(StoreInstruction *instr,
                                           const VRegisterAssignment &assignment,
                                           const SpillStackAssignment &stackAssignment,
                                           const SymbolTable &table) {

}
void MipsIRTargetGen::emitReturnInstruction(ReturnInstruction *instr,
                                            const VRegisterAssignment &assignment,
                                            const SpillStackAssignment &stackAssignment,
                                            const SymbolTable &table) {

}
void MipsIRTargetGen::emitValuedReturnInstruction(ValuedReturnInstruction *instr,
                                                  const VRegisterAssignment &assignment,
                                                  const SpillStackAssignment &stackAssignment,
                                                  const SymbolTable &table) {

}
void MipsIRTargetGen::emitLoadInstruction(LoadInstruction *instr,
                                          const VRegisterAssignment &assignment,
                                          const SpillStackAssignment &stackAssignment,
                                          const SymbolTable &table) {

}

void MipsIRTargetGen::emitAddInstruction(AddInstruction *instr,
                                         const VRegisterAssignment &va,
                                         const SpillStackAssignment &sa,
                                         const SymbolTable &st) {
    auto operands = instr->getOperands();
    auto *lhs = dynamic_cast<Constant *>(operands[0]);
    auto *rhs = dynamic_cast<Constant *>(operands[1]);
    if (lhs || rhs) {
        throw std::runtime_error("emit addi");
    } else {
        m_assembler->emitAdd(va.at(instr), va.at(operands[0]), va.at(operands[1]));
    }
}

void MipsIRTargetGen::emitSubInstruction(SubInstruction *instr,
                                         const VRegisterAssignment &assignment,
                                         const SpillStackAssignment &stackAssignment,
                                         const SymbolTable &table) {

}
void MipsIRTargetGen::emitMulInstruction(MulInstruction *instr,
                                         const VRegisterAssignment &assignment,
                                         const SpillStackAssignment &stackAssignment,
                                         const SymbolTable &table) {

}
void MipsIRTargetGen::emitDivInstruction(DivInstruction *instr,
                                         const VRegisterAssignment &assignment,
                                         const SpillStackAssignment &stackAssignment,
                                         const SymbolTable &table) {

}
void MipsIRTargetGen::emitCmpInstruction(CmpInstruction *instr,
                                         const VRegisterAssignment &assignment,
                                         const SpillStackAssignment &stackAssignment,
                                         const SymbolTable &table) {

}
}
