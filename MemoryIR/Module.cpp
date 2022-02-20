//
// Created by henry on 2022-02-19.
//

#include <memory>

#include "Module.h"
#include "IRContext.h"
#include "Function.h"

namespace mipsir {

Function *Module::createFunction(const std::string &name, const std::vector<std::string> &args) {
    m_context->m_functions[name] = std::move(std::make_unique<Function>(m_context, name, args));
    auto ptr = m_context->m_functions[name].get();
    m_functions[name] = ptr;
    return ptr;
}

}
