//
// Created by henry on 2022-02-20.
//

#ifndef MIPS_IR_CODEGEN_TARGETS_MIPSIRTARGETGEN_H_
#define MIPS_IR_CODEGEN_TARGETS_MIPSIRTARGETGEN_H_

#include "../IRTargetGen.h"

namespace assembler {
class Assembler;
}

namespace mipsir {

class MipsIRTargetGen : public IRTargetGen {
    assembler::Assembler *m_assembler;
  public:
    explicit MipsIRTargetGen(assembler::Assembler *assembler) : m_assembler(assembler) {}

    void emitCallInstruction(CallInstruction *instr,
                             const VRegisterAssignment &assignment,
                             const SpillStackAssignment &stackAssignment,
                             const SymbolTable &table) override;
    void emitBranchUnconditional(BranchUnconditional *instr,
                                 const VRegisterAssignment &assignment,
                                 const SpillStackAssignment &stackAssignment,
                                 const SymbolTable &table) override;
    void emitBranchConditional(BranchConditional *instr,
                               const VRegisterAssignment &assignment,
                               const SpillStackAssignment &stackAssignment,
                               const SymbolTable &table) override;
    void emitStoreInstruction(StoreInstruction *instr,
                              const VRegisterAssignment &assignment,
                              const SpillStackAssignment &stackAssignment,
                              const SymbolTable &table) override;
    void emitReturnInstruction(ReturnInstruction *instr,
                               const VRegisterAssignment &assignment,
                               const SpillStackAssignment &stackAssignment,
                               const SymbolTable &table) override;
    void emitValuedReturnInstruction(ValuedReturnInstruction *instr,
                                     const VRegisterAssignment &assignment,
                                     const SpillStackAssignment &stackAssignment,
                                     const SymbolTable &table) override;
    void emitLoadInstruction(LoadInstruction *instr,
                             const VRegisterAssignment &assignment,
                             const SpillStackAssignment &stackAssignment,
                             const SymbolTable &table) override;
    void emitAddInstruction(AddInstruction *instr,
                            const VRegisterAssignment &assignment,
                            const SpillStackAssignment &stackAssignment,
                            const SymbolTable &table) override;
    void emitSubInstruction(SubInstruction *instr,
                            const VRegisterAssignment &assignment,
                            const SpillStackAssignment &stackAssignment,
                            const SymbolTable &table) override;
    void emitMulInstruction(MulInstruction *instr,
                            const VRegisterAssignment &assignment,
                            const SpillStackAssignment &stackAssignment,
                            const SymbolTable &table) override;
    void emitDivInstruction(DivInstruction *instr,
                            const VRegisterAssignment &assignment,
                            const SpillStackAssignment &stackAssignment,
                            const SymbolTable &table) override;
    void emitCmpInstruction(CmpInstruction *instr,
                            const VRegisterAssignment &assignment,
                            const SpillStackAssignment &stackAssignment,
                            const SymbolTable &table) override;
};

}

#endif //MIPS_IR_CODEGEN_TARGETS_MIPSIRTARGETGEN_H_
