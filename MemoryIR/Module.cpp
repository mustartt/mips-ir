//
// Created by henry on 2022-02-19.
//

#include <memory>
#include <utility>

#include "Module.h"
#include "IRContext.h"
#include "Function.h"

namespace mipsir {

Function *Module::createFunction(const std::string &name,
                                 const std::vector<std::string> &args,
                                 bool isVoidType) {
    m_context->m_functions[name] = std::move(
        std::make_unique<Function>(m_context, name, args, isVoidType)
    );
    auto ptr = m_context->m_functions[name].get();
    m_functions[name] = ptr;
    return ptr;
}

GlobalVariable *Module::createGlobal(const std::string &name, int value) {
    auto var = m_context->createGlobal(value);
    m_globals[name] = var;
    return var;
}

GlobalVariable *Module::createGlobal(const std::string &name, std::vector<int> values) {
    auto var = m_context->createGlobal(std::move(values));
    m_globals[name] = var;
    return var;
}

void Module::print(std::ostream &ostream) const {
    const auto divider = [&]() {
      for (int i = 0; i < 50; ++i) ostream << '=';
      ostream << std::endl;
    };
    ostream << "IR-Module: " << m_moduleName << std::endl;
    divider();
    ostream << "Globals: " << std::endl;
    divider();

    for (const auto&[name, var]: m_globals) {
        ostream << "global %" << name << " = ";
        var->print(ostream);
        ostream << std::endl;
    }

    divider();
    ostream << "Functions: " << std::endl;
    divider();
    ostream << std::endl;

    for (const auto&[name, func]: m_functions) {
        func->print(ostream);
        ostream << std::endl;
    }
}

}
