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

}

#endif //MIPS_IR_MEMORYIR_CONSTANT_H_
