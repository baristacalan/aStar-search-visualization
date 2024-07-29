#include "functions.h"

int main() {

    /* Description of the Grid-
     1--> The cell is not blocked
     0--> The cell is blocked    */

    std::cout << "Welcome to the A* path finding visualization.\n";
    std::cout << "Here is the grid bellow. S and D are temporarily set.\n";
    int grid[ROW][COL]
        = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 0, 1, 1, 0, 0 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 },
            { 1, 1, 1, 1, 0, 0, 1, 0, 1, 1 } };

    Pair src = std::make_pair(0, 0);
    Pair dest = std::make_pair(9, 9);

    printGrid(grid, src, dest);
    std::cout << "\n";

    int x_src = 0, y_src = 0, x_dest = 0, y_dest = 0;
    bool valid_coordinates = false;

    while (!valid_coordinates) {

        //Getting the input for row of source.

        std::cout << "Enter x of source [0, 9]: ";
        std::cin >> x_src;

        //Getting the input for column of source.
        std::cout << "Enter y of source [0, 9]: ";
        std::cin >> y_src;

        //Getting the input for row of destination.
        std::cout << "Enter x of destination [0, 9]: ";
        std::cin >> x_dest;

        //Getting the input for row of destination.
        std::cout << "Enter y of destination [0, 9]: ";
        std::cin >> y_dest;

        //Creating the pairs of source and destination locations.
        src = std::make_pair(x_src, y_src);
        dest = std::make_pair(x_dest, y_dest);

        if (!isReachable(src.first, src.second) || !isReachable(dest.first, dest.second)) {
            std::cout << "Source or destination is out of range! Try again.\n";
        }
        else if (!isNotBlocked(grid, src.first, src.second) || !isNotBlocked(grid, dest.first, dest.second)) {
            std::cout << "Source or destination is blocked! Try again.\n";
        }
        else if (isDestination(src.first, src.second, dest)) {
            printf_s("Destination and source are the same. --> (%d, %d) Try again.\n", src.first, src.second);
        }
        else {
            std::cout << "Coordinates valid. Source and Destination are set.\n";
            valid_coordinates = true;
        }
    }

    printGrid(grid, src, dest);
    //std::cin.ignore();
    std::cout << "Press Enter to start...\n";
    std::cin.ignore();
    std::cin.get();

    aStarSearch(grid, src, dest);
    std::cin.get(); //Blocks the instant shutdown when ran on .exe

    return 0;
}

