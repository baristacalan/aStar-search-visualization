#include "functions.h"

// Check if the given cell is within the grid boundaries
bool isReachable(int x, int y) {
    return (x >= 0) && (x < ROW) && (y >= 0) && (y < COL);
}

// Check if the given cell is not blocked
bool isNotBlocked(int grid[][COL], int x, int y) {
    return grid[x][y] == 1;
}

// Check if the given cell is the destination
bool isAtDestination(int x, int y, Pair dest) {
    return dest.first == x && dest.second == y;
}

// Calculate the heuristic cost from the current cell to the destination
double calculateHCostValue(int x, int col, Pair dest) {
    return static_cast<double>(sqrt(pow(x - dest.first, 2) + pow(col - dest.second, 2)));
}

// Trace the path from the destination to the source
void trackPath(Cell cells[][COL], Pair dest, int grid[][COL]) {
    std::cout << "The path is: ";
    int x = dest.first;
    int y = dest.second;

    std::stack<Pair> Path;

    // Trace the path back to the source
    while (!(cells[x][y].parent_x == x && cells[x][y].parent_y == y)) {
        Path.push(std::make_pair(x, y));
        int temp_row = cells[x][y].parent_x;
        int temp_col = cells[x][y].parent_y;
        x = temp_row;
        y = temp_col;
    }
    Path.push(std::make_pair(x, y));

    // Mark the path on the grid
    while (!Path.empty()) {
        Pair p = Path.top();
        Path.pop();
        grid[p.first][p.second] = 2; // Mark the path in the grid
        printf_s("-->(%d, %d)", p.first, p.second);
    }
    return;
}

// Print the grid with the source and destination marked
void printGrid(int grid[][COL], Pair src, Pair dest) {
    std::cout << "\n";
    for (int x = 0; x < ROW; x++) {
        for (int y = 0; y < COL; y++) {
            if (x == src.first && y == src.second)
                std::cout << "\033[35mS  \033[0m"; // Starting point - Purple
            else if (x == dest.first && y == dest.second)
                std::cout << "\033[37mD  \033[0m"; // Destination point - White
            else if (grid[x][y] == 0)
                std::cout << "\033[31m0  \033[0m"; // Obstacle - Red
            else if (grid[x][y] == 1)
                std::cout << "\033[33m1  \033[0m"; // Free cell - Yellow
            else if (grid[x][y] == 2)
                std::cout << "\033[32m1  \033[0m"; // Path - Green
            else if (grid[x][y] == 3)
                std::cout << "\033[36m1  \033[0m"; // Temporary path - Cyan
            else
                std::cout << ".  "; // Any other cell
        }
        std::cout << "\n\n";
    }
}

// Clear temporary path markers from the grid
void clearTemporaryPath(int grid[][COL]) {
    for (int x = 0; x < ROW; x++) {
        for (int y = 0; y < COL; y++) {
            if (grid[x][y] == 3) {
                grid[x][y] = 1; // Reset temporary path markers to free cells
            }
        }
    }
}

// A* Search algorithm to find the shortest path
void aStarSearch(int grid[][COL], Pair src, Pair dest) {
    Cell cells[ROW][COL];

    clock_t start = clock();

    int x = src.first, y = src.second;
    cells[x][y].fCost = 0.0;
    cells[x][y].gCost = 0.0;
    cells[x][y].hCost = 0.0;
    cells[x][y].parent_x = x;
    cells[x][y].parent_y = y;

    std::set<pPair> possiblePaths;
    possiblePaths.insert(std::make_pair(0.0, std::make_pair(x, y)));

    bool foundDest = false;

    while (!possiblePaths.empty()) {
        pPair p = *possiblePaths.begin();
        possiblePaths.erase(possiblePaths.begin());
        x = p.second.first;
        y = p.second.second;
        cells[x][y].isPassed = true;

        for (int add_x = -1; add_x <= 1; add_x++) {
            for (int add_y = -1; add_y <= 1; add_y++) {
                if (add_x == 0 && add_y == 0) continue;
                int new_x = x + add_x;
                int new_y = y + add_y;
                if (isReachable(new_x, new_y)) {
                    if (isAtDestination(new_x, new_y, dest)) {
                        clock_t end = clock();
                        double search_time = calculateTime(start, end);
                        cells[new_x][new_y].parent_x = x;
                        cells[new_x][new_y].parent_y = y;
                        printf("The destination cell is found\n");
                        trackPath(cells, dest, grid);
                        foundDest = true;
                        std::cout << "\n";
                        printGrid(grid, src, dest);
                        std::cout << "Found path in " << search_time << " seconds.\n";
                        return;
                    }
                    else if (!cells[new_x][new_y].isPassed && isNotBlocked(grid, new_x, new_y)) {
                        double gNew = cells[x][y].gCost + ((add_x == 0 || add_y == 0) ? 1.0 : 1.414);
                        double hNew = calculateHCostValue(new_x, new_y, dest);
                        double fNew = gNew + hNew;

                        if (cells[new_x][new_y].fCost == FLT_MAX || cells[new_x][new_y].fCost > fNew) {
                            possiblePaths.insert(std::make_pair(fNew, std::make_pair(new_x, new_y)));
                            cells[new_x][new_y].fCost = fNew;
                            cells[new_x][new_y].gCost = gNew;
                            cells[new_x][new_y].hCost = hNew;
                            cells[new_x][new_y].parent_x = x;
                            cells[new_x][new_y].parent_y = y;

                            // Visualize the step
                            grid[new_x][new_y] = 3; // Temporary marker
                            std::this_thread::sleep_for(std::chrono::milliseconds(290)); // Delay for visualization
                            clearConsole(); // Clear console
                            printGrid(grid, src, dest);
                            clearTemporaryPath(grid); // Clear temporary markers
                        }
                    }
                }
            }
        }
    }

    if (!foundDest) {
        printf_s("There is no valid path to the destination!  --> (%d, %d)\n", dest.first, dest.second);
    }
    std::cout << "\n";
    printGrid(grid, src, dest);
}

// Clear the console screen
void clearConsole() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

// Calculate the time elapsed between start and end
double calculateTime(clock_t start, clock_t end) {
    return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

// Generate a random grid with a given block ratio
void generateRandomGrid(int grid[][COL], double block_ratio) {
    std::random_device rd;
    std::mt19937 mt_engine(rd());

    int total_cells = ROW * COL;
    int block_num = static_cast<int>(total_cells * block_ratio);

    std::vector<int> values(total_cells, 1); // Creates a vector storing total_cells amount of 1's.
    std::fill(values.begin(), values.begin() + block_num, 0); // Filling the vector from the beginning till the block_num th.
    std::shuffle(values.begin(), values.end(), mt_engine); // Shuffle's the vector.

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            grid[i][j] = values.at(i * COL + j); // Assigning the values to the grid array.
        }
    }
    grid[0][0] = 1; // Ensure the starting point is not blocked
    grid[9][9] = 1; // Ensure the ending point is not blocked
}

// Main function to start the program with either a random or predefined grid
void start(bool generate_random) {

    /* Description of the Grid-
    1--> The cell is not blocked
    0--> The cell is blocked    */

    int grid[ROW][COL];

    if (generate_random)
        generateRandomGrid(grid, 0.4);
    else {
        int predefined_grid[ROW][COL] = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                           { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                           { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                           { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                           { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                           { 1, 0, 1, 1, 1, 0, 1, 1, 0, 0 },
                           { 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 },
                           { 1, 1, 1, 1, 0, 0, 1, 0, 1, 1 } };
        std::copy(&predefined_grid[0][0], &predefined_grid[0][0] + ROW * COL, &grid[0][0]);
    }

    Pair src = std::make_pair(0, 0);
    Pair dest = std::make_pair(9, 9);

    printGrid(grid, src, dest);
    std::cout << "\n";

    int x_src = 0, y_src = 0, x_dest = 0, y_dest = 0;
    bool valid_coordinates = false;

    while (!valid_coordinates) {
        // Getting the input for row of source
        std::cout << "Enter x of source [0, 9]: ";
        std::cin >> x_src;

        // Getting the input for column of source
        std::cout << "Enter y of source [0, 9]: ";
        std::cin >> y_src;

        // Getting the input for row of destination
        std::cout << "Enter x of destination [0, 9]: ";
        std::cin >> x_dest;

        // Getting the input for column of destination
        std::cout << "Enter y of destination [0, 9]: ";
        std::cin >> y_dest;

        // Creating the pairs of source and destination locations
        src = std::make_pair(x_src, y_src);
        dest = std::make_pair(x_dest, y_dest);

        if (!isReachable(src.first, src.second) || !isReachable(dest.first, dest.second)) {
            std::cout << "Source or destination is out of range! Try again.\n";
        }
        else if (!isNotBlocked(grid, src.first, src.second) || !isNotBlocked(grid, dest.first, dest.second)) {
            std::cout << "Source or destination is blocked! Try again.\n";
        }
        else if (isAtDestination(src.first, src.second, dest)) {
            printf_s("Destination and source are the same. --> (%d, %d) Try again.\n", src.first, src.second);
        }
        else {
            std::cout << "Coordinates valid. Source and Destination are set.\n";
            valid_coordinates = true;
        }
    }

    printGrid(grid, src, dest);
    std::cout << "Press Enter to start...\n";
    std::cin.ignore();
    std::cin.get();

    clock_t start_time = 0, end_time = 0;

    aStarSearch(grid, src, dest);
}

