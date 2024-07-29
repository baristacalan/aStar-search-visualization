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

constexpr int ROW = 10;
constexpr int COL = 10;

typedef std::pair<int, int> Pair; // Creating a shortcut for int, int pair type.

typedef std::pair<double, std::pair<int, int>> pPair; // Creating a shortcut for pair<double, pair<int, int>> type.


// A structure to hold parent_x, parent_y, f(full route), 
// gCost(Distance between current cell and start cell), 
// hCost(Heuristic, is the estimated cost from the current cell to the destination cell.), of each cell.

struct Cell {
    
    int parent_x, parent_y; // Previous Row and Column index of a cell.

    double fCost, gCost, hCost; // fCost = gCost + hCost

    bool isPassed = false;
};


bool isReachable(int row, int col);                        // A function to check whether given cell (row, col) is inside the grid or not.
bool isNotBlocked(int grid[][COL], int row, int col);     // A function to check whether the given cell is blocked or not.
bool isDestination(int row, int col, Pair dest);         // A function to check whether destination cell is reached or not.                                                                                              //has been reached or not.


double calculateHCostValue(int row, int col, Pair dest);  // A function to calculate the 'hCost' heuristics with Manhattan Distance.


void printGrid(int grid[][COL], Pair src, Pair dest);
void trackPath(Cell cellDetails[][COL], Pair dest, int grid[][COL]); // A function to track the path from destination to source.
void aStarSearch(int grid[][COL], Pair src, Pair dest); // A Function to find the shortest path between
                                                        // a given source cell to a destination cell according
                                                        // to A* Search Algorithm.

void clearTemporaryPath(int grid[][COL]); //Clears the temporary path that the algorithm tried.
void clearConsole();

#endif //FUNCTIONS_H