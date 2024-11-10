#ifndef PATHFINDERBFS_H
#define PATHFINDERBFS_H

#include <cstdint>
#include <queue>
#include "pathfinder.h"  // For maze cell constants and MAX_ROWS/COLS

class PathfinderBFS {
public:
    PathfinderBFS(int rows, int cols);
    bool findPath(uint8_t maze[][MAX_COLS]);

private:
    int rows;
    int cols;

    struct Cell {
        int row;
        int col;
    };

    void markPath(uint8_t maze[][MAX_COLS], const std::vector<Cell>& path);
    bool isValidMove(int row, int col, uint8_t maze[][MAX_COLS], uint8_t visited[][MAX_COLS]);
};

#endif // PATHFINDERBFS_H