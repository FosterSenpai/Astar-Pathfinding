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

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

// Custom hash function for Node struct, to be able to use it as a key in an unordered_map.
// Unordered map O(1) lookup time, map O(log n) lookup time.
namespace std {
    template <>
    struct hash<Node> {
        std::size_t operator()(const Node& node) const {
            return std::hash<int>()(node.x) ^ (std::hash<int>()(node.y) << 1);
        }
    };
}

class c_graph {
public:
    Node get_node(int x, int y) const;
    c_graph() = default;
    c_graph(const std::vector<std::vector<char>>& map);
    std::vector<Node> get_neighbors(const Node& node) const;
    double euclidean_distance(const Node& a, const Node& b) const;
    double manhattan_distance(const Node& a, const Node& b) const;
    void dfs(const Node& start);
    void bfs(const Node& start);
    void a_star(const Node& start, const Node& goal);

private:
    std::vector<std::vector<Node>> nodes_;
    std::unordered_map<Node, std::vector<Node>> adj_list_;
    void build_graph(const std::vector<std::vector<char>>& map);
};