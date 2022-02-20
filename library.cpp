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

    const std::vector<std::string> args{"a", "b"};
    Function *function = module->createFunction("add", args);
    Block *entryBlock = ctx->createBlock(function);
    builder->setInsertPoint(entryBlock);

    Value *temp1 = builder->createAddInstr(function->getArgs()[1], function->getArgs()[0]);
    Value *temp2 = builder->createMulInstr(function->getArgs()[0], function->getArgs()[1]);
    Value *val = ctx->createConstantInt(10);
    builder->createAddInstr(temp1, val);

    function->print(std::cout);

    return 0;
}
