#include "c_graph.h"
#include <iostream>
#include <limits>

Node c_graph::get_node(int x, int y) const {
    // Check if the coordinates are within the bounds of the graph.
    if (x < 0 || x >= nodes_.size() || y < 0 || y >= nodes_[0].size()) {
        throw std::out_of_range("Node position out of range");
    }
    return nodes_[x][y];
}

c_graph::c_graph(const std::vector<std::vector<char>>& map) {
    build_graph(map);
}

void c_graph::build_graph(const std::vector<std::vector<char>>& map) {
    // Resize the nodes vector to match the map size.
    int rows = map.size();
    int cols = map[0].size();
    nodes_.resize(rows, std::vector<Node>(cols)); 

    // Iterate over the map and build the nodes.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char ch = map[i][j];
            nodes_[i][j] = {i, j, (ch >= 'a' && ch <= 'j'), ch == 'w', ch == 's', ch == 'x'};
        }
    }

    // Iterate over the nodes and build the adjacency list.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!nodes_[i][j].is_wall) { // Skip walls.
                adj_list_[nodes_[i][j]] = get_neighbors(nodes_[i][j]);
            }
        }
    }
}

std::vector<Node> c_graph::get_neighbors(const Node& node) const {
    std::vector<Node> neighbors;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, down, left, right.

    // Iterate over the directions and add valid neighbors.
    for (const auto& dir : directions) {
        int new_x = node.x + dir[0];
        int new_y = node.y + dir[1];

        // Check if the new coordinates are within the bounds of the graph.
        if (new_x >= 0 && new_x < nodes_.size() && new_y >= 0 && new_y < nodes_[0].size()) {
            neighbors.push_back(nodes_[new_x][new_y]);
        }
    }

    return neighbors;
}

double c_graph::euclidean_distance(const Node& a, const Node& b) const {
    // Euclidean distance formula: sqrt((x2 - x1)^2 + (y2 - y1)^2)
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

double c_graph::manhattan_distance(const Node& a, const Node& b) const {
    // Manhattan distance formula: |x2 - x1| + |y2 - y1|
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void c_graph::dfs(const Node& start) {
    std::stack<Node> stack;                 // Stack for DFS traversal.
    std::unordered_map<Node, bool> visited; // Map to store visited nodes.
    std::vector<Node> collected_items;      // Vector to store collected items.
    stack.push(start); // Push the start node onto the stack.

    while (!stack.empty()) { // Continue until the stack is empty.
        // Get the top node from the stack.
        Node current = stack.top();
        stack.pop();
        // Skip if the node has already been visited.
        if (visited[current]) continue;
        visited[current] = true;
        // Mark the node as visited.
        if (current.is_item) {
            collected_items.push_back(current);
            if (collected_items.size() == 10) break;
        }
        // Add unvisited neighbors to the stack.
        for (const auto& neighbor : get_neighbors(current)) {
            if (!visited[neighbor]) {
                stack.push(neighbor);
            }
        }
    }

    // Print the array of collected items.
    std::cout << "DFS collected items in order: ";
    for (size_t i = 0; i < collected_items.size(); ++i) {
        std::cout << "(" << collected_items[i].x << ", " << collected_items[i].y << ")";
        if (i < collected_items.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}

void c_graph::bfs(const Node& start) {
    std::queue<Node> queue;                 // Queue for BFS traversal.
    std::unordered_map<Node, bool> visited; // Map to store visited nodes.
    std::vector<Node> collected_items; 	    // Vector to store collected items.
    queue.push(start); // Push the start node onto the queue.

    while (!queue.empty()) { // Continue until the queue is empty.
        // Get the front node from the queue.
        Node current = queue.front();
        queue.pop();
        // Skip if the node has already been visited.
        if (visited[current]) continue;
        visited[current] = true;
        // Mark the node as visited.
        if (current.is_item) {
            collected_items.push_back(current);
            if (collected_items.size() == 10) break;
        }
        // Add unvisited neighbors to the queue.
        for (const auto& neighbor : get_neighbors(current)) {
            if (!visited[neighbor]) {
                queue.push(neighbor);
            }
        }
    }

    // Print the array of collected items.
    std::cout << "BFS collected items in order: ";
    for (size_t i = 0; i < collected_items.size(); ++i) {
        std::cout << "(" << collected_items[i].x << ", " << collected_items[i].y << ")";
        if (i < collected_items.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}

void c_graph::a_star(const Node& start, const Node& goal) {
    // Implement A* algorithm here
}