#include <iostream>
#include "c_dungeon_map.h"
#include "c_graph.h"
#include "c_dfs.h"
#include "c_dfs.h"
#include "c_a_star.h"

void display_map(const DungeonMap& map) {
	map.display_map();
}

void display_menu() {
	std::cout << "1. Load a new map\n";
	std::cout << "2. Perform DFS\n";
	std::cout << "3. Perform BFS\n";
	std::cout << "4. Run A* algorithm\n";
	std::cout << "5. Save current map\n";
	std::cout << "6. Exit\n";
}

/**
 * @brief Handle user input and call the appropriate function.
 * @param choice - The user's choice.
 * @param map    - The DungeonMap object.
 * @param graph  - The Graph object.
 */
void handle_user_input(const int choice, DungeonMap& map, Graph& graph) {
	switch (choice) {
        case 1: { // === Load a new map ===
        		std::string filename;
        		std::cout << "Enter the filename to load: ";
		        std::cin >> filename;
		        try {
                    // Load & verify the map, catching any exceptions.
		            map.load_map(filename);
		            map.verify_map();
		        } catch (const std::exception& e) {
		            std::cerr << "Error loading map: " << e.what() << '\n';
		        }
		        break;
        }

        case 2:   // === Perform DFS ===
            // TODO: Perform DFS 
            break;

        case 3:   // === Perform BFS ===
            // TODO: Perform BFS
            break;

        case 4:   // === Run A* algorithm ===
            // TODO: Run A* algorithm
            break;

        case 5: { // === Save current map === todo: make this make sense lmao. should just save 
            std::string filename;
            std::cout << "Enter the filename to save: ";
            std::cin >> filename;
            try {
                map.save_map(filename);
            } catch (const std::exception& e) {
                std::cerr << "Error saving map: " << e.what() << '\n';
            }
            break;
        }
        case 6:   // === Exit the program ===
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

int main() {
    // Create the Objects.
    DungeonMap map("maps/example_map.txt");
    Graph graph;

    // Main loop.
    while (true) {
        // === Render ===
        display_map(map);
        display_menu();

        // === Input ===
        int choice;
        std::cin >> choice;
        handle_user_input(choice, map, graph);
    }

    return 0;
}