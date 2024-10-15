#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()

// Function to print the grid
void PrintGrid(const std::vector<std::vector<char>>& grid) {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Function to count live neighbors
int CountLiveNeighbors(const std::vector<std::vector<char>>& grid, int x, int y) {
    int live_neighbors = 0;
    int grid_size = grid.size();

    // Check surrounding 8 neighbors
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;  // Skip the cell itself
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && ny >= 0 && nx < grid_size && ny < grid_size) {
                if (grid[nx][ny] == 'O') {
                    live_neighbors++;
                }
            }
        }
    }
    return live_neighbors;
}

// Function to create the grid and simulate the game
void CreateGrid(int grid_size, int alive_squares, int number_of_iterations) {
    // Initialize the grid with all dead cells (' ')
    std::vector<std::vector<char>> grid(grid_size, std::vector<char>(grid_size, ' '));

    // Set grid borders (full-stops '.' at corners)
    grid[0][0] = grid[0][grid_size - 1] = '.';
    grid[grid_size - 1][0] = grid[grid_size - 1][grid_size - 1] = '.';

    // Randomly place alive cells ('O') in the grid
    srand(time(0));  // Seed random number generator
    int alive_placed = 0;
    while (alive_placed < alive_squares) {
        int x = rand() % grid_size;
        int y = rand() % grid_size;
        if (grid[x][y] == ' ') {  // Only place if the cell is dead
            grid[x][y] = 'O';
            alive_placed++;
        }
    }

    std::cout << "Initial Grid:" << std::endl;
    PrintGrid(grid);

    // Iterate through the number of steps
    for (int step = 0; step < number_of_iterations; ++step) {
        std::vector<std::vector<char>> new_grid = grid;  // Create a new grid for the next generation

        // Apply Game of Life rules to each cell
        for (int i = 0; i < grid_size; ++i) {
            for (int j = 0; j < grid_size; ++j) {
                int live_neighbors = CountLiveNeighbors(grid, i, j);

                // Rule 1: Any live cell with fewer than 2 or more than 3 live neighbors dies
                if (grid[i][j] == 'O' && (live_neighbors < 2 || live_neighbors > 3)) {
                    new_grid[i][j] = ' ';  // Cell dies
                }
                // Rule 2: Any dead cell with exactly 3 live neighbors becomes a live cell
                else if (grid[i][j] == ' ' && live_neighbors == 3) {
                    new_grid[i][j] = 'O';  // Cell becomes alive
                }
            }
        }

        // Update the grid to the new state
        grid = new_grid;

        std::cout << "Grid after iteration " << step + 1 << ":" << std::endl;
        PrintGrid(grid);
    }
}
