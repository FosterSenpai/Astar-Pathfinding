# Dungeon Map Pathfinder
Foster Rae GD1P02 Assignment 2

This project implements a dungeon map pathfinding application using Depth-First Search (DFS), Breadth-First Search (BFS), 
and A* algorithms. The application allows you to load a map, perform pathfinding, and save the map at any time.

## Features

- Load a dungeon map from a file
- Display the loaded map
- Perform DFS, BFS for the order of collecting items, ignoring any obstacles
- Run A* algorithm to find the shortest path from the start to the end
- Save the current map with the found path to a file

## Valid Map
A valid map is a text file with the following format:
- 20x20 grid
- 's' for start
- 'x' for end
- '.' for empty space
- 'w' for wall
- letters 'a' to 'j' for items (exactly 10 items)

A map must have exactly one start and one end point, and 10 items.  
Maps without valid paths are able to be loaded, but can only have BFS and DFS pathfinding algorithms applied.

## Using the Application
You will be presented with a menu with the following options:

1. Load a new map
2. Perform DFS
3. Perform BFS
4. Run A* algorithm
5. Save current map
6. Exit

### Loading a Map

To load a map, select option `1` and enter the filename of the map. The filename can be enclosed in quotation marks, which 
will be ignored.

### Performing Pathfinding

To perform pathfinding, select one of the algorithms (options `2`, `3`, or `4`). The application will display the map with 
the found path.

### Saving the Map

To save the current map with the found path, select option `5` and enter the filename. The map will be saved as a `.txt` file 
in the `maps/` directory. If the filename you provide does not end with `.txt`, it will be automatically appended.