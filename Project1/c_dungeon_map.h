// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_dungeon_map.h
// Description : Methods for loading, verifying, displaying and saving the dungeon map.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/
#pragma once
#include <vector>
#include <string>
#include "c_graph.h"

class c_dungeon_map
{
public:
    /**
	 * @brief Empty map to be shown when no map is loaded.
	 */
	c_dungeon_map();
    /**
     * @brief Constructor for the c_dungeon_map class.
     * @param filename - The name of the file to load.
     * @note  Map must contain exactly one start point ('s'), one end point ('x'),
              and 10 unique items ('a' - 'j').
     */
    c_dungeon_map(const std::string& filename);
    /**
     * @brief Load a new map from a file.
     * @param filename - The name of the file to load.
     * @note  Called by the constructor.
     */
    void load_map(const std::string& filename);
    /**
     * @brief Verify the map data.
     * @note  Called by the constructor.
     */
    void verify_map() const;
    /**
     * @brief Display the map data.
     */
    void display_map() const;
    /**
     * @brief Save the map data to a new file.
     * @note  Saved as 'original_filename_' + '-searched.txt'.
     */
    void save_map(const std::string& new_filename) const;

    /**
     * @brief Convert the map to a graph.
     * @return A graph representation of the map.
     */
    c_graph to_graph() const;

private:
    std::vector<std::vector<char>> map_; // Map data stored as a 2D vector.
    std::string original_filename_;      // Need for new save file name.
};