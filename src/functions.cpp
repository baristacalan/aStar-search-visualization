#include "functions.h"

bool isReachable(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isNotBlocked(int grid[][COL], int row, int col) {
    if (grid[row][col] == 1) return true;
    else return false;
}

bool isDestination(int row, int col, Pair dest) {
    if (dest.first == row && dest.second == col) return true;
    else return false;
}

double calculateHCostValue(int row, int col, Pair dest) {
    //return (double)sqrt(pow(row - dest.first, 2) + pow(col - dest.second, 2));
    return static_cast<double>(sqrt(pow(row - dest.first, 2) + pow(col - dest.second, 2)));
}   

void trackPath(Cell cells[][COL], Pair dest, int grid[][COL]) {
    std::cout << "The path is: ";
    int row = dest.first;
    int col = dest.second;

    std::stack<Pair> Path;

    //Starts from the destination, checks if parent(previous) cordinates of the cell is equal to current.
    //If it's not equal, then the pair will be pushed into the Pair stack.
    //There, it updates the current row and col value of cell to its parent(previous) one.

    while (!(cells[row][col].parent_x == row && cells[row][col].parent_y == col)) {
        Path.push(std::make_pair(row, col));
        int temp_row = cells[row][col].parent_x;
        int temp_col = cells[row][col].parent_y;
        row = temp_row;
        col = temp_col;
    }
    Path.push(std::make_pair(row, col));

    while (!Path.empty()) {
        Pair p = Path.top();
        Path.pop();
        grid[p.first][p.second] = 2; // Mark the path in the grid
        printf_s("-->(%d, %d)", p.first, p.second);
    }
    return;
}

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
        std::cout << "\n";
    }
}

void clearTemporaryPath(int grid[][COL]) {
    for (int x = 0; x < ROW; x++) {
        for (int y = 0; y < COL; y++) {
            if (grid[x][y] == 3) {
                grid[x][y] = 1; // Reset temporary path markers to free cells
            }
        }
    }
}

void aStarSearch(int grid[][COL], Pair src, Pair dest) {
    if (!isReachable(src.first, src.second) || !isReachable(dest.first, dest.second)) {
        std::cout << "Source or destination is out of range!\n";
        return;
    }
    if (!isNotBlocked(grid, src.first, src.second) || !isNotBlocked(grid, dest.first, dest.second)) {
        std::cout << "Source or destination is blocked!\n";
        return;
    }
    if (isDestination(src.first, src.second, dest)) {
        printf_s("We are already at the destination. --> (%d, %d)\n", src.first, src.second);
        return;
    }

    bool closedList[ROW][COL]; //A bool array to check whether the algorithm has been on any (x, y) location.
    memset(closedList, false, sizeof(closedList));

    Cell cells[ROW][COL];

    int x = 0, y = 0;

    for (x = 0; x < ROW; x++) {
        for (y = 0; y < COL; y++) {
            cells[x][y].fCost = FLT_MAX;
            cells[x][y].gCost = FLT_MAX;
            cells[x][y].hCost = FLT_MAX;
            cells[x][y].parent_x = -1;
            cells[x][y].parent_y = -1;
        }
    }

    x = src.first, y = src.second;
    cells[x][y].fCost = 0.0;
    cells[x][y].gCost = 0.0;
    cells[x][y].hCost = 0.0;
    cells[x][y].parent_x = x;
    cells[x][y].parent_y = y;

    std::set<pPair> openList;
    openList.insert(std::make_pair(0.0, std::make_pair(x, y)));

    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        x = p.second.first;
        y = p.second.second;
        closedList[x][y] = true;

        for (int add_x = -1; add_x <= 1; add_x++) {
            for (int add_y = -1; add_y <= 1; add_y++) {
                if (add_x == 0 && add_y == 0) continue;
                int new_x = x + add_x;
                int new_y = y + add_y;
                if (isReachable(new_x, new_y)) {
                    if (isDestination(new_x, new_y, dest)) {
                        cells[new_x][new_y].parent_x = x; //Previous value of x to track.
                        cells[new_x][new_y].parent_y = y; // Previous value of y to track.
                        printf("The destination cell is found\n");
                        trackPath(cells, dest, grid);
                        foundDest = true;
                        std::cout << "\n";
                        printGrid(grid, src, dest);
                        return;
                    }
                    else if (!closedList[new_x][new_y] && isNotBlocked(grid, new_x, new_y)) {
                        double gNew = cells[x][y].gCost + ((add_x == 0 || add_y == 0) ? 1.0 : 1.414);
                        double hNew = calculateHCostValue(new_x, new_y, dest);
                        double fNew = gNew + hNew;

                        if (cells[new_x][new_y].fCost == FLT_MAX || cells[new_x][new_y].fCost > fNew) {
                            openList.insert(std::make_pair(fNew, std::make_pair(new_x, new_y)));
                            cells[new_x][new_y].fCost = fNew;
                            cells[new_x][new_y].gCost = gNew;
                            cells[new_x][new_y].hCost = hNew;
                            cells[new_x][new_y].parent_x = x; //Previous value of x to track.
                            cells[new_x][new_y].parent_y = y; //Previous value of y to track.

                            // Visualize the step
                            grid[new_x][new_y] = 3; // Temporary marker
                            std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Delay for visualization
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

void clearConsole() {

    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}
