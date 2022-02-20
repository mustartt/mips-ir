//
// Created by henry on 2022-02-19.
//

#ifndef MIPS_IR_MEMORYIR_INSTRUCTION_H_
#define MIPS_IR_MEMORYIR_INSTRUCTION_H_

#include <utility>
#include <vector>
#include <unordered_map>

#include "Function.h"

#include "Value.h"

namespace mipsir {

class Block;

class Instruction : public Value {
  public:
    virtual std::vector<Value *> getOperands() = 0;
    [[nodiscard]] virtual bool hasReturnValue() const = 0;
};

class PointerCalculation : public Instruction {};

class CallInstruction : public Instruction {
    Function *callee;
    std::vector<Value *> args;
  public:
    CallInstruction(Function *callee, std::vector<Value *> args) : callee(callee), args(std::move(args)) {}
    [[nodiscard]] bool hasReturnValue() const override { return callee->hasReturnValue(); }
    void print(std::ostream &ostream) override { ostream << "call"; }
    std::vector<Value *> getOperands() override { return {}; }
    [[nodiscard]] const std::vector<Value *> &getFunctionArguments() const { return args; }
    [[nodiscard]] const std::string &getCalleName() const { return callee->getName(); }
};

/*
class IndirectCallInstruction : public CallInstruction {
    Value *funcPtr;
    std::vector<Value *> args;
  public:
    IndirectCallInstruction(Function *callee, Value *ptr, std::vector<Value *> args)
        : CallInstruction(callee, std::move(args)), funcPtr(ptr) {}
    std::vector<Value *> getOperands() override { return {funcPtr}; }
};
*/

class BranchInstruction : public Instruction {
  public:
    [[nodiscard]] bool hasReturnValue() const override { return false; }
    virtual std::vector<Block *> getOutbound() = 0;
    void print(std::ostream &ostream) override { ostream << "br"; }
};

class BranchUnconditional : public BranchInstruction {
    Block *branch;
  public:
    explicit BranchUnconditional(Block *block) : branch(block) {}
    std::vector<Value *> getOperands() override { return {}; }
    std::vector<Block *> getOutbound() override { return {branch}; }
};

class BranchConditional : public BranchInstruction {
    Block *branchTrue;
    Block *branchFalse;
    Value *condition;
  public:
    BranchConditional(Value *condition, Block *branchTrue, Block *branchFalse)
        : condition(condition), branchTrue(branchTrue), branchFalse(branchFalse) {}
    std::vector<Value *> getOperands() override { return {condition}; }
    std::vector<Block *> getOutbound() override { return {branchTrue, branchFalse}; }
};

class StoreInstruction : public Instruction {
    Value *ptr;
    Value *expr;
  public:
    StoreInstruction(Value *ptr, Value *expr) : ptr(ptr), expr(expr) {}
    [[nodiscard]] bool hasReturnValue() const override { return false; }
    void print(std::ostream &ostream) override { ostream << "store"; }
    std::vector<Value *> getOperands() override { return {ptr, expr}; }
};

class ReturnInstruction : public Instruction {
  public:
    [[nodiscard]] bool hasReturnValue() const override { return false; }
    void print(std::ostream &ostream) override { ostream << "ret"; }
    std::vector<Value *> getOperands() override { return {}; }
};

class ValuedReturnInstruction : public ReturnInstruction {
    Value *retValue;
  public:
    explicit ValuedReturnInstruction(Value *retValue) : retValue(retValue) {}
    std::vector<Value *> getOperands() override { return {retValue}; }
};

class UnaryInstruction : public Instruction {
    Value *expr;
  public:
    explicit UnaryInstruction(Value *expr) : expr(expr) {}
    [[nodiscard]] bool hasReturnValue() const override { return true; }
    std::vector<Value *> getOperands() override { return {expr}; }
};

class LoadInstruction : public UnaryInstruction {
  public:
    explicit LoadInstruction(Value *expr) : UnaryInstruction(expr) {}
    void print(std::ostream &ostream) override { ostream << "load"; }
};

class BinaryInstruction : public Instruction {
  protected:
    Value *lhs;
    Value *rhs;
  public:
    BinaryInstruction(Value *lhs, Value *rhs) : lhs(lhs), rhs(rhs) {}
    std::vector<Value *> getOperands() override { return {lhs, rhs}; }
    [[nodiscard]] bool hasReturnValue() const override { return true; }
};

class AddInstruction : public BinaryInstruction {
  public:
    AddInstruction(Value *lhs, Value *rhs) : BinaryInstruction(lhs, rhs) {}
    void print(std::ostream &ostream) override { ostream << "add"; }
};

class SubInstruction : public BinaryInstruction {
  public:
    SubInstruction(Value *lhs, Value *rhs) : BinaryInstruction(lhs, rhs) {}
    void print(std::ostream &ostream) override { ostream << "sub"; }
};

class MulInstruction : public BinaryInstruction {
  public:
    MulInstruction(Value *lhs, Value *rhs) : BinaryInstruction(lhs, rhs) {}
    void print(std::ostream &ostream) override { ostream << "mul"; }
};

class DivInstruction : public BinaryInstruction {
  public:
    DivInstruction(Value *lhs, Value *rhs) : BinaryInstruction(lhs, rhs) {}
    void print(std::ostream &ostream) override { ostream << "div"; }
};

class CmpInstruction : public BinaryInstruction {
  public:
    enum class CmpOp {
      Equal, NotEqual, LessThan, GreaterThan, GreaterThanEqual, LessThanEqual
    };
  private:
    CmpOp op;
  private:
    static std::string getEnumCmp(CmpInstruction::CmpOp op) {
        std::unordered_map<CmpOp, std::string> operatorMap{
            {CmpOp::Equal, "eq"},
            {CmpOp::NotEqual, "ne"},
            {CmpOp::LessThan, "lt"},
            {CmpOp::GreaterThan, "gt"},
            {CmpOp::GreaterThanEqual, "ge"},
            {CmpOp::LessThanEqual, "le"}
        };
        return operatorMap.at(op);
    }
  public:
    CmpInstruction(CmpInstruction::CmpOp op, Value *lhs, Value *rhs)
        : BinaryInstruction(lhs, rhs), op(op) {}
    void print(std::ostream &ostream) override { ostream << "cmp " << getEnumCmp(op); }
};

}

#endif //MIPS_IR_MEMORYIR_INSTRUCTION_H_
