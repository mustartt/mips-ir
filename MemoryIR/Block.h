//
// Created by henry on 2022-02-19.
//

#ifndef MIPS_IR_MEMORYIR_BLOCK_H_
#define MIPS_IR_MEMORYIR_BLOCK_H_

#include <vector>

namespace mipsir {

class IRContext;
class Function;
class Instruction;

class Block {
  public:
    using InstructionList = std::vector<Instruction *>;
  private:
    IRContext *m_context;
    Function *m_parent;
    InstructionList m_instructions;
  public:
    explicit Block(IRContext *context, Function *parent = nullptr);

    [[nodiscard]] IRContext *getContext() const;
    [[nodiscard]] const std::vector<Instruction *> &getInstructions() const;
    [[nodiscard]] std::vector<Instruction *> &getInstructions();
    [[nodiscard]] std::vector<Block *> getOutboundingEdge() const;
};

}

#endif //MIPS_IR_MEMORYIR_BLOCK_H_
