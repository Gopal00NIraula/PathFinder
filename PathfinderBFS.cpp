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

        /*------DEBUG------------*/
        std::cout << "Visiting Cell: (" << current.row << ", " << current.col << ")" << std::endl;
        /*------DEBUG------------*/

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

/*------DEBUG------------*/
    std::cout << "Checking move to (" << row << ", " << col << "): ";

if (row < 0 || row >= rows || col < 0 || col >= cols) {
    std::cout << "Out of bounds." << std::endl;
    return false;
}
if (visited[row][col]) {
    std::cout << "Already visited." << std::endl;
    return false;
}

// Print the wall status of the current and next cell
std::cout << "Current cell walls: "
          << "UP: " << (maze[row][col] & WALL_UP)
          << " RIGHT: " << (maze[row][col] & WALL_RIGHT)
          << " DOWN: " << (maze[row][col] & WALL_DOWN)
          << " LEFT: " << (maze[row][col] & WALL_LEFT) << std::endl;

// Check wall collisions
if (row > 0 && (maze[row][col] & WALL_UP) && (maze[row - 1][col] & WALL_DOWN)) {
    std::cout << "Blocked by upper wall." << std::endl;
    return false;
}
if (row < rows - 1 && (maze[row][col] & WALL_DOWN) && (maze[row + 1][col] & WALL_UP)) {
    std::cout << "Blocked by lower wall." << std::endl;
    return false;
}
if (col > 0 && (maze[row][col] & WALL_LEFT) && (maze[row][col - 1] & WALL_RIGHT)) {
    std::cout << "Blocked by left wall." << std::endl;
    return false;
}
if (col < cols - 1 && (maze[row][col] & WALL_RIGHT) && (maze[row][col + 1] & WALL_LEFT)) {
    std::cout << "Blocked by right wall." << std::endl;
    return false;
}

std::cout << "Move valid." << std::endl;
return true;

/*------DEBUG------------*/

    return true;
}
