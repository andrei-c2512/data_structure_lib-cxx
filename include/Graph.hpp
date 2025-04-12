#pragma once
#include <vector>
#include <concepts>
#include <forward_list>

typedef std::vector<std::vector<int8_t>> AdjacencyMatrix;


template <typename T>
concept vertex = requires(T a, T b) {
	{ a.operator==(b) }->std::convertible_to<bool>;
};

namespace TinyDS{
    template <vertex T>
    class Graph {
    public:
            Graph() = default;
            bool isEmpty() const {
                    return vertices.empty() && edgeList.empty();
            }
            void addEdge(std::pair<int, int> edge) {
                    auto it = std::lower_bound(edgeList.begin(), edgeList.end(), edge.first, 
                            [](const std::pair<int , int>& pair , int val) {
                                    return pair.first < val;
                            });
                    edgeList.insert(it, edge);
            }
            void removeEdge(std::pair<int, int> edge) {
                    //binary search
                    int left = 0, right = edge.size() - 1;
                    int middle = right / 2;

                    while (left <= right) {
                            if (edgeList[middle].first > edge.first) {
                                    right = middle - 1;
                            }
                            else if (edgeList[middle].first < edge.first) {
                                    left = middle + 1;
                            }
                            else
                                    break;
                    }

                    //we go left and right
                    for (int i = middle; i >= 0; i--) {
                            if (edgeList[i].second == edge.second)
                            {
                                    edgeList.erase(std::begin() + i);
                                    return;
                            }
                    }

                    for (int i = middle; i < edgeList.size(); i++) {
                            if (edgeList[i].second == edge.second)
                            {
                                    edgeList.erase(std::begin() + i);
                                    return;
                            }
                    }
            }
            void addVertex(const T& vertex) {
                    vertices.emplace_back(vertex);
            }
            void removeVertex(const T& vertex) {

            }
            AdjacencyMatrix adjacencyMatrix() const {
                    AdjacencyMatrix matrix(vertices.size(), std::vector<int>(vertices.size() , 0));
                    for (const std::pair<int, int>& pair : edgeList) {
                            matrix[pair.first][pair.second] = 1;
                    }

                    return matrix;
            }
            std::vector<std::forward_list<T>> adjacencyList() const {

            }
            T& vertex(int i) {
                    return vertices[i];
            }
            size_t verticesCount() const {
                    return vertices.size();
            }
            size_t edgeCount() const {
                    return edgeList.size();
            }
    private:
            std::vector<T> vertices;
            std::vector<std::pair<int, int>> edgeList;
    };

}
