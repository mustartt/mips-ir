//
// Created by henry on 2022-02-19.
//

#ifndef MIPS_IR_MEMORYIR_MODULE_H_
#define MIPS_IR_MEMORYIR_MODULE_H_

#include <unordered_map>
#include <string>
#include <vector>

namespace mipsir {

class IRContext;
class Function;
class Constant;

class Module {
    IRContext *m_context;
    std::unordered_map<std::string, Function *> m_functions;
    std::unordered_map<std::string, Constant *> m_globals;
  public:
    explicit Module(IRContext *ctx) : m_context(ctx) {}
    Function *createFunction(const std::string &name, const std::vector<std::string> &args);
};

}

#endif //MIPS_IR_MEMORYIR_MODULE_H_
