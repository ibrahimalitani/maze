/**
 * Maze.h
 *
 * Represents a maze structure with functionalities for maze generation, visualization,
 * and querying. The maze is generated using randomized algorithms and can be navigated
 * by pathfinding algorithms. The class supports setting specific start and end points
 * by clearing walls at specified coordinates, allowing for integration with pathfinding
 * algorithms like A* to find paths through the maze.
 *
 */

#ifndef PROJECTPHASEONE_MAZE_H
#define PROJECTPHASEONE_MAZE_H

#include <iostream>
#include <vector>

using namespace std;

class Maze {
private:
    /**
     * Represents a single cell within the maze, indicating whether the cell is a wall,
     * if it has been visited during generation, and its coordinates.
     */
    struct Cell {
        bool wall; // Indicates if the cell is a wall.
        bool visited; // Used during maze generation to mark visited cells.
        int x, y; // Coordinates of the cell within the maze.

        /** Constructor for a cell.
         * @param x X-coordinate of the cell.
         * @param y Y-coordinate of the cell.
         */
        Cell(int x, int y);
    };

    vector<vector<Cell>> grid; // 2D grid representing the entire maze.
    vector<Cell*> wallList; // List of walls that can be turned into paths during generation.
    int width, height; // Dimensions of the maze.

    /** Adds neighboring walls of a cell to the wall list during maze generation.
     * @param cell Pointer to the cell whose walls are to be added.
     */
    void addWalls(Cell* cell);

public:
    /** Constructor for the Maze class.
     * @param w Width of the maze.
     * @param h Height of the maze.
     */
    Maze(int w, int h);

    /** Generates the maze using randomized algorithms. */
    void generate();

    /** Prints the maze to the console. */
    void print();

    /** Gets the width of the maze.
     * @return The width of the maze.
     */
    int getWidth() const;

    /** Gets the height of the maze.
     * @return The height of the maze.
     */
    int getHeight() const;

    /** Checks if a specified cell is a wall.
     * @param x X-coordinate of the cell to check.
     * @param y Y-coordinate of the cell to check.
     * @return True if the cell is a wall, false otherwise.
     */
    bool isWall(int x, int y) const;

    /** Sets the start and end points of the maze by clearing the corresponding cells.
     * @param startX X-coordinate of the start cell.
     * @param startY Y-coordinate of the start cell.
     * @param endX X-coordinate of the end cell.
     * @param endY Y-coordinate of the end cell.
     */
    void setStartAndEndPoint(int startX, int startY, int endX, int endY);
};

#endif //PROJECTPHASEONE_MAZE_H
