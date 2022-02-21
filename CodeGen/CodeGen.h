//
// Created by henry on 2022-02-20.
//

#ifndef MIPS_IR_CODEGEN_CODEGEN_H_
#define MIPS_IR_CODEGEN_CODEGEN_H_

namespace mipsir {

class Module;
class IRTargetGen;

class CodeGenerator {
  protected:
    IRTargetGen *m_targetGen;
  public:
    explicit CodeGenerator(IRTargetGen *targetGen) : m_targetGen(targetGen) {}
    virtual ~CodeGenerator() = default;
    virtual void generateAssembly(const Module &module) = 0;
};

}

#endif //MIPS_IR_CODEGEN_CODEGEN_H_
