#include "MazeGenerator.h"
#include <algorithm>

MazeGenerator::MazeGenerator(int rows, int cols)
    : rows(rows), cols(cols), disjointSet(rows * cols) {}

void MazeGenerator::generateMaze(uint8_t maze[][MAX_COLS]) {
    std::vector<std::pair<int, int>> walls;
    initializeWalls(walls);
    std::shuffle(walls.begin(), walls.end(), std::mt19937{std::random_device{}()});

    // Initialize all cells as enclosed by walls
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maze[i][j] = WALL_UP | WALL_RIGHT | WALL_DOWN | WALL_LEFT;
        }
    }

    removeWalls(maze, walls);
}

void MazeGenerator::initializeWalls(std::vector<std::pair<int, int>>& walls) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (j + 1 < cols) // Right wall
                walls.emplace_back(cellIndex(i, j), cellIndex(i, j + 1));
            if (i + 1 < rows) // Down wall
                walls.emplace_back(cellIndex(i, j), cellIndex(i + 1, j));
        }
    }
}

void MazeGenerator::removeWalls(uint8_t maze[][MAX_COLS], std::vector<std::pair<int, int>>& walls) {
    for (const auto& wall : walls) {
        int cell1 = wall.first;
        int cell2 = wall.second;

        if (disjointSet.find(cell1) != disjointSet.find(cell2)) {
            int r1 = cell1 / cols, c1 = cell1 % cols;
            int r2 = cell2 / cols, c2 = cell2 % cols;

            if (r1 == r2) { // Horizontal wall
                if (c1 < c2) {
                    maze[r1][c1] &= ~WALL_RIGHT;
                    maze[r2][c2] &= ~WALL_LEFT;
                } else {
                    maze[r1][c1] &= ~WALL_LEFT;
                    maze[r2][c2] &= ~WALL_RIGHT;
                }
            } else if (c1 == c2) { // Vertical wall
                if (r1 < r2) {
                    maze[r1][c1] &= ~WALL_DOWN;
                    maze[r2][c2] &= ~WALL_UP;
                } else {
                    maze[r1][c1] &= ~WALL_UP;
                    maze[r2][c2] &= ~WALL_DOWN;
                }
            }

            disjointSet.join(cell1, cell2);

            /*------DEBUG------------*/
            std::cout << "Removed wall between (" << r1 << ", " << c1 << ") and (" << r2 << ", " << c2 << ")" << std::endl;
            /*------DEBUG------------*/
        }
    }
}

int MazeGenerator::cellIndex(int row, int col) const {
    return row * cols + col;
}
