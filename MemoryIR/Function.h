//
// Created by henry on 2022-02-19.
//

#ifndef MIPS_IR_MEMORYIR_FUNCTION_H_
#define MIPS_IR_MEMORYIR_FUNCTION_H_

#include <string>
#include <vector>

#include "Value.h"

namespace mipsir {

class IRContext;
class Block;

class Argument : public Value {
    std::string name;
  public:
    explicit Argument(std::string name) : name(std::move(name)) {}
    void print(std::ostream &ostream) override { ostream << name; };
    [[nodiscard]] const std::string &getArgName() const { return name; }
};

class Function : public Value {
    IRContext *m_context;
    std::string m_name;
    std::vector<Argument *> m_args;
    Block *m_entryBlock;
    bool isVoidType;
  public:
    Function(IRContext *ctx, std::string name, const std::vector<std::string> &args, bool isVoidType = true);
    [[nodiscard]] std::vector<Block *> getFunctionBlocks() const;
    std::vector<Argument *> &getArgs() { return m_args; }
    void print(std::ostream &ostream) override;
    void setEntryBlock(Block *entryBlock) { m_entryBlock = entryBlock; }
    [[nodiscard]] bool hasBody() const { return m_entryBlock != nullptr; }
    [[nodiscard]] bool hasReturnValue() const { return isVoidType; }
    [[nodiscard]] const std::string &getName() const { return m_name; }
};

}

#endif //MIPS_IR_MEMORYIR_FUNCTION_H_
