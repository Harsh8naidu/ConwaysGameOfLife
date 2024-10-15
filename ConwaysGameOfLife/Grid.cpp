#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()

// Function to print the grid with corners marked by full stops
void PrintGrid(const std::vector<std::vector<char>>& grid, int grid_height, int grid_width) {
    // Loop through the grid to print the cells
    for (int i = 0; i < grid_height; ++i) {
        // Print the top boundary of each row
        for (int j = 0; j < grid_width; ++j) {
            std::cout << ".---";  // Top of the cell with corners marked by "."
        }
        std::cout << "." << std::endl;  // End of the top boundary

        // Print the content of each cell (alive or dead)
        for (int j = 0; j < grid_width; ++j) {
            std::cout << "| " << grid[i][j] << " ";  // Cell content with vertical boundary
        }
        std::cout << "|" << std::endl;  // End of the cell row

        // Print the bottom boundary of the row
        for (int j = 0; j < grid_width; ++j) {
            std::cout << ".---";  // Bottom boundary with corners marked by "."
        }
        std::cout << "." << std::endl;  // End of the bottom boundary
    }
}

// Function to count live neighbors around a cell
int CountLiveNeighbors(const std::vector<std::vector<char>>& grid, int x, int y, int grid_height, int grid_width) {
    int live_neighbors = 0;

    // Check surrounding 8 neighbors
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;  // Skip the cell itself
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && ny >= 0 && nx < grid_height && ny < grid_width) {
                if (grid[nx][ny] == 'O') {
                    live_neighbors++;
                }
            }
        }
    }
    return live_neighbors;
}

// Function to create the grid and simulate the game
void CreateGrid(int grid_height, int grid_width, int alive_squares, int number_of_iterations) {
    // Initialize the grid with all dead cells (' ')
    std::vector<std::vector<char>> grid(grid_height, std::vector<char>(grid_width, ' '));

    // Randomly place alive cells ('O') in the grid
    srand(time(0));  // Seed random number generator
    int alive_placed = 0;
    while (alive_placed < alive_squares) {
        int x = rand() % grid_height;
        int y = rand() % grid_width;
        if (grid[x][y] == ' ') {  // Only place if the cell is dead
            grid[x][y] = 'O';
            alive_placed++;
        }
    }

    std::cout << "Initial Grid:" << std::endl;
    PrintGrid(grid, grid_height, grid_width);

    // Iterate through the number of steps
    for (int step = 0; step < number_of_iterations; ++step) {
        std::vector<std::vector<char>> new_grid = grid;  // Create a new grid for the next generation

        // Apply Game of Life rules to each cell
        for (int i = 0; i < grid_height; ++i) {
            for (int j = 0; j < grid_width; ++j) {
                int live_neighbors = CountLiveNeighbors(grid, i, j, grid_height, grid_width);

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
        PrintGrid(grid, grid_height, grid_width);
    }
}
