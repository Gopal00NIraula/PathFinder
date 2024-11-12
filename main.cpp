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

    // Ensure start and end cells are open
    maze[0][0] &= ~(WALL_UP | WALL_LEFT);
    maze[rows - 1][cols - 1] &= ~(WALL_DOWN | WALL_RIGHT);

    std::cout << "Generated Maze (After Opening Start/End Cells):" << std::endl;
    printMaze(maze, rows, cols);


/*------DEBUG------------*/
    std::cout << "Initial Maze:" << std::endl;
    printMaze(maze, rows, cols);
/*------DEBUG------------*/

    // Step 2: Solve the maze using BFS
    PathfinderBFS pathfinder(rows, cols);
    bool pathFound = pathfinder.findPath(maze);

    // Step 3: Output the maze
    if (pathFound) {
        std::cout << "Path found! Saving maze with solution to maze.ps" << std::endl;
        printMaze(maze, rows, cols);

/*------DEBUG------------*/
if (maze[0][0] & (WALL_UP | WALL_LEFT)) {
    std::cout << "Error: Start cell (0, 0) is enclosed by walls." << std::endl;
}
if (maze[rows - 1][cols - 1] & (WALL_DOWN | WALL_RIGHT)) {
    std::cout << "Error: End cell (" << rows - 1 << ", " << cols - 1 << ") is enclosed by walls." << std::endl;
}
/*------DEBUG------------*/

    } else {
        std::cout << "No path found through the maze." << std::endl;
    }

    return 0;
}
