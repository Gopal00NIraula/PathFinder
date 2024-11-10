#include <iostream>
#include "MazeGenerator.h"
#include "PathfinderBFS.h"
#include "pathfinder.h"  // For printMaze function and maze constants

int main() {
    const int rows = 20; // Customize as needed
    const int cols = 20;

    // Step 1: Generate the maze
    uint8_t maze[MAX_ROWS][MAX_COLS] = {0};
    MazeGenerator mazeGen(rows, cols);
    mazeGen.generateMaze(maze);

    // Step 2: Solve the maze using BFS
    PathfinderBFS pathfinder(rows, cols);
    bool pathFound = pathfinder.findPath(maze);

    // Step 3: Output the maze
    if (pathFound) {
        std::cout << "Path found! Saving maze with solution to maze.ps" << std::endl;
        printMaze(maze, rows, cols);
    } else {
        std::cout << "No path found through the maze." << std::endl;
    }

    return 0;
}
