//
// Created by henry on 2022-02-19.
//

#ifndef MIPS_IR_MEMORYIR_MODULE_H_
#define MIPS_IR_MEMORYIR_MODULE_H_

#include <unordered_map>
#include <string>
#include <vector>
#include "IRContext.h"

namespace mipsir {

class IRContext;
class Function;
class Constant;

class Module {
    std::string m_moduleName;
    IRContext *m_context;
    std::unordered_map<std::string, Function *> m_functions;
    std::unordered_map<std::string, Constant *> m_globals;
  public:
    explicit Module(IRContext *ctx, std::string moduleName = "module")
        : m_context(ctx), m_moduleName(std::move(moduleName)) {}
    Function *createFunction(const std::string &name, const std::vector<std::string> &args, bool isVoidType = true);
    GlobalVariable *createGlobal(const std::string &name, int value);
    GlobalVariable *createGlobal(const std::string &name, std::vector<int> values);

    void print(std::ostream &ostream) const;
};

}

#endif //MIPS_IR_MEMORYIR_MODULE_H_
