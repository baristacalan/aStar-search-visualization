#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <utility>
#include <cmath>
#include <cfloat>
#include <cstring>
#include <set>
#include <stack>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>

// Constants representing the dimensions of the grid
constexpr int ROW = 10;
constexpr int COL = 10;

// Creating a shortcut for int, int pair type to store coordinates.
typedef std::pair<int, int> Pair;

// Creating a shortcut for pair<double, std::pair<int, int>> type.
typedef std::pair<double, std::pair<int, int>> pPair;

// A structure to hold parent_x, parent_y, f(full route), 
// gCost(Distance between current cell and start cell), 
// hCost(Heuristic, is the estimated cost from the current cell to the destination cell.), of the current cell.
struct Cell {
    int parent_x = -1, parent_y = -1; // Previous Row and Column index of a cell.
    double fCost = FLT_MAX, gCost = FLT_MAX, hCost = FLT_MAX; // fCost = gCost + hCost
    bool isPassed = false; // Indicator if the cell has been processed
};

// Function declarations with explanations
// x and y represents row and column respectively.


// A function to check whether given cell (row, col) is inside the grid or not.
bool isReachable(int x, int y);

// A function to check whether the given cell is blocked or not.
bool isNotBlocked(int grid[][COL], int x, int y);

// A function to check whether destination cell is reached or not.
bool isAtDestination(int x, int y, Pair dest);

// A function to calculate the 'hCost' heuristics with Manhattan Distance.
double calculateHCostValue(int x, int y, Pair dest);

// Function to calculate the time passed between given end-start.
double calculateTime(clock_t start, clock_t end);

// Function to generate a random grid with a given block ratio
void generateRandomGrid(int grid[][COL], double block_ratio);

// Function to print the grid with the given source and destination
void printGrid(int grid[][COL], Pair src, Pair dest);

// A function to track the path from destination to source.
void trackPath(Cell cellDetails[][COL], Pair dest, int grid[][COL]);

// A function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm.
void aStarSearch(int grid[][COL], Pair src, Pair dest);

// Clears the temporary path that the algorithm tried.
void clearTemporaryPath(int grid[][COL]);

// Function to clear the console screen.
void clearConsole();

// Starts the whole program which contains every function above.
void start(bool generate_random);

#endif // FUNCTIONS_H
