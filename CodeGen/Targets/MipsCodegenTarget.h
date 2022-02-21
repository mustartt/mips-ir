//
// Created by henry on 2022-02-20.
//

#ifndef MIPS_IR_CODEGEN_MIPSCODEGENTARGET_H_
#define MIPS_IR_CODEGEN_MIPSCODEGENTARGET_H_

#include "CodeGen.h"
#include "../../MemoryIR/Module.h"

namespace assembler {
class Assembler;
}

namespace mipsir {

class MipsCodegenTarget : public CodeGenerator {
    assembler::Assembler *m_assembler;
  public:
    friend class Module;
    explicit MipsCodegenTarget(IRTargetGen *targetGen, assembler::Assembler *assembler)
        : CodeGenerator(targetGen), m_assembler(assembler) {}
    void generateAssembly(const Module &module) override;
  private:
    void emitGlobal(GlobalVariable *globalVariable);
    void emitFunction(Function *function);
};

}

#endif //MIPS_IR_CODEGEN_MIPSCODEGENTARGET_H_
