#include "c_dungeon_map.h"
#include "c_graph.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <unordered_set>

constexpr int MAP_SIZE = 20;

c_dungeon_map::c_dungeon_map() {
	map_.resize(MAP_SIZE, std::vector<char>(MAP_SIZE, '.')); // Initialize with empty cells.

	// Set walls around the outside.
	for (int i = 0; i < MAP_SIZE; ++i) {
		map_[0][i] = 'w'; // Top row.
		map_[MAP_SIZE - 1][i] = 'w'; // Bottom row.
		map_[i][0] = 'w'; // Left column.
		map_[i][MAP_SIZE - 1] = 'w'; // Right column.
	}
}

c_dungeon_map::c_dungeon_map(const std::string& filename) : original_filename_(filename) {
	load_map(filename);
	verify_map();
}

void c_dungeon_map::load_map(const std::string& filename) {
    // Strip quotation marks from the filename
    std::string clean_filename = filename;
    clean_filename.erase(remove(clean_filename.begin(), clean_filename.end(), '\"'), clean_filename.end());

    // Open the file, throw an exception if it fails.
    std::ifstream file(clean_filename);
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

    // Verify the map after loading
    try {
        verify_map();
    }
    catch (const std::exception& e) {
        // Log the exception message
        std::cerr << "Error verifying map: " << e.what() << '\n';

        // If verification fails, reset to an empty map and rethrow the exception
        map_.clear();
        map_.resize(MAP_SIZE, std::vector<char>(MAP_SIZE, '.'));
        // Set walls around the outside.
        for (int i = 0; i < MAP_SIZE; ++i) {
            map_[0][i] = 'w'; // Top row.
            map_[MAP_SIZE - 1][i] = 'w'; // Bottom row.
            map_[i][0] = 'w'; // Left column.
            map_[i][MAP_SIZE - 1] = 'w'; // Right column.
        }
        throw;
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

void c_dungeon_map::save_map(const std::string& new_filename) const {
    // Ensure the filename has a .txt extension
    std::string filename = new_filename;
    if (filename.find(".txt") == std::string::npos) {
        filename += ".txt";
    }

    // Prepend the 'data/' directory to the filename
    std::string filepath = "data/" + filename;

    // Open the file for writing, throw an exception if it fails.
    std::ofstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing");
    }

    // Write the map data to the file.
    for (const auto& row : map_) {
        for (char cell : row) {
            file << cell << ' ';
        }
        file << '\n'; // Newline after each row.
    }

    // Close the file.
    file.close();
    std::cout << "Map saved successfully to " << filepath << '\n';
}

c_graph c_dungeon_map::to_graph() const {
    return {map_};
}

std::pair<int, int> c_dungeon_map::get_start_node() const {
	// Iterate over the map to find the start node.
	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			if (map_[i][j] == 's') {
				return { i, j };
			}
		}
	}
	throw std::runtime_error("Start node not found");
}

std::pair<int, int> c_dungeon_map::get_end_node() const {
	// Iterate over the map to find the end node.
	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			if (map_[i][j] == 'x') {
				return { i, j };
			}
		}
	}
	throw std::runtime_error("End node not found");
}

void c_dungeon_map::mark_path(const std::vector<std::pair<int, int>>& path) {
    for (const auto& coord : path) {
        int x = coord.first;
        int y = coord.second;
        if (map_[x][y] != 's' && map_[x][y] != 'x') {
            map_[x][y] = 'p'; // Mark the path with 'p'
        }
    }
}