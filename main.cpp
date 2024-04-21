/**
 * main.cpp
 *
 * Main driver program that demonstrates generating a maze and finding a path through it
 * using the A* algorithm. The maze is generated with specified dimensions, and a path is
 * calculated from a start point to an end point within this maze. The program outputs the
 * generated maze and the path found to the console.
 */

#include "Maze.h"
#include "AStar.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SFML/graphics.hpp>

using namespace std;
void drawMaze(sf::RenderWindow& window, const Maze& maze) {
    int cellSize = 30; // Size of each maze cell
    sf::RectangleShape wall(sf::Vector2f(cellSize, cellSize));
    wall.setFillColor(sf::Color::Black);

    int width = maze.getWidth();
    int height = maze.getHeight();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (maze.isWall(x, y)) {
                wall.setPosition(x * cellSize, y * cellSize);
                window.draw(wall);
            }
        }
    }
}

// Function to draw the path on the SFML window
void drawPath(sf::RenderWindow& window, const std::vector<std::pair<int, int>>& path) {
    if (path.empty()) return;

    int cellSize = 30; // Size of each maze cell
    sf::VertexArray lines(sf::LinesStrip, path.size());

    for (size_t i = 0; i < path.size(); ++i) {
        lines[i].position = sf::Vector2f(path[i].first * cellSize + cellSize / 2, path[i].second * cellSize + cellSize / 2);
        lines[i].color = sf::Color::Red;
    }

    window.draw(lines);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maze");
    // Initialize the random number generator.
    srand(static_cast<unsigned>(time(nullptr)));

    // Create and generate a maze of specified dimensions.
    Maze maze(20, 20);
    maze.generate();

    // Define the start and end points for the pathfinding within the maze.
    int startX = 1; // Start cell position.
    int startY = 1; // Start cell position.
    int endX = maze.getWidth() - 2; // End cell position, ensuring it is within the maze boundaries.
    int endY = maze.getHeight() - 2; // End cell position, ensuring it is within the maze boundaries.

    // Set the start and end points in the maze, clearing any walls at these positions.
    maze.setStartAndEndPoint(startX, startY, endX, endY);

    // Initialize the A* pathfinding algorithm with the generated maze.
    AStar aStar(maze);

    // Find and print the path from the start to the end point using A* algorithm.
    vector<pair<int, int>> path = aStar.findPath(startX, startY, endX, endY);

    // Output the path found to the console, formatting the output for readability.

       while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Draw the maze and the path
        drawMaze(window, maze);
        drawPath(window, path);

        window.display();
    }
    return 0;
}
