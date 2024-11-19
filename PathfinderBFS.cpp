#include "PathfinderBFS.h"

PathfinderBFS::PathfinderBFS(int rows, int cols) : rows(rows), cols(cols) {}

bool PathfinderBFS::findPath(uint8_t maze[][MAX_COLS]) {
    std::queue<Cell> bfsQueue;
    std::vector<Cell> parent(rows * cols, {-1, -1}); // Parent tracker for the path
    uint8_t visited[MAX_ROWS][MAX_COLS] = {0};

    Cell start = {0, 0};
    Cell end = {rows - 1, cols - 1};

    bfsQueue.push(start);
    visited[start.row][start.col] = 1;

    while (!bfsQueue.empty()) {
        Cell current = bfsQueue.front();
        bfsQueue.pop();

        if (current.row == end.row && current.col == end.col) {
            // Trace back the shortest path using the parent tracker
            std::vector<Cell> path;
            Cell trace = current;
            while (!(trace.row == -1 && trace.col == -1)) {
                path.push_back(trace);
                trace = parent[trace.row * cols + trace.col];
            }
            markPath(maze, path);
            return true; // Path found
        }

        // Check adjacent cells
        int rowMoves[] = {-1, 1, 0, 0};
        int colMoves[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; ++i) {
            int newRow = current.row + rowMoves[i];
            int newCol = current.col + colMoves[i];

            if (isValidMove(newRow, newCol, maze, visited, current, i)) {
                visited[newRow][newCol] = 1;
                bfsQueue.push({newRow, newCol});
                parent[newRow * cols + newCol] = current; // Set parent
            }
        }
    }

    return false; // No path found
}

void PathfinderBFS::markPath(uint8_t maze[][MAX_COLS], const std::vector<Cell>& path) {
    for (const auto& cell : path) {
        maze[cell.row][cell.col] |= VISITED; // Mark only the shortest path
    }
}

bool PathfinderBFS::isValidMove(int row, int col, uint8_t maze[][MAX_COLS], uint8_t visited[][MAX_COLS], const Cell& current, int direction) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) return false;
    if (visited[row][col]) return false;

    // Check walls based on direction
    if (direction == 0 && (maze[current.row][current.col] & WALL_UP)) return false;     // Moving up
    if (direction == 1 && (maze[current.row][current.col] & WALL_DOWN)) return false;   // Moving down
    if (direction == 2 && (maze[current.row][current.col] & WALL_LEFT)) return false;   // Moving left
    if (direction == 3 && (maze[current.row][current.col] & WALL_RIGHT)) return false;  // Moving right

    return true;
}
