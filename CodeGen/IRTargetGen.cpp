//
// Created by henry on 2022-02-20.
//

#include "IRTargetGen.h"

#include "../MemoryIR/Instruction.h"

namespace mipsir {

void IRTargetGen::emitTargetInstruction(Instruction *instruction,
                                        const VRegisterAssignment &va,
                                        const SpillStackAssignment &sa,
                                        const SymbolTable &st) {
    auto ptrCallInstruction = dynamic_cast<CallInstruction *>(instruction);
    if (ptrCallInstruction) {
        emitCallInstruction(ptrCallInstruction, va, sa, st);
        return;
    }
    auto ptrBranchUnconditional = dynamic_cast<BranchUnconditional *>(instruction);
    if (ptrBranchUnconditional) {
        emitBranchUnconditional(ptrBranchUnconditional, va, sa, st);
        return;
    }
    auto ptrBranchConditional = dynamic_cast<BranchConditional *>(instruction);
    if (ptrBranchConditional) {
        emitBranchConditional(ptrBranchConditional, va, sa, st);
        return;
    }
    auto ptrStoreInstruction = dynamic_cast<StoreInstruction *>(instruction);
    if (ptrStoreInstruction) {
        emitStoreInstruction(ptrStoreInstruction, va, sa, st);
        return;
    }
    auto ptrValuedReturnInstruction = dynamic_cast<ValuedReturnInstruction *>(instruction);
    if (ptrValuedReturnInstruction) {
        emitValuedReturnInstruction(ptrValuedReturnInstruction, va, sa, st);
        return;
    }
    auto ptrReturnInstruction = dynamic_cast<ReturnInstruction *>(instruction);
    if (ptrReturnInstruction) {
        emitReturnInstruction(ptrReturnInstruction, va, sa, st);
        return;
    }
    auto ptrLoadInstruction = dynamic_cast<LoadInstruction *>(instruction);
    if (ptrLoadInstruction) {
        emitLoadInstruction(ptrLoadInstruction, va, sa, st);
        return;
    }
    auto ptrAddInstruction = dynamic_cast<AddInstruction *>(instruction);
    if (ptrAddInstruction) {
        emitAddInstruction(ptrAddInstruction, va, sa, st);
        return;
    }
    auto ptrSubInstruction = dynamic_cast<SubInstruction *>(instruction);
    if (ptrSubInstruction) {
        emitSubInstruction(ptrSubInstruction, va, sa, st);
        return;
    }
    auto ptrMulInstruction = dynamic_cast<MulInstruction *>(instruction);
    if (ptrMulInstruction) {
        emitMulInstruction(ptrMulInstruction, va, sa, st);
        return;
    }
    auto ptrDivInstruction = dynamic_cast<DivInstruction *>(instruction);
    if (ptrDivInstruction) {
        emitDivInstruction(ptrDivInstruction, va, sa, st);
        return;
    }
    auto ptrCmpInstruction = dynamic_cast<CmpInstruction *>(instruction);
    if (ptrCmpInstruction) {
        emitCmpInstruction(ptrCmpInstruction, va, sa, st);
        return;
    }
    throw std::runtime_error("unknown instruction!");
}

}
