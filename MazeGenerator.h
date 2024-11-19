#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include <cstdint>
#include "disjointSet.h"
#include "Sampler.h"
#include "pathfinder.h" // Include this for MAX_COLS definition

class MazeGenerator {
public:
    MazeGenerator(int rows, int cols);
    void generateMaze(uint8_t maze[][MAX_COLS], int extraWalls);

private:
    int rows;
    int cols;
    bool removeWall(int wall, uint8_t maze[][MAX_COLS], DisjointSet &ds, int numVerticalWalls, int numHorizontalWalls);
};

#endif // MAZE_GENERATOR_H
