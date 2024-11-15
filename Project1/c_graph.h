#pragma once
#include <vector>
#include <unordered_map>
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>

struct Node {
	int x, y;
	bool is_item;
	bool is_wall;
	bool is_start;
	bool is_exit;

	// Equality operator for Node struct, to be able to use it as a key in an unordered_map.
	bool operator==(const Node& other) const {
		return x == other.x && y == other.y;
	}
};

struct NodeComparator { // Custom comparator for the priority queue in A* algorithm.
    bool operator()(const std::pair<Node, double>& a, const std::pair<Node, double>& b) const {
        return a.second > b.second;
    }
};

// Custom hash function for Node struct, to be able to use it as a key in an unordered_map.
// Unordered map O(1) lookup time, map O(log n) lookup time.
namespace std {
	template <>
	struct hash<Node> { // Hash function for Node struct.
		std::size_t operator()(const Node& node) const noexcept{					   // Takes a Node object as input.
			return std::hash<int>()(node.x) ^ (std::hash<int>()(node.y) << 1); // Hash the x and y coordinates.
		}
	};
}

class c_graph {
public:
	c_graph() = default; // Default constructor.
	/**
	 * @brief Constructor that builds the graph from the specified map.
	 * @param map - The map to build the graph from.
	 */
	c_graph(const std::vector<std::vector<char>>& map);

	/**
	 * @brief Get the node object at the specified coordinates.
	 * @param x  - The x-coordinate of the node.
	 * @param y  - The y-coordinate of the node.
	 * @return   - The node object at the specified coordinates.
	 */
	Node get_node(int x, int y) const;
	/**
	 * @brief Get the neighbors of the specified node.
	 * @param node - The node to get the neighbors of.
	 * @return     - A vector of nodes that are neighbors of the specified node.
	 */
	std::vector<Node> get_neighbors(const Node& node) const;
	/**
	 * @brief Calculate the Euclidean distance between two nodes.
	 * @param a - The first node.
	 * @param b - The second node.
	 * @return  - The Euclidean distance between the two nodes.
	 */
	double euclidean_distance(const Node& a, const Node& b) const;
	/**
	 * @brief Calculate the Manhattan distance between two nodes.
	 * @param a - The first node.
	 * @param b - The second node.
	 * @return  - The Manhattan distance between the two nodes.
	 */
	double manhattan_distance(const Node& a, const Node& b) const;
	/**
	 * @brief Perform a depth-first search starting from the specified node.
	 * @param start - The node to start the search from.
	 */
	void dfs(const Node& start);
	/**
	 * @brief Perform a breadth-first search starting from the specified node.
	 * @param start - The node to start the search from.
	 */
	void bfs(const Node& start);
    /**
     * @brief Perform the A* algorithm to find the shortest path from the start node to the goal node.
     * @param start - The start node.
     * @param goal  - The goal node.
     * @return A vector of pairs representing the path coordinates.
     */
    std::vector<std::pair<int, int>> a_star(const Node& start, const Node& goal);

private:
	std::vector<std::vector<Node>> nodes_;                        // 2D vector of nodes representing the map.
	std::unordered_map<Node, std::vector<Node>> adj_list_; 	      // Adjacency list representation of the graph.

	/**
	 * @brief Build the graph from the specified map.
	 * @param map - The map to build the graph from.
	 * @note      - This function is called by the constructor.
	 */
	void build_graph(const std::vector<std::vector<char>>& map);

	/**
     * @brief Reconstruct the path from the came_from map.
     * @param came_from - Map of nodes and their predecessors.
     * @param current - The current node.
     * @return A vector of nodes representing the path.
     */
    std::vector<Node> reconstruct_path(const std::unordered_map<Node, Node>& came_from, Node current) const;

    /**
     * @brief Check if a move is valid (not cutting corners).
     * @param current - The current node.
     * @param neighbor - The neighbor node.
     * @return True if the move is valid, false otherwise.
     */
    bool is_valid_move(const Node& current, const Node& neighbor) const;
};