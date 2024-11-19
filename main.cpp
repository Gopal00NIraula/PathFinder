#include <iostream>
#include <string>
#include "MazeGenerator.h"
#include "PathfinderBFS.h"
#include "pathfinder.h"

int main(int argc, char* argv[]) {
    // Check if the required number of arguments is provided
    if (argc != 4) {
        std::cerr << "Usage: ./project3 <rows> <cols> <extraWalls>" << std::endl;
        return 1;
    }

    try {
        // Parse command-line arguments using C++'s std::stoi
        int rows = std::stoi(argv[1]);
        int cols = std::stoi(argv[2]);
        int extraWalls = std::stoi(argv[3]);

        // Validate input values
        if (rows < 1 || rows > 50 || cols < 1 || cols > 50 || extraWalls < 0) {
            std::cerr << "Invalid input. Rows and columns must be between 1 and 50. Extra walls must be non-negative." << std::endl;
            return 1;
        }

        // Initialize the maze
        uint8_t maze[MAX_ROWS][MAX_COLS] = {0};
        MazeGenerator mazeGen(rows, cols);
        mazeGen.generateMaze(maze, extraWalls);

        // Open the start cell and close the bottom-right boundary
        maze[0][0] &= ~(WALL_UP | WALL_LEFT);
        maze[rows - 1][cols - 1] |= WALL_DOWN | WALL_RIGHT;

        std::cout << "Generated Maze (After Opening Start/End Cells):" << std::endl;
        printMaze(maze, rows, cols);

        // Find the path through the maze
        PathfinderBFS pathfinder(rows, cols);
        bool pathFound = pathfinder.findPath(maze);

        if (pathFound) {
            std::cout << "Path found!" << std::endl;
            printMaze(maze, rows, cols);
        } else {
            std::cout << "No path found." << std::endl;
        }
    } catch (const std::invalid_argument&) {
        std::cerr << "Error: All arguments must be valid integers." << std::endl;
        return 1;
    } catch (const std::out_of_range&) {
        std::cerr << "Error: Input values are out of range." << std::endl;
        return 1;
    }

    return 0;
}
