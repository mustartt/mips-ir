//
// Created by henry on 2022-02-20.
//

#ifndef MIPS_IR_CODEGEN_IRTARGETGEN_H_
#define MIPS_IR_CODEGEN_IRTARGETGEN_H_

#include "../RegisterAllocation/RegisterAllocator.h"

namespace mipsir {

class Instruction;
class CallInstruction;
class BranchUnconditional;
class BranchConditional;
class StoreInstruction;
class ReturnInstruction;
class ValuedReturnInstruction;
class LoadInstruction;
class AddInstruction;
class SubInstruction;
class MulInstruction;
class DivInstruction;
class CmpInstruction;
class Block;

using SymbolTable = std::unordered_map<Block *, std::string>;

class IRTargetGen {
  public:
    virtual ~IRTargetGen() = default;
    void emitTargetInstruction(Instruction *instruction,
                               const VRegisterAssignment &,
                               const SpillStackAssignment &,
                               const SymbolTable &);
  private:
    virtual void emitCallInstruction(CallInstruction *instr,
                                     const VRegisterAssignment &,
                                     const SpillStackAssignment &,
                                     const SymbolTable &) = 0;
    virtual void emitBranchUnconditional(BranchUnconditional *instr,
                                         const VRegisterAssignment &,
                                         const SpillStackAssignment &,
                                         const SymbolTable &) = 0;
    virtual void emitBranchConditional(BranchConditional *instr,
                                       const VRegisterAssignment &,
                                       const SpillStackAssignment &,
                                       const SymbolTable &) = 0;
    virtual void emitStoreInstruction(StoreInstruction *instr,
                                      const VRegisterAssignment &,
                                      const SpillStackAssignment &,
                                      const SymbolTable &) = 0;
    virtual void emitReturnInstruction(ReturnInstruction *instr,
                                       const VRegisterAssignment &,
                                       const SpillStackAssignment &,
                                       const SymbolTable &) = 0;
    virtual void emitValuedReturnInstruction(ValuedReturnInstruction *instr,
                                             const VRegisterAssignment &,
                                             const SpillStackAssignment &,
                                             const SymbolTable &) = 0;
    virtual void emitLoadInstruction(LoadInstruction *instr,
                                     const VRegisterAssignment &,
                                     const SpillStackAssignment &,
                                     const SymbolTable &) = 0;
    virtual void emitAddInstruction(AddInstruction *instr,
                                    const VRegisterAssignment &,
                                    const SpillStackAssignment &,
                                    const SymbolTable &) = 0;
    virtual void emitSubInstruction(SubInstruction *instr,
                                    const VRegisterAssignment &,
                                    const SpillStackAssignment &,
                                    const SymbolTable &) = 0;
    virtual void emitMulInstruction(MulInstruction *instr,
                                    const VRegisterAssignment &,
                                    const SpillStackAssignment &,
                                    const SymbolTable &) = 0;
    virtual void emitDivInstruction(DivInstruction *instr,
                                    const VRegisterAssignment &,
                                    const SpillStackAssignment &,
                                    const SymbolTable &) = 0;
    virtual void emitCmpInstruction(CmpInstruction *instr,
                                    const VRegisterAssignment &,
                                    const SpillStackAssignment &,
                                    const SymbolTable &) = 0;
};

}

#endif //MIPS_IR_CODEGEN_IRTARGETGEN_H_
