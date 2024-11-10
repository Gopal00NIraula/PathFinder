#include "PathfinderBFS.h"

PathfinderBFS::PathfinderBFS(int rows, int cols)
    : rows(rows), cols(cols) {}

bool PathfinderBFS::findPath(uint8_t maze[][MAX_COLS]) {
    std::queue<Cell> bfsQueue;
    std::vector<Cell> path;
    uint8_t visited[MAX_ROWS][MAX_COLS] = {0};

    Cell start = {0, 0};
    Cell end = {rows - 1, cols - 1};

    bfsQueue.push(start);
    visited[start.row][start.col] = 1;

    while (!bfsQueue.empty()) {
        Cell current = bfsQueue.front();
        bfsQueue.pop();
        path.push_back(current);

        if (current.row == end.row && current.col == end.col) {
            markPath(maze, path);
            return true; // Path found
        }

        // Check adjacent cells in all four directions
        int rowMoves[] = {-1, 1, 0, 0};
        int colMoves[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; ++i) {
            int newRow = current.row + rowMoves[i];
            int newCol = current.col + colMoves[i];

            if (isValidMove(newRow, newCol, maze, visited)) {
                visited[newRow][newCol] = 1;
                bfsQueue.push({newRow, newCol});
            }
        }
    }

    return false; // No path found
}

void PathfinderBFS::markPath(uint8_t maze[][MAX_COLS], const std::vector<Cell>& path) {
    for (const auto& cell : path) {
        maze[cell.row][cell.col] |= VISITED;
    }
}

bool PathfinderBFS::isValidMove(int row, int col, uint8_t maze[][MAX_COLS], uint8_t visited[][MAX_COLS]) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) return false;
    if (visited[row][col]) return false;

    // Check if the move is allowed by checking the walls
    if (row > 0 && (maze[row][col] & WALL_UP) && (maze[row - 1][col] & WALL_DOWN)) return false;
    if (row < rows - 1 && (maze[row][col] & WALL_DOWN) && (maze[row + 1][col] & WALL_UP)) return false;
    if (col > 0 && (maze[row][col] & WALL_LEFT) && (maze[row][col - 1] & WALL_RIGHT)) return false;
    if (col < cols - 1 && (maze[row][col] & WALL_RIGHT) && (maze[row][col + 1] & WALL_LEFT)) return false;

    return true;
}
