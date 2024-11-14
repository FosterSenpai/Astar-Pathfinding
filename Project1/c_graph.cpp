#include "c_graph.h"
#include <iostream>

int c_graph::add_node(int row, int col) {
    nodes_.emplace_back(row, col);
    return nodes_.size() - 1;
}

void c_graph::add_edge(int from_index, int to_index) {
    nodes_[from_index].neighbors.push_back(to_index);
    nodes_[to_index].neighbors.push_back(from_index); // Assuming an undirected graph
}

std::vector<int> c_graph::get_neighbors(int node_index) const {
    return nodes_[node_index].neighbors;
}

void c_graph::print_graph() const {
    for (size_t i = 0; i < nodes_.size(); ++i) {
        const s_node& node = nodes_[i];
        std::cout << "Node " << i << " (" << node.row << ", " << node.col << ") has neighbors: ";
        for (int neighbor_index : node.neighbors) {
            std::cout << neighbor_index << " ";
        }
        std::cout << "\n";
    }
}

int c_graph::euclidean_distance(int from_index, int to_index) const {
    const s_node& from = nodes_[from_index];
    const s_node& to = nodes_[to_index];
    int dx = from.row - to.row;
    int dy = from.col - to.col;
    return static_cast<int>(std::sqrt(dx * dx + dy * dy));
}