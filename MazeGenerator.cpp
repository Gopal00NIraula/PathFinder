#include "MazeGenerator.h"
#include "disjointSet.h"
#include "Sampler.h"
#include "pathfinder.h"

MazeGenerator::MazeGenerator(int rows, int cols) : rows(rows), cols(cols) {}

void MazeGenerator::generateMaze(uint8_t maze[][MAX_COLS], int extraWalls) {
    // Initialize maze with all walls
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            maze[r][c] = WALL_UP | WALL_RIGHT | WALL_DOWN | WALL_LEFT;
        }
    }

    // Create a disjoint set to track connected components
    DisjointSet ds(rows * cols);

    int numVerticalWalls = rows * (cols - 1);
    int numHorizontalWalls = (rows - 1) * cols;
    Sampler walls(numVerticalWalls + numHorizontalWalls);

    // Remove walls to form a spanning tree, ensuring connectivity between start and end
    while (ds.find(0) != ds.find((rows - 1) * cols + (cols - 1))) {
        int wall = walls.getSample();
        removeWall(wall, maze, ds, numVerticalWalls, numHorizontalWalls);
    }

    // Remove extra walls to introduce loops (optional)
    for (int i = 0; i < extraWalls; i++) {
        int wall = walls.getSample();
        removeWall(wall, maze, ds, numVerticalWalls, numHorizontalWalls);
    }
}

bool MazeGenerator::removeWall(int wall, uint8_t maze[][MAX_COLS], DisjointSet &ds, int numVerticalWalls, int numHorizontalWalls) {
    int r1, c1, r2, c2;

    if (wall < numVerticalWalls) { // Vertical wall
        r1 = wall / (cols - 1);
        c1 = wall % (cols - 1);
        r2 = r1;
        c2 = c1 + 1;
        if (ds.find(r1 * cols + c1) != ds.find(r2 * cols + c2)) {
            ds.join(r1 * cols + c1, r2 * cols + c2);
            maze[r1][c1] &= ~WALL_RIGHT;
            maze[r2][c2] &= ~WALL_LEFT;
            return true; // Wall removed successfully
        }
    } else { // Horizontal wall
        wall -= numVerticalWalls;
        r1 = wall / cols;
        c1 = wall % cols;
        r2 = r1 + 1;
        c2 = c1;
        if (ds.find(r1 * cols + c1) != ds.find(r2 * cols + c2)) {
            ds.join(r1 * cols + c1, r2 * cols + c2);
            maze[r1][c1] &= ~WALL_DOWN;
            maze[r2][c2] &= ~WALL_UP;
            return true; // Wall removed successfully
        }
    }
    return false; // Wall not removed (already connected)
}
