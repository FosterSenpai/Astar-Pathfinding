// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_node.h
// Description : A simple struct to represent a node in a graph.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/
#pragma once
#include <vector>

struct s_node {
    // A node is represented by its (row, col) position.
    int row;
    int col;

    std::vector<int> neighbors; // Vector of indices of neighboring nodes.

    /**
	 * @brief Constructor for the s_node struct.
	 * @param r - The row of the node.
	 * @param c - The column of the node.
	 */
    s_node(int r, int c) : row(r), col(c) {}
};