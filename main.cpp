#include <iostream>
#include <cstdlib>
#include "MazeGenerator.h"
#include "PathfinderBFS.h"
#include "pathfinder.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./Project3 <rows> <cols> <extraWalls>" << std::endl;
        return 1;
    }

    int rows = std::stoi(argv[1]);
    int cols = std::stoi(argv[2]);
    int extraWalls = std::stoi(argv[3]);

    if (rows < 1 || rows > 50 || cols < 1 || cols > 50 || extraWalls < 0) {
        std::cerr << "Invalid input. Rows and columns must be between 1 and 50. Extra walls must be non-negative." << std::endl;
        return 1;
    }

    uint8_t maze[MAX_ROWS][MAX_COLS] = {0};
    MazeGenerator mazeGen(rows, cols);
    mazeGen.generateMaze(maze, extraWalls);

    maze[0][0] &= ~(WALL_UP | WALL_LEFT);
    maze[rows - 1][cols - 1] &= ~(WALL_DOWN | WALL_RIGHT);

    std::cout << "Generated Maze (After Opening Start/End Cells):" << std::endl;
    printMaze(maze, rows, cols);

    PathfinderBFS pathfinder(rows, cols);
    bool pathFound = pathfinder.findPath(maze);

    if (pathFound) {
        std::cout << "Path found!" << std::endl;
        printMaze(maze, rows, cols);
    } else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}
