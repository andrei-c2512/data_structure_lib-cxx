#pragma once
#include <vector>

namespace TinyDS{
    template <typename T>
    class GraphNode {
    public:
            GraphNode() = default;
            void addNeighbour(GraphNode<T>* node) {
                    neighbours.emplace_back(node);
            }
    private:
            std::vector<GraphNode<T>*> neighbours;
            T info;
    };
}
