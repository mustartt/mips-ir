//
// Created by henry on 2022-02-19.
//

#include "Block.h"

#include "Instruction.h"

namespace mipsir {

Block::Block(IRContext *context, Function *parent) : m_context(context), m_parent(parent) {}

IRContext *Block::getContext() const { return m_context; }

const std::vector<Instruction *> &Block::getInstructions() const { return m_instructions; }

std::vector<Instruction *> &Block::getInstructions() { return m_instructions; }

std::vector<Block *> Block::getOutboundingEdge() const {
    Instruction *lastInstr = m_instructions.back();
    if (dynamic_cast<ReturnInstruction *>(lastInstr)) return {};
    const auto branch = dynamic_cast<BranchInstruction *>(lastInstr);
    if (branch) return branch->getOutbound();
    throw std::runtime_error("Block must end with ret or br");
}

}
