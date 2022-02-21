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
 *  2, 3            - function return values (prefers 3)
 *  4-7             - function parameters
 *  1, 8-15, 24, 25 - unsaved temporary (prefers 8-15)
 *  16-23           - saved temporary
 *  26-29           - reserved for os
 *  30              - stack pointer
 *  31              - return address
 *
 * Calling Convention
 *  - callee clean up, saves ret val on top stack, reverse push order
 *      param_n
 *      .......
 *      param_0
 *      retval
 *  ---stack top---
 */

void MipsIRTargetGen::emitCallInstruction(CallInstruction *instr,
                                          const VRegisterAssignment &va,
                                          const SpillStackAssignment &sa,
                                          const SymbolTable &st) {
    size_t stackOffset = (instr->getFunctionArguments().size() + 1) * 4;
    m_assembler->emitAddi(30, 30, -((int)stackOffset));
    int currOffset = 4 - (int)stackOffset;
    for (auto arg: instr->getFunctionArguments()) {
        m_assembler->emitSw(30, va.at(arg), currOffset);
        currOffset += 4;
    }
    m_assembler->emitSw(30, 31, 0);
    std::string funcCall = "func_" + instr->getCalleName();
    m_assembler->emitJal(funcCall);
    m_assembler->emitAddi(va.at(instr), 3, 0);
    m_assembler->emitLw(30, 31, 0);

    m_assembler->emitAddi(30, 30, (int)stackOffset);
}
void MipsIRTargetGen::emitBranchUnconditional(BranchUnconditional *instr,
                                              const VRegisterAssignment &va,
                                              const SpillStackAssignment &sa,
                                              const SymbolTable &st) {
    m_assembler->emitBeq(0, 0, st.at(instr->getOutbound()[0]));
}

void MipsIRTargetGen::emitBranchConditional(BranchConditional *instr,
                                            const VRegisterAssignment &va,
                                            const SpillStackAssignment &sa,
                                            const SymbolTable &st) {
    auto cond = instr->getOperands()[0];
    auto branches = instr->getOutbound();
    m_assembler->emitBne(va.at(cond), 0, st.at(branches[0]));
    m_assembler->emitBeq(0, 0, st.at(branches[1]));
}

void MipsIRTargetGen::emitStoreInstruction(StoreInstruction *instr,
                                           const VRegisterAssignment &va,
                                           const SpillStackAssignment &sa,
                                           const SymbolTable &st) {
    auto operands = instr->getOperands();
    m_assembler->emitSw(va.at(operands[1]), va.at(operands[0]), 0);
}
void MipsIRTargetGen::emitReturnInstruction(ReturnInstruction *instr,
                                            const VRegisterAssignment &assignment,
                                            const SpillStackAssignment &stackAssignment,
                                            const SymbolTable &table) {
    m_assembler->emitJr(31);
}

void MipsIRTargetGen::emitValuedReturnInstruction(ValuedReturnInstruction *instr,
                                                  const VRegisterAssignment &va,
                                                  const SpillStackAssignment &sa,
                                                  const SymbolTable &st) {
    auto retValue = instr->getOperands()[0];
    m_assembler->emitAdd(3, 0, va.at(retValue));
    m_assembler->emitJr(31);
}

void MipsIRTargetGen::emitLoadInstruction(LoadInstruction *instr,
                                          const VRegisterAssignment &va,
                                          const SpillStackAssignment &sa,
                                          const SymbolTable &st) {
    auto operands = instr->getOperands();
    m_assembler->emitLw(va.at(instr), va.at(operands[0]), 0);
}

void MipsIRTargetGen::emitAddInstruction(AddInstruction *instr,
                                         const VRegisterAssignment &va,
                                         const SpillStackAssignment &sa,
                                         const SymbolTable &st) {
    auto operands = instr->getOperands();
    auto lhs = dynamic_cast<IntegerConstant *>(operands[0]);
    auto rhs = dynamic_cast<IntegerConstant *>(operands[1]);
    if (lhs && rhs) {
        m_assembler->emitAddi(va.at(instr), 0, lhs->getValue() + rhs->getValue());
    } else if (lhs) {
        m_assembler->emitAddi(va.at(instr), va.at(operands[1]), lhs->getValue());
    } else if (rhs) {
        m_assembler->emitAddi(va.at(instr), va.at(operands[0]), rhs->getValue());
    } else {
        m_assembler->emitAdd(va.at(instr), va.at(operands[0]), va.at(operands[1]));
    }
}

void MipsIRTargetGen::emitSubInstruction(SubInstruction *instr,
                                         const VRegisterAssignment &va,
                                         const SpillStackAssignment &sa,
                                         const SymbolTable &st) {
    auto operands = instr->getOperands();
    auto lhs = dynamic_cast<IntegerConstant *>(operands[0]);
    auto rhs = dynamic_cast<IntegerConstant *>(operands[1]);
    if (lhs && rhs) {
        m_assembler->emitAddi(va.at(instr), 0, lhs->getValue() - rhs->getValue());
    } else if (lhs) {
        m_assembler->emitSub(va.at(instr), 0, va.at(operands[1]));
        m_assembler->emitAddi(va.at(instr), va.at(instr), lhs->getValue());
    } else if (rhs) {
        m_assembler->emitAddi(va.at(instr), va.at(operands[0]), -rhs->getValue());
    } else {
        m_assembler->emitSub(va.at(instr), va.at(operands[0]), va.at(operands[1]));
    }
}

void MipsIRTargetGen::emitMulInstruction(MulInstruction *instr,
                                         const VRegisterAssignment &va,
                                         const SpillStackAssignment &sa,
                                         const SymbolTable &st) {
    auto operands = instr->getOperands();
    m_assembler->emitMult(va.at(operands[0]), va.at(operands[1]));
    m_assembler->emitMflo(va.at(instr));
}

void MipsIRTargetGen::emitDivInstruction(DivInstruction *instr,
                                         const VRegisterAssignment &va,
                                         const SpillStackAssignment &sa,
                                         const SymbolTable &st) {
    auto operands = instr->getOperands();
    m_assembler->emitDiv(va.at(operands[0]), va.at(operands[1]));
    m_assembler->emitMflo(va.at(instr));
}

void MipsIRTargetGen::emitCmpInstruction(CmpInstruction *instr,
                                         const VRegisterAssignment &va,
                                         const SpillStackAssignment &sa,
                                         const SymbolTable &st) {
    auto operands = instr->getOperands();
    switch (instr->getOperator()) {
        case CmpInstruction::CmpOp::Equal: {
            m_assembler->emitSub(va.at(instr), va.at(operands[0]), va.at(operands[1]));
            m_assembler->emitBeq(va.at(instr), 0, 2);
            m_assembler->emitAddi(va.at(instr), 0, 0);
            m_assembler->emitBeq(0, 0, 1);
            m_assembler->emitAddi(va.at(instr), 0, 1);
            break;
        }
        case CmpInstruction::CmpOp::NotEqual: {
            m_assembler->emitSub(va.at(instr), va.at(operands[0]), va.at(operands[1]));
            m_assembler->emitBeq(va.at(instr), 0, 2);
            m_assembler->emitAddi(va.at(instr), 0, 1);
            m_assembler->emitBeq(0, 0, 1);
            m_assembler->emitAddi(va.at(instr), 0, 0);
            break;
        }
        case CmpInstruction::CmpOp::LessThan: {
            m_assembler->emitSlt(va.at(instr), va.at(operands[0]), va.at(operands[1]));
            break;
        }
        case CmpInstruction::CmpOp::GreaterThan: {
            m_assembler->emitSlt(va.at(instr), va.at(operands[1]), va.at(operands[0]));
            break;
        }
        case CmpInstruction::CmpOp::LessThanEqual: {
            m_assembler->emitAddi(va.at(instr), va.at(operands[1]), 1);
            m_assembler->emitSlt(va.at(instr), va.at(operands[0]), va.at(instr));
            break;
        }
        case CmpInstruction::CmpOp::GreaterThanEqual: {
            m_assembler->emitAddi(va.at(instr), va.at(operands[0]), 1);
            m_assembler->emitSlt(va.at(instr), va.at(operands[1]), va.at(instr));
            break;
        }
    }
}
}
