#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <cstdint>
#include <vector>
#include <random>
#include "disjointSet.h"
#include "pathfinder.h" // For maze cell constants and MAX_ROWS/COLS

class MazeGenerator {
public:
    MazeGenerator(int rows, int cols);
    void generateMaze(uint8_t maze[][MAX_COLS]);

private:
    int rows;
    int cols;
    DisjointSet disjointSet;

    void initializeWalls(std::vector<std::pair<int, int>>& walls);
    void removeWalls(uint8_t maze[][MAX_COLS], std::vector<std::pair<int, int>>& walls);
    int cellIndex(int row, int col) const;
};

#endif // MAZEGENERATOR_H
