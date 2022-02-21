#include "library.h"

#include <iostream>
#include <memory>
#include <fstream>

#include "Assembler/Assembler.h"

#include "MemoryIR/IRContext.h"
#include "MemoryIR/IRbuilder.h"
#include "MemoryIR/Module.h"
#include "RegisterAllocation/InterferenceGraph.h"
#include "RegisterAllocation/LivenessAnalyzer.h"
#include "CodeGen/Targets/MipsCodegenTarget.h"
#include "CodeGen/Targets/MipsIRTargetGen.h"

void generateEntryPoint(assembler::Assembler &assembler) {
    assembler.insertLabel("entry");
    assembler.emitAddi(30, 30, -8);
    assembler.emitSw(30, 1, -4);
    assembler.emitSw(30, 31, 0);
    assembler.emitJal("func_fibonacci");
    assembler.emitLw(30, 31, 0);
    assembler.emitAddi(30, 30, 8);
    assembler.emitJr(31);
}

int main() {
    using namespace mipsir;

    auto ctx = std::make_unique<IRContext>();
    auto builder = std::make_unique<IRBuilder>(ctx.get());
    auto module = std::make_unique<Module>(ctx.get());
    const std::vector<std::string> args{"n"};
    Function *function = module->createFunction("fibonacci", args);
    Block *entry = ctx->createBlock(function);
    Block *baseCase = ctx->createBlock(function);
    Block *recursiveCase = ctx->createBlock(function);
    builder->setInsertPoint(entry);

    Value *num0 = ctx->createConstantInt(0);
    Value *num1 = ctx->createConstantInt(1);
    Value *num2 = ctx->createConstantInt(2);
    Value *cmp = builder->createCmpInstruction(
        CmpInstruction::CmpOp::LessThanEqual, function->getArgs()[0],
        builder->createAddInstr(num0, num1));
    builder->createBranch(cmp, baseCase, recursiveCase);

    builder->setInsertPoint(baseCase);
    builder->createReturn(function->getArgs()[0]);

    builder->setInsertPoint(recursiveCase);

    Value *leftCase = builder->createSubInstr(function->getArgs()[0], num1);
    Value *rightCase = builder->createSubInstr(function->getArgs()[0], num2);

    builder->createReturn(builder->createAddInstr(
        builder->createCallInstr(function, {leftCase}),
        builder->createCallInstr(function, {rightCase})
    ));

    module->print(std::cout);

    assembler::Assembler assembler;
    generateEntryPoint(assembler);
    auto cgIRTarget = std::make_unique<MipsIRTargetGen>(&assembler);
    auto cgTarget = std::make_unique<MipsCodegenTarget>(cgIRTarget.get(), &assembler);

    cgTarget->generateAssembly(*module);
    std::cout << "========== Assembler Output ==========" << std::endl;
    assembler.print(std::cout);

    std::ofstream file{"output.mips"};
    assembler.emit(file);

    return 0;
}
