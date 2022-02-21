#include "library.h"

#include <iostream>
#include <memory>

#include "Assembler/Assembler.h"

#include "MemoryIR/IRContext.h"
#include "MemoryIR/IRbuilder.h"
#include "MemoryIR/Module.h"
#include "RegisterAllocation/InterferenceGraph.h"
#include "RegisterAllocation/LivenessAnalyzer.h"
#include "CodeGen/Targets/MipsCodegenTarget.h"
#include "CodeGen/Targets/MipsIRTargetGen.h"

int main() {
    using namespace mipsir;

    auto ctx = std::make_unique<IRContext>();
    auto builder = std::make_unique<IRBuilder>(ctx.get());
    auto module = std::make_unique<Module>(ctx.get());
    const std::vector<std::string> args{"a", "b"};
    Function *function = module->createFunction("add", args);

    const std::vector<std::string> argsMultiply{"x1", "x2"};
    Function *callee = module->createFunction("multiply", argsMultiply);
    Block *calleBlock = ctx->createBlock(callee);
    builder->setInsertPoint(calleBlock);
    builder->createReturn(builder->createMulInstr(callee->getArgs()[0], callee->getArgs()[1]));

    Block *entryBlock = ctx->createBlock(function);
    builder->setInsertPoint(entryBlock);
    Value *a = function->getArgs()[0];
    Value *b = function->getArgs()[1];
    Value *c = builder->createCallInstr(callee, {a, b});
    builder->createReturn(c);
    module->print(std::cout);

    assembler::Assembler assembler;
    auto cgIRTarget = std::make_unique<MipsIRTargetGen>(&assembler);
    auto cgTarget = std::make_unique<MipsCodegenTarget>(cgIRTarget.get(), &assembler);

    cgTarget->generateAssembly(*module);
    std::cout << "========== Assembler Output ==========" << std::endl;
    assembler.print(std::cout);

    return 0;
}
