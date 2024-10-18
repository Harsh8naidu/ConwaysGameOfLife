#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()
#include <fstream>
#include "Grid.hpp"
#include <string>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::milliseconds

// Define the global grid here
std::vector<std::vector<char>> grid;

// Global experiment counter
int experiment_count = 0;


bool HasAliveCells(const std::vector<std::vector<char>>& grid);
void ClearConsole();

// Function to print the grid
void PrintGrid(const std::vector<std::vector<char>>& grid, int grid_height, int grid_width) {
    //ClearConsole(); // Clear the console before printing the grid
    for (int i = 0; i < grid_height; ++i) {
        for (int j = 0; j < grid_width; ++j) {
            std::cout << ".   ";
        }
        std::cout << "." << std::endl;

        for (int j = 0; j < grid_width; ++j) {
            std::cout << ". " << grid[i][j] << " ";
        }
        std::cout << "." << std::endl;
    }

    for (int j = 0; j < grid_width; ++j) {
        std::cout << ".   ";
    }
    std::cout << "." << std::endl;
}

// Function to count live neighbors
int CountLiveNeighbors(const std::vector<std::vector<char>>& grid, int x, int y, int grid_height, int grid_width) {
    int live_neighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && ny >= 0 && nx < grid_height && ny < grid_width && grid[nx][ny] == 'O') {
                live_neighbors++;
            }
        }
    }
    return live_neighbors;
}

// Function to create the grid
void CreateGrid(int grid_height, int grid_width, int alive_squares, int number_of_iterations) {
    grid.resize(grid_height, std::vector<char>(grid_width, ' '));

    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
    int alive_placed = 0;

    while (alive_placed < alive_squares) {
        int x = rand() % grid_height;
        int y = rand() % grid_width;
        if (grid[x][y] == ' ') {
            grid[x][y] = 'O';
            alive_placed++;
        }
    }

    std::cout << "Initial Grid:" << std::endl;
    PrintGrid(grid, grid_height, grid_width);

    for (int step = 0; step < number_of_iterations; ++step) {
        std::vector<std::vector<char>> new_grid = grid;

        for (int i = 0; i < grid_height; ++i) {
            for (int j = 0; j < grid_width; ++j) {
                int live_neighbors = CountLiveNeighbors(grid, i, j, grid_height, grid_width);

                if (grid[i][j] == 'O' && (live_neighbors < 2 || live_neighbors > 3)) {
                    new_grid[i][j] = ' ';
                }
                else if (grid[i][j] == ' ' && live_neighbors == 3) {
                    new_grid[i][j] = 'O';
                }
            }
        }

        grid = new_grid;
        std::cout << "Grid after iteration " << step + 1 << ":" << std::endl;
        PrintGrid(grid, grid_height, grid_width);
    }
}

// Function to save the grid to a file
void SaveGrid(const std::vector<std::vector<char>>& grid, int grid_height, int grid_width, int number_of_iterations) {
    std::ofstream save_file("saved_game.txt", std::ios::trunc);
    if (!save_file.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    // Save dimensions and number of iterations first
    save_file << grid_height << " " << grid_width << " " << number_of_iterations << std::endl;

    for (int i = 0; i < grid_height; ++i) {
        for (int j = 0; j < grid_width; ++j) {
            save_file << grid[i][j];
        }
        save_file << std::endl; // Write a newline after each row
    }

    save_file.close();
    std::cout << "Game saved successfully!" << std::endl;
}


bool LoadGrid(std::vector<std::vector<char>>& grid, int& grid_height, int& grid_width, int& number_of_iterations) {
    std::ifstream load_file("saved_game.txt");
    if (!load_file.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    // Read dimensions and number of iterations
    load_file >> grid_height >> grid_width >> number_of_iterations;

    // Resize the grid based on the dimensions read
    grid.resize(grid_height, std::vector<char>(grid_width, ' '));

    load_file.ignore(); // Skip the remaining part of the first line

    // Read the grid row by row
    std::string line;
    for (int i = 0; i < grid_height; ++i) {
        std::getline(load_file, line); // Read the whole row as a string
        for (int j = 0; j < grid_width && j < line.size(); ++j) {
            grid[i][j] = line[j];
        }
    }

    load_file.close();
    std::cout << "Game loaded successfully!" << std::endl;
    PrintGrid(grid, grid_height, grid_width); // Display the loaded grid
    return true;
}

// Function to match a pattern at a given position in the grid
bool MatchesShape(const std::vector<std::vector<char>>& grid, const std::vector<std::vector<char>>& shape, int x, int y) {
    int shape_height = shape.size();
    int shape_width = shape[0].size();

    // Ensure that the shape doesn't go out of bounds
    for (int i = 0; i < shape_height; ++i) {
        for (int j = 0; j < shape_width; ++j) {
            if (x + i >= grid.size() || y + j >= grid[0].size()) {
                return false; // Shape goes beyond grid boundaries
            }
            if (grid[x + i][y + j] != shape[i][j]) {
                return false; // Mismatch at some position
            }
        }
    }
    return true; // All cells match
}

// Function to check the grid for any shape like a block or beehive
std::string CheckForShapes(const std::vector<std::vector<char>>& grid, int target_shape) {
    // Define patterns
    std::vector<std::vector<char>> block = {
        {'O', 'O'},
        {'O', 'O'}
    };

    std::vector<std::vector<char>> beehive = {
        {' ', 'O', 'O', ' '},
        {'O', ' ', ' ', 'O'},
        {' ', 'O', 'O', ' '}
    };

    std::vector<std::vector<char>> blinker = {
        {' ', 'O', ' '},
        {' ', 'O', ' '},
        {' ', 'O', ' '}
    };

    std::vector<std::vector<char>> toad = {
        {' ', ' ', 'O', 'O', 'O'},
        {'O', 'O', 'O', ' ', ' '}
    };

    std::vector<std::vector<char>> glider = {
        {'O', ' ', ' '},
        {' ', 'O', 'O'},
        {'O', 'O', ' '}
    };

    std::vector<std::vector<char>> LWSS = {
        {'O', 'O', ' ', 'O'},
        {' ', ' ', 'O', 'O'},
        {'O', 'O', 'O', ' '}
    };

    // Check for shapes
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (target_shape == 2 && MatchesShape(grid, block, i, j)) {
                return "Block";
            }
            else if (target_shape == 2 && MatchesShape(grid, beehive, i, j)) {
                return "Beehive";
            }
            else if (target_shape == 3 && MatchesShape(grid, blinker, i, j)) {
                return "Blinker";
            }
            else if (target_shape == 3 && MatchesShape(grid, toad, i, j)) {
                return "Toad";
            }
            else if (target_shape == 4 && MatchesShape(grid, glider, i, j)) {
                return "Glider";
            }
            else if (target_shape == 4 && MatchesShape(grid, LWSS, i, j)) {
                return "LWSS";
            }
        }
    }

    return "None"; // No shape found
}

void ClearConsole() {
    // Clear console command for Windows
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void MoveCursorUp(int lines) {
    // Move the cursor up by the specified number of lines
    std::cout << "\033[" << lines << "A"; // ANSI escape code to move up
}

void RunExperiment(int grid_height, int grid_width, int alive_squares, int number_of_iterations, int target_shape) {
    bool pattern_found = false;

    while (!pattern_found) {
        experiment_count++;

        // Create a list to store all iterations of the current experiment
        std::vector<std::vector<std::vector<char>>> iterations;

        // Create a new random grid
        CreateGrid(grid_height, grid_width, alive_squares, number_of_iterations);
        std::cout << "Experiment " << experiment_count << " - Initial Grid:" << std::endl;

        // Store the initial grid state
        iterations.push_back(grid);
        PrintGrid(grid, grid_height, grid_width);

        if (!HasAliveCells(grid)) {
            std::cout << "No alive cells in the grid for Experiment " << experiment_count << ". Starting a new experiment..." << std::endl;
            continue; // Skip to the next experiment
        }

        // Iterate through the grid
        for (int step = 0; step < number_of_iterations; ++step) {
            std::vector<std::vector<char>> new_grid = grid;

            // Apply rules of Conway's Game of Life
            for (int i = 0; i < grid_height; ++i) {
                for (int j = 0; j < grid_width; ++j) {
                    int live_neighbors = CountLiveNeighbors(grid, i, j, grid_height, grid_width);
                    if (grid[i][j] == 'O' && (live_neighbors < 2 || live_neighbors > 3)) {
                        new_grid[i][j] = ' ';
                    }
                    else if (grid[i][j] == ' ' && live_neighbors == 3) {
                        new_grid[i][j] = 'O';
                    }
                }
            }

            grid = new_grid;
            // Store the current iteration
            iterations.push_back(grid);

            ClearConsole();
            std::cout << "Experiment " << experiment_count << " - Iteration " << step + 1 << ":" << std::endl;
            PrintGrid(grid, grid_height, grid_width);

            std::string result = CheckForShapes(grid, target_shape);
            std::cout << "Checking for " << result << "..." << std::endl;
            if (result != "None") {
                std::cout << result << " found in Experiment " << experiment_count << " after " << step + 1 << " iterations." << std::endl;
                pattern_found = true;

                // Print all saved iterations that led to this pattern
                std::cout << "Displaying the series of grids leading to the pattern:\n";
                for (int i = 0; i < iterations.size(); ++i) {
                    std::cout << "Iteration " << i + 1 << ":\n";
                    PrintGrid(iterations[i], grid_height, grid_width);
                }
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        if (!pattern_found) {
            std::cout << "No " << target_shape << " found in Experiment " << experiment_count << ". Starting a new experiment..." << std::endl;
        }
    }
}

// Function to check if there are any alive cells in the grid
bool HasAliveCells(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell == 'O') { // 'O' represents an alive cell
                return true; // There's at least one alive cell
            }
        }
    }
    return false; // No alive cells found
}