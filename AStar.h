/**
 * AStar.h
 *
 *
 * The AStar class implements the A* pathfinding algorithm to find the shortest path
 * from a start point to a goal point within a maze. It utilizes the Maze class to
 * interact with the maze structure, querying for walls and dimensions. The A* algorithm
 * combines features of Dijkstra's algorithm (which focuses on minimizing the distance
 * from the start node) and a heuristic to estimate the distance to the goal, thereby
 * efficiently finding the shortest path.
 *
 * Author: [Student Name]
 * Course: [Course Name]
 *
 * Created by [Author] on 24-Mar-24.
 */

#ifndef PROJECTPHASEONE_ASTAR_H
#define PROJECTPHASEONE_ASTAR_H

#include "Maze.h"
#include <vector>
#include <utility>

class AStar {
private:
    Maze& maze; /** Reference to the Maze object to navigate.*/

    /** 2D vector representing the cost to reach each cell from the start.
     * Initialized with INT_MAX to indicate unvisited cells. */
    std::vector<std::vector<int>> cost;

    /** 2D vector storing the parent cell for each cell in the path.
     * Used for path reconstruction. */
    std::vector<std::vector<std::pair<int, int>>> parent;

    /** 2D vector indicating whether a cell is currently in the priority queue. */
    std::vector<std::vector<bool>> inQueue;

    /** Private method to calculate the heuristic value (estimated cost) from a cell
     * to the goal. Typically, this is the Manhattan distance for grid-based pathfinding. */
    int heuristic(int x1, int y1, int x2, int y2);

public:
    /** Constructor that initializes the AStar algorithm with a reference to a Maze.
     * @param maze: Reference to the Maze object to be navigated. */
    AStar(Maze& maze);

    /** Finds the shortest path from a start point to a goal point within the maze.
     * @param startX: The x-coordinate of the start cell.
     * @param startY: The y-coordinate of the start cell.
     * @param goalX: The x-coordinate of the goal cell.
     * @param goalY: The y-coordinate of the goal cell.
     * @return: A vector of cell coordinates (pairs of int) representing the path
     * from start to goal, inclusive. If no path is found, the returned vector is empty. */
    std::vector<std::pair<int, int>> findPath(int startX, int startY, int goalX, int goalY);
};

#endif //PROJECTPHASEONE_ASTAR_H
