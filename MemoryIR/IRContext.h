//
// Created by henry on 2022-02-19.
//

#ifndef MIPS_IR_MEMORYIR_IRCONTEXT_H_
#define MIPS_IR_MEMORYIR_IRCONTEXT_H_

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

#include "Value.h"
#include "Constant.h"
#include "Function.h"

namespace mipsir {

class Instruction;
class Block;

class IRContext {
    std::unordered_map<int, std::unique_ptr<Constant>> m_constantTable;
    std::vector<std::unique_ptr<Instruction>> m_instructions;
    std::vector<std::unique_ptr<Block>> m_blocks;
    std::unordered_map<std::string, std::unique_ptr<Function>> m_functions;
    std::unordered_map<std::string, std::unique_ptr<Argument>> m_arguments;
    std::vector<std::unique_ptr<GlobalVariable>> m_globalVars;
  public:
    IRContext() = default;
    friend class Module;
    friend class Function;
    friend class IRBuilder;
  public:
    Constant *createConstantInt(int value);
    Block *createBlock(Function *parent = nullptr);
    Argument *createArgument(const std::string &func, const std::string &argument);
    GlobalVariable *createGlobal(int value);
    GlobalVariable *createGlobal(std::vector<int> values);
};

}

#endif //MIPS_IR_MEMORYIR_IRCONTEXT_H_
