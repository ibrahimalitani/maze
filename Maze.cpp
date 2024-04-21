/**
 * Maze.cpp
 *
 * Implementation of the Maze class, which includes functionalities for maze generation,
 * visualization, and basic interaction. This file contains the definitions of the methods
 * declared in Maze.h.
 *
 */

#include "Maze.h"
#include <cstdlib>

/**
 * Cell constructor initializes a cell with specified coordinates, setting it as a wall and unvisited.
 * @param x The x-coordinate of the cell within the maze.
 * @param y The y-coordinate of the cell within the maze.
 */
Maze::Cell::Cell(int x, int y) : wall(true), visited(false), x(x), y(y) {}

/**
 * Maze constructor initializes a maze with specified width and height, and prepares the internal
 * grid representing the maze.
 * @param w The width of the maze.
 * @param h The height of the maze.
 */
Maze::Maze(int w, int h) : width(w), height(h), grid(h, vector<Cell>(w, Cell(0, 0))) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            grid[y][x].x = x;
            grid[y][x].y = y;
        }
    }
}

/**
 * Adds walls adjacent to a given cell to the wall list if they are not part of the maze yet.
 * This method is used during maze generation to identify potential walls to remove.
 * @param cell The cell whose adjacent walls are to be added.
 */
void Maze::addWalls(Cell* cell) {
    int x = cell->x;
    int y = cell->y;

    // Checks each adjacent cell and adds it to the wall list if it's not visited
    if (x > 0 && !grid[y][x - 1].visited) wallList.push_back(&grid[y][x - 1]);
    if (y > 0 && !grid[y - 1][x].visited) wallList.push_back(&grid[y - 1][x]);
    if (x < width - 1 && !grid[y][x + 1].visited) wallList.push_back(&grid[y][x + 1]);
    if (y < height - 1 && !grid[y + 1][x].visited) wallList.push_back(&grid[y + 1][x]);
}

/**
 * Generates the maze using a randomized version of Prim's algorithm. It starts with a single cell,
 * gradually adding cells to the maze by removing walls between visited and unvisited cells.
 */
void Maze::generate() {
    Cell* start = &grid[0][0];
        start->visited = true;
        start->wall = false;
        addWalls(start);

        while (!wallList.empty()) {
            int randIndex = rand() % wallList.size();
            Cell* current = wallList[randIndex];
            wallList.erase(wallList.begin() + randIndex);

            std::vector<Cell*> unvisitedNeighbors;
            if (current->y > 0 && !grid[current->y - 1][current->x].visited)
                unvisitedNeighbors.push_back(&grid[current->y - 1][current->x]);
            if (current->y < height - 1 && !grid[current->y + 1][current->x].visited)
                unvisitedNeighbors.push_back(&grid[current->y + 1][current->x]);
            if (current->x > 0 && !grid[current->y][current->x - 1].visited)
                unvisitedNeighbors.push_back(&grid[current->y][current->x - 1]);
            if (current->x < width - 1 && !grid[current->y][current->x + 1].visited)
                unvisitedNeighbors.push_back(&grid[current->y][current->x + 1]);

            if (!unvisitedNeighbors.empty()) {
                current->wall = false;
                current->visited = true;
                Cell* next = unvisitedNeighbors[rand() % unvisitedNeighbors.size()];
                next->wall = false;
                next->visited = true;
                addWalls(current);
                addWalls(next);
            }
        }
}

/**
 * Prints the maze to the standard output, representing walls with 'X' and free spaces with ' '.
 */
/**
 * Prints the maze to the standard output with ASCII art representation.
 * Walls are represented by '#', and empty paths are represented by ' '.
 */
void Maze::print() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << (grid[y][x].wall ? 'X' : ' ') << ' ';
        }
        std::cout << std::endl;
    }
}


/** Returns the width of the maze. */
int Maze::getWidth() const { return width; }

/** Returns the height of the maze. */
int Maze::getHeight() const { return height; }

/**
 * Checks if the specified cell is a wall.
 * @param x X-coordinate of the cell to check.
 * @param y Y-coordinate of the cell to check.
 * @return True if the cell is a wall, otherwise false.
 */
bool Maze::isWall(int x, int y) const { return grid[y][x].wall; }

/**
 * Sets specified cells as the start and end points of the maze by clearing the walls at those points.
 * @param startX X-coordinate of the start cell.
 * @param startY Y-coordinate of the start cell.
 * @param endX X-coordinate of the end cell.
 * @param endY Y-coordinate of the end cell.
 */
void Maze::setStartAndEndPoint(int startX, int startY, int endX, int endY) {
    grid[startY][startX].wall = false;
    grid[endY][endX].wall = false;
}
