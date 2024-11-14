#include "c_dungeon_map.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <unordered_set>

constexpr int MAP_SIZE = 20;

c_dungeon_map::c_dungeon_map(const std::string& filename) : original_filename_(filename) {
    load_map(filename);
    verify_map();
}

void c_dungeon_map::load_map(const std::string& filename) {
    // Open the file, throw an exception if it fails.
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    // Read the map data into 'map_' vector.
    map_.resize(MAP_SIZE, std::vector<char>(MAP_SIZE));
    for (int i = 0; i < MAP_SIZE; ++i) {     // Rows.
        for (int j = 0; j < MAP_SIZE; ++j) { // Columns.
            file >> map_[i][j];              // Read char into map_.
        }
    }
}

void c_dungeon_map::verify_map() const
{
    // Start + end point counters, and a set to store items.
    int start_count = 0;
    int end_count = 0;
    std::unordered_set<char> items;

    for (const auto& row : map_) { // Iterate over rows.
        for (char cell : row) { // For each cell in the row:
            // Count start/end points and store items.
            if (cell == 's') start_count++;
            if (cell == 'x') end_count++;
            if (cell >= 'a' && cell <= 'j') items.insert(cell);
            // Check for invalid characters.
            if (cell != 'w' && cell != '.' && cell != 's' && cell != 'x' && (cell < 'a' || cell > 'j')) {
                throw std::runtime_error("Invalid character in map");
            }
        }
    }

    // Check for invalid counts.
    if (start_count != 1 || end_count != 1) {
        throw std::runtime_error("Map must contain exactly one start point and one end point");
    }
    if (items.size() != 10) {
        throw std::runtime_error("Map must contain exactly 10 unique items (a-j)");
    }
}

void c_dungeon_map::display_map() const {
    // Iterate over each row in the map.
    for (const auto& row : map_) {
        // Print cell char + padding for each cell in the row.
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n'; // Newline after each row.
    }
}

void c_dungeon_map::save_map() const {
    // Create a new filename by inserting "-searched" before the file extension.
    std::string new_filename = original_filename_;
    size_t dot_pos = new_filename.find_last_of('.');
    if (dot_pos != std::string::npos) {
        new_filename.insert(dot_pos, "-searched");
    } else {
        new_filename.append("-searched");
    }

    // Make the new file.
    std::ofstream file(new_filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    // Write the map data to the new file.
    for (const auto& row : map_) {
        for (char cell : row) {
            file << cell << ' ';
        }
        file << '\n';
    }
}