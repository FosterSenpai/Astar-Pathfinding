#include "c_graph.h"
#include <iostream>
#include <unordered_set>

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
			nodes_[i][j] = { i, j, (ch >= 'a' && ch <= 'j'), ch == 'w', ch == 's', ch == 'x' };
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

std::vector<Node> c_graph::reconstruct_path(const std::unordered_map<Node, Node>& came_from, Node current) const {
    std::vector<Node> path;

	// Traverse the came_from map from the goal and move backwards to the start.
    while (came_from.find(current) != came_from.end()) {
        path.push_back(current);         // Add the current node to the path.
        current = came_from.at(current); // Move to the previous node in the path.
    }

    path.push_back(current); // Add the start node to the path.
    std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order.
    return path;
}

bool c_graph::is_valid_move(const Node& current, const Node& neighbor) const {
	// Difference in x and y coordinates between the current and neighbor nodes.
    int dx = neighbor.x - current.x;
    int dy = neighbor.y - current.y;

	// Check if the move is valid (not cutting corners)
    if (std::abs(dx) + std::abs(dy) == 2) { // Absolute difference of 2 means we are moving diagonally.
		// If there is a wall blocking the diagonal move, it is invalid.
        if (nodes_[current.x + dx][current.y].is_wall || nodes_[current.x][current.y + dy].is_wall) { 
            return false;
        }
    }
	// If the move is not diagonal or the diagonal move is valid, return true.
    return true;
}

std::vector<Node> c_graph::get_neighbors(const Node& node) const {
	std::vector<Node> neighbors;
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // Up, down, left, right.

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

std::vector<std::pair<int, int>> c_graph::a_star(const Node& start, const Node& goal) {
    std::priority_queue<std::pair<Node, double>, std::vector<std::pair<Node, double>>, NodeComparator> open_set; // Priority queue for nodes to be evaluated, ordered by f_score.
    std::unordered_map<Node, Node> came_from; // Map to store the most efficient previous step for each node.
    std::unordered_map<Node, double> g_score; // Map to store the cost of the cheapest path from start to each node.
    std::unordered_map<Node, double> f_score; // Map to store the estimated total cost from start to goal through each node.
    std::unordered_set<Node> closed_set;      // Set to store nodes that have already been evaluated.

    // Initialize the start node.
    open_set.emplace(start, 0.0);
    g_score[start] = 0.0;
    f_score[start] = manhattan_distance(start, goal);

    // Continue until the open set is empty.
    while (!open_set.empty()) {
        // Get the node with the lowest f_score.
        Node current = open_set.top().first;
        open_set.pop();

        // Check if the current node is the goal.
        if (current == goal) {
            // If the goal is reached, reconstruct the path and return it.
            std::vector<Node> path_nodes = reconstruct_path(came_from, current);

            // Convert the nodes to a vector of pairs representing the path coordinates.
            std::vector<std::pair<int, int>> path;
            for (const auto& node : path_nodes) {
                path.emplace_back(node.x, node.y);
            }

            std::cout << "Path found!" << std::endl;
            return path;
        }

        // If the current node is not the goal, add it to the closed set.
        closed_set.insert(current);

        // Iterate over the neighbors of the current node.
        for (const auto& neighbor : get_neighbors(current)) {
            // Skip if the neighbor is in the closed set, is a wall, or the move is invalid.
            if (closed_set.find(neighbor) != closed_set.end() || neighbor.is_wall || !is_valid_move(current, neighbor)) {
                continue;
            }

            // Calculate the tentative g_score.
            double tentative_g_score = g_score[current] + euclidean_distance(current, neighbor);

            // If the neighbor is not in the g_score map or the tentative g_score is less than the current g_score.
            if (g_score.find(neighbor) == g_score.end() || tentative_g_score < g_score[neighbor]) {
                // Update the path and scores.
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = g_score[neighbor] + manhattan_distance(neighbor, goal);
                // Add the neighbor to the open set.
                open_set.emplace(neighbor, f_score[neighbor]);
            }
        }
    }

    // If no path is found, return an empty vector.
    std::cout << "No path found!" << std::endl;
    return {};
}