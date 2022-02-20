//
// Created by henry on 2022-02-17.
//

#include "InterferenceGraph.h"

namespace mipsir {

void InterferenceGraph::addInterference(RegisterID a, RegisterID b) {
    if (a == b) throw std::runtime_error("register cannot interfere with it self");
    if (!m_registerContext.count(a)) m_registerContext[a] = std::move(std::make_unique<Register>(a));
    if (!m_registerContext.count(b)) m_registerContext[b] = std::move(std::make_unique<Register>(b));
    m_graph[m_registerContext[a].get()].insert(m_registerContext[b].get());
    m_graph[m_registerContext[b].get()].insert(m_registerContext[a].get());
}

void InterferenceGraph::color() {
    const auto firstAvailable = [](const auto &nbr, size_t n) -> Color {
      std::unordered_set<Color> used;
      for (const auto &reg: nbr) used.insert(reg->getColor());
      for (Color c = 1; c <= n; ++c) {
          if (!used.count(c)) return c;
      }
      return 0;
    };
    for (auto &[vertex, nbr]: m_graph) {
        vertex->setColor(firstAvailable(nbr, m_graph.size()));
    }
    m_colored = true;
}

std::unordered_map<RegisterID, Color> InterferenceGraph::getColoring() {
    if (!m_colored) throw std::runtime_error("graph is not colored");
    std::unordered_map<RegisterID, Color> coloring;
    for (const auto&[id, reg]: m_registerContext) {
        coloring[id] = reg->getColor();
    }
    return coloring;
}

}
