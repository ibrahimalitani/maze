/**
 * AStar.cpp
 *
 * Implementation of the AStar class, which utilizes the A* algorithm to find the shortest path
 * through a maze from a start point to an end point.
 *
 */

#include "AStar.h"
#include <queue>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

/**
 * Constructor for the AStar class.
 *
 * @param maze Reference to a Maze object. This is the maze through which the A* algorithm
 * will search for a path. The maze provides the necessary interface for querying wall positions
 * and dimensions.
 */
AStar::AStar(Maze& maze) : maze(maze) {}

/**
 * Calculates the heuristic value used in the A* algorithm. This implementation uses
 * the Manhattan distance between two points as the heuristic, suitable for grid-based
 * pathfinding where diagonal movement is not allowed.
 *
 * @param x1 X-coordinate of the first point.
 * @param y1 Y-coordinate of the first point.
 * @param x2 X-coordinate of the second point.
 * @param y2 Y-coordinate of the second point.
 * @return The Manhattan distance between the two points.
 */
int AStar::heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

/**
 * Finds the shortest path from a specified start point to a specified end point
 * within the maze, using the A* pathfinding algorithm. The path is represented as
 * a vector of cell coordinates (pairs of integers).
 *
 * @param startX The X-coordinate of the starting cell.
 * @param startY The Y-coordinate of the starting cell.
 * @param goalX The X-coordinate of the goal cell.
 * @param goalY The Y-coordinate of the goal cell.
 * @return A vector of cell coordinates (pairs of int) representing the path from
 * the start cell to the goal cell, inclusive. If no path is found, returns an empty vector.
 */
vector<pair<int, int>> AStar::findPath(int startX, int startY, int goalX, int goalY) {
    int width = maze.getWidth();
    int height = maze.getHeight();

    cost = vector<vector<int>>(height, vector<int>(width, INT_MAX));
    parent = vector<vector<pair<int, int>>>(height, vector<pair<int, int>>(width, {-1, -1}));
    inQueue = vector<vector<bool>>(height, vector<bool>(width, false));

    auto cmp = [&](const pair<int, int>& a, const pair<int, int>& b) {
        int f1 = cost[a.second][a.first] + heuristic(a.first, a.second, goalX, goalY);
        int f2 = cost[b.second][b.first] + heuristic(b.first, b.second, goalX, goalY);
        return f1 > f2;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> frontier(cmp);

    cost[startY][startX] = 0;
    frontier.push({startX, startY});
    inQueue[startY][startX] = true;

    while (!frontier.empty()) {
        auto current = frontier.top();
        frontier.pop();
        int x = current.first;
        int y = current.second;
        inQueue[y][x] = false;

        if (x == goalX && y == goalY) {
            break; // Found the path to the goal.
        }

        vector<pair<int, int>> neighbors = {
                {x, y - 1}, {x + 1, y}, {x, y + 1}, {x - 1, y}
        };

        for (const auto& next : neighbors) {
            int nx = next.first, ny = next.second;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height && !maze.isWall(nx, ny)) {
                int newCost = cost[y][x] + 1; // Assuming uniform cost for all movements.

                if (newCost < cost[ny][nx]) {
                    cost[ny][nx] = newCost;
                    parent[ny][nx] = {x, y};
                    if (!inQueue[ny][nx]) {
                        frontier.push({nx, ny});
                        inQueue[ny][nx] = true;
                    }
                }
            }
        }
    }

    vector<pair<int, int>> path;
    for (pair<int, int> at = {goalX, goalY}; at != make_pair(-1, -1); at = parent[at.second][at.first]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());

    return path; // Return the reconstructed path from start to goal.
}
