//
// Created by henry on 2022-02-19.
//

#ifndef MIPS_IR_MEMORYIR_VALUE_H_
#define MIPS_IR_MEMORYIR_VALUE_H_

#include <ostream>

namespace mipsir {

class Value {
  public:
    virtual ~Value() = default;
    virtual void print(std::ostream &) = 0;
};

}

#endif //MIPS_IR_MEMORYIR_VALUE_H_
