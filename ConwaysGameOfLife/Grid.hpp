#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

// Declare the grid and related variables as extern so they are accessible across files
extern std::vector<std::vector<char>> grid;


// Function declarations
void CreateGrid(int grid_height, int grid_width, int alive_squares, int number_of_iterations);
bool LoadGrid(std::vector<std::vector<char>>& grid, int& grid_height, int& grid_width, int& number_of_iterations);
void SaveGrid(const std::vector<std::vector<char>>& grid, int grid_height, int grid_width, int number_of_iterations);
void PrintGrid(const std::vector<std::vector<char>>& grid, int grid_height, int grid_width);
void RunExperiment(int grid_height, int grid_width, int alive_squares, int number_of_iterations, std::string target_shape);
void SaveIterationsToFile(const std::vector<std::vector<std::vector<char>>>& iterations, const std::string& filename);
void LoadIterationsFromFile(const std::string& filename);


#endif
