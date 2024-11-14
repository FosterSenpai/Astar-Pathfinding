#include "c_graph.h"
#include <iostream>
#include <limits>

Node c_graph::get_node(int x, int y) const {
    if (x < 0 || x >= nodes_.size() || y < 0 || y >= nodes_[0].size()) {
        throw std::out_of_range("Node position out of range");
    }
    return nodes_[x][y];
}

c_graph::c_graph(const std::vector<std::vector<char>>& map) {
    build_graph(map);
}

void c_graph::build_graph(const std::vector<std::vector<char>>& map) {
    int rows = map.size();
    int cols = map[0].size();
    nodes_.resize(rows, std::vector<Node>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char ch = map[i][j];
            nodes_[i][j] = {i, j, (ch >= 'a' && ch <= 'j'), ch == 'w', ch == 's', ch == 'x'};
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!nodes_[i][j].is_wall) {
                adj_list_[nodes_[i][j]] = get_neighbors(nodes_[i][j]);
            }
        }
    }
}

std::vector<Node> c_graph::get_neighbors(const Node& node) const {
    std::vector<Node> neighbors;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (const auto& dir : directions) {
        int new_x = node.x + dir[0];
        int new_y = node.y + dir[1];

        if (new_x >= 0 && new_x < nodes_.size() && new_y >= 0 && new_y < nodes_[0].size()) {
            neighbors.push_back(nodes_[new_x][new_y]);
        }
    }

    return neighbors;
}

double c_graph::euclidean_distance(const Node& a, const Node& b) const {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

double c_graph::manhattan_distance(const Node& a, const Node& b) const {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void c_graph::dfs(const Node& start) {
    std::stack<Node> stack;
    std::unordered_map<Node, bool> visited;
    std::vector<Node> collected_items;
    stack.push(start);

    while (!stack.empty()) {
        Node current = stack.top();
        stack.pop();

        if (visited[current]) continue;
        visited[current] = true;

        if (current.is_item) {
            collected_items.push_back(current);
            if (collected_items.size() == 10) break;
        }

        auto neighbors = get_neighbors(current);
        std::sort(neighbors.begin(), neighbors.end(), [this, &current](const Node& a, const Node& b) {
            return euclidean_distance(current, a) < euclidean_distance(current, b);
        });

        for (const auto& neighbor : neighbors) {
            if (!visited[neighbor] && !neighbor.is_wall) {
                stack.push(neighbor);
            }
        }
    }

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
    std::queue<Node> queue;
    std::unordered_map<Node, bool> visited;
    std::vector<Node> collected_items;
    queue.push(start);

    while (!queue.empty()) {
        Node current = queue.front();
        queue.pop();

        if (visited[current]) continue;
        visited[current] = true;

        if (current.is_item) {
            collected_items.push_back(current);
            if (collected_items.size() == 10) break;
        }

        for (const auto& neighbor : get_neighbors(current)) {
            if (!visited[neighbor] && !neighbor.is_wall) {
                queue.push(neighbor);
            }
        }
    }

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