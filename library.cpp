#include "library.h"

#include <iostream>
#include <memory>

#include "MemoryIR/IRContext.h"
#include "MemoryIR/IRbuilder.h"
#include "MemoryIR/Module.h"
#include "RegisterAllocation/InterferenceGraph.h"
#include "RegisterAllocation/LivenessAnalyzer.h"

int main() {
    using namespace mipsir;

    auto ctx = std::make_unique<IRContext>();
    auto builder = std::make_unique<IRBuilder>(ctx.get());
    auto module = std::make_unique<Module>(ctx.get());
    const std::vector<std::string> args{"a", "b"};
    Function *function = module->createFunction("add", args);
    Block *entryBlock = ctx->createBlock(function);

    builder->setInsertPoint(entryBlock);
    Value *a = function->getArgs()[0];
    Value *b = function->getArgs()[1];
    Value *c = builder->createAddInstr(a, b);
    Value *d = ctx->createConstantInt(3);

    builder->createReturn(builder->createAddInstr(d, c));

    module->print(std::cout);

    InterferenceGraph g = LivenessAnalyzer::constructRegisterInterferenceGraph(function);
    g.color();
    auto coloring = g.getColoring();
    for (auto &pair: coloring) {
        std::cout << "%" << pair.first << " -> " << pair.second << std::endl;
    }

    return 0;
}
