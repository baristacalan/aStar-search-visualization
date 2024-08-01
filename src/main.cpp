#include "functions.h"

int main() {
    bool retry = false;
    std::cout << "Welcome to the A* Algoritm Visualization.\n";

    do {
        // Ask the user whether to generate a random grid or use a predefined grid
        bool generate_random;
        std::cout << "Generate random grid? (1 for Yes, 0 for No): ";
        std::cin >> generate_random;

        // Start the pathfinding visualization
        start(generate_random);

        // Ask the user if they want to retry
        std::cout << "Do you want to retry? (1 for Yes, 0 for No): ";
        std::cin >> retry;

    } while (retry);
    std::cin.ignore();
    std::cin.get(); // Blocks the instant shutdown when ran on .exe

    return 0;
}
