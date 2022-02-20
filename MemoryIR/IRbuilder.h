//
// Created by henry on 2022-02-19.
//

#ifndef MIPS_IR_MEMORYIR_IRBUILDER_H_
#define MIPS_IR_MEMORYIR_IRBUILDER_H_

#include <memory>

#include "IRContext.h"
#include "Block.h"
#include "Instruction.h"

namespace mipsir {

class IRBuilder {
  public:
    using InsertionPoint = Block::InstructionList::iterator;
  private:
    IRContext *m_context;
    Block *m_currentBlock;
    InsertionPoint m_insertionPoint;
  public:
    explicit IRBuilder(IRContext *context) : m_context(context), m_currentBlock(nullptr) {};
    explicit IRBuilder(Block *currentBlock)
        : m_context(currentBlock->getContext()),
          m_currentBlock(currentBlock),
          m_insertionPoint(currentBlock->getInstructions().end()) {}
    IRBuilder(const IRBuilder &) = delete;
    IRBuilder(IRBuilder &&) = default;

    void setInsertPoint(Block *block) {
        m_currentBlock = block;
        m_insertionPoint = block->getInstructions().end();
    }

    Instruction *createStoreInstr(Value *ptr, Value *expr) { return createInstruction<StoreInstruction>(ptr, expr); }
    Instruction *createVoidReturn() { return createInstruction<ReturnInstruction>(); }
    Instruction *createReturn(Value *expr) { return createInstruction<ValuedReturnInstruction>(expr); }

    Value *createLoadInstr(Value *ptr) { return createInstruction<LoadInstruction>(ptr); }

    Value *createAddInstr(Value *lhs, Value *rhs) { return createInstruction<AddInstruction>(lhs, rhs); }
    Value *createSubInstr(Value *lhs, Value *rhs) { return createInstruction<SubInstruction>(lhs, rhs); }
    Value *createMulInstr(Value *lhs, Value *rhs) { return createInstruction<MulInstruction>(lhs, rhs); }
    Value *createDivInstr(Value *lhs, Value *rhs) { return createInstruction<DivInstruction>(lhs, rhs); }

  private:
    template<typename InstrType, typename... Args>
    Instruction *createInstruction(Args &&... args) {
        auto instr = std::make_unique<InstrType>(std::forward<Args>(args)...);
        m_context->m_instructions.push_back(std::move(instr));
        insertInstruction(m_context->m_instructions.back().get());
        return m_context->m_instructions.back().get();
    }

    void insertInstruction(Instruction *instruction) {
        if (!m_currentBlock || !m_context) throw std::runtime_error("No Block or Context!");
        m_insertionPoint = m_currentBlock->getInstructions().insert(m_insertionPoint, instruction);
        ++m_insertionPoint;
    }
};

}

#endif //MIPS_IR_MEMORYIR_IRBUILDER_H_
