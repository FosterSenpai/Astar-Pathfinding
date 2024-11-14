// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_graph.h
// Description : Methods for adding nodes + edges and getting neighbors.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/
#pragma once
#include <vector>
#include <cmath>
#include "c_node.h"

class c_graph
{
public:
    /**
     * @brief Add a node to the graph.
     * @param row - The row position of the node.
     * @param col - The column position of the node.
     * @return The index of the added node.
     */
    int add_node(int row, int col);

    /**
     * @brief Add an edge between two nodes with a weight.
     * @param from_index - The index of the starting node.
     * @param to_index   - The index of the ending node.
     */
    void add_edge(int from_index, int to_index);

    /**
     * @brief Get the neighbors of a node.
     * @param node_index - The index of the node to get neighbors for.
     * @return A vector of indices representing neighboring nodes.
     */
    std::vector<int> get_neighbors(int node_index) const;

    /**
     * @brief Print the graph.
     */
    void print_graph() const;

    /**
     * @brief Calculate the Euclidean distance between two nodes.
     * @param from_index - The index of the starting node.
     * @param to_index   - The index of the ending node.
     * @return The Euclidean distance between the nodes.
     */
    int euclidean_distance(int from_index, int to_index) const;

private:
    std::vector<s_node> nodes_;
};