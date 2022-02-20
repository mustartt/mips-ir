//
// Created by henry on 2022-02-19.
//

#include "IRContext.h"
#include "Block.h"

namespace mipsir {

Constant *IRContext::createConstantInt(int value) {
    if (!m_constantTable.contains(value)) {
        m_constantTable[value] = std::move(std::make_unique<IntegerConstant>(value));
    }
    return m_constantTable[value].get();
}

Block *IRContext::createBlock(Function *parent) {
    auto block = std::make_unique<Block>(this, parent);
    m_blocks.push_back(std::move(block));
    if (parent && !parent->hasBody())
        parent->setEntryBlock(m_blocks.back().get());
    return m_blocks.back().get();
}

Argument *IRContext::createArgument(const std::string &func, const std::string &argument) {
    const auto key = func + "::" + argument;
    if (m_arguments.count(key)) return m_arguments[key].get();
    m_arguments[key] = std::move(std::make_unique<Argument>(argument));
    return m_arguments[key].get();
}

}
