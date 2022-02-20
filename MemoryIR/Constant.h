//
// Created by henry on 2022-02-19.
//

#ifndef MIPS_IR_MEMORYIR_CONSTANT_H_
#define MIPS_IR_MEMORYIR_CONSTANT_H_

#include <ostream>

#include "Value.h"

namespace mipsir {

class Constant : public Value {};

class IntegerConstant : public Constant {
    int value;
  public:
    explicit IntegerConstant(int val) : value(val) {}
    void print(std::ostream &ostream) override { ostream << value; }
};

class GlobalVariable : public Constant {
  public:
    GlobalVariable() = default;
};

class GlobalConstantInt : public GlobalVariable {
    int value;
  public:
    explicit GlobalConstantInt(int val) : value(val) {}
    void print(std::ostream &ostream) override { ostream << value; }
};

class GlobalConstantIntArray : public GlobalVariable {
    std::vector<int> values;
  public:
    explicit GlobalConstantIntArray(std::vector<int> values) : values(std::move(values)) {}
    void print(std::ostream &ostream) override {
        ostream << "[";
        for (size_t i = 0; i < values.size(); ++i) {
            ostream << values[i];
            if (i + 1 != values.size()) ostream << ", ";
        }
        ostream << "]";
    }
};

}

#endif //MIPS_IR_MEMORYIR_CONSTANT_H_
