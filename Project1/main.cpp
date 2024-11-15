#include <iostream>
#include <limits>
#include "c_dungeon_map.h"
#include "c_graph.h"

// Finally have a good clear console function.
void clear_console() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void display_map(const c_dungeon_map& map) {
    map.display_map();
}

void display_menu() {
    std::cout << "\n\n1. Load a new map\n";
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
void handle_user_input(const int choice, c_dungeon_map& map, c_graph& graph) {
    switch (choice) {
        case 1: { // === Load a new map ===
            std::string filename;
            std::cout << "Enter the filename to load: ";
            std::getline(std::cin >> std::ws, filename); // Read the filename with leading whitespace ignored
            std::cout << "Attempting to load file: " << filename << std::endl;
            try {
                // Load & verify the map, catching any exceptions.
                map.load_map(filename);
                std::cout << "Map loaded and verified successfully.\n";
                graph = map.to_graph(); // Convert the map to a graph
            } catch (const std::exception& e) {
                std::cerr << "Error loading map: " << e.what() << '\n';
                map = c_dungeon_map(); // Load an empty map
                graph = map.to_graph(); // Convert the empty map to a graph
            }
            break;
        }

        case 2: { // === Perform DFS ===
            try {
                auto start_pos = map.get_start_node();
                Node start_node = graph.get_node(start_pos.first, start_pos.second);
                graph.dfs(start_node);
            } catch (const std::exception& e) {
                std::cerr << "Error performing DFS: " << e.what() << '\n';
            }
            break;
        }

        case 3: { // === Perform BFS ===
            try {
                auto start_pos = map.get_start_node();
                Node start_node = graph.get_node(start_pos.first, start_pos.second);
                graph.bfs(start_node);
            } catch (const std::exception& e) {
                std::cerr << "Error performing BFS: " << e.what() << '\n';
            }
            break;
        }

        case 4: { // === Run A* algorithm ===
            try {
                auto start_pos = map.get_start_node();
                auto end_pos = map.get_end_node();
                Node start_node = graph.get_node(start_pos.first, start_pos.second);
                Node end_node = graph.get_node(end_pos.first, end_pos.second);
                graph.a_star(start_node, end_node);
            } catch (const std::exception& e) {
                std::cerr << "Error running A* algorithm: " << e.what() << '\n';
            }
            break;
        }

        case 5: { // === Save current map ===
            std::string save_filename;
            std::cout << "Enter the filename to save as: ";
            std::getline(std::cin >> std::ws, save_filename); // Read the filename with leading whitespace ignored
            try {
                map.save_map(save_filename);
                std::cout << "Map saved successfully as " << save_filename << ".\n";
            } catch (const std::exception& e) {
                std::cerr << "Error saving map: " << e.what() << '\n';
            }
            break;
        }

        case 6:   // === Exit the program ===
            std::cout << "Exiting program.\n";
            exit(0);

        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

int main() {
    try {
        // Create the Objects.
        c_dungeon_map map; // Initialize with an empty map
        c_graph graph;

        // Main loop.
        while (true) {
            // === Render ===
            display_map(map);
            display_menu();

            // === Input ===
            int choice;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            // Check if the input is valid
            if (std::cin.fail()) {
                // Clear the error flag
                std::cin.clear();
                // Ignore the rest of the input buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            // Clear the input buffer to remove any leftover characters.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            handle_user_input(choice, map, graph);
        }
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred.\n";
        return 2;
    }

    return 0;
}