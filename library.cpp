#include "library.h"

#include <iostream>
#include <memory>

#include "MemoryIR/IRContext.h"
#include "MemoryIR/IRbuilder.h"
#include "MemoryIR/Module.h"

int main() {
    using namespace mipsir;

    auto ctx = std::make_unique<IRContext>();
    auto builder = std::make_unique<IRBuilder>(ctx.get());
    auto module = std::make_unique<Module>(ctx.get());

    Function *callee = module->createFunction("random_function", {}, true);

    const std::vector<std::string> args{"a", "b"};
    Function *function = module->createFunction("add", args);
    Block *entryBlock = ctx->createBlock(function);
    Block *exitBlock = ctx->createBlock(function);

    builder->setInsertPoint(entryBlock);
    Value *temp1 = function->getArgs()[0];
    Value *temp2 = function->getArgs()[1];
    builder->createCallInstr(callee, {temp1, temp2});
    builder->createCmpInstruction(CmpInstruction::CmpOp::Equal, temp1, temp2);

    builder->createBranch(exitBlock);

    builder->setInsertPoint(exitBlock);
    builder->createReturn(builder->createAddInstr(temp1, temp2));

    function->print(std::cout);

    return 0;
}
