#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Grid.hpp"
#include "Utils.hpp"

int grid_height = 0;
int grid_width = 0;
int alive_squares = 0;
int number_of_iterations = 0;

void CheckStartInput(std::string input_text, bool& first_input_flag);
void StartGame();
void InGame();
void EndGame();

void StartGame() {
    bool first_input_flag = false;
    std::string input_text = "";

    std::cout << "Welcome to Conway's Game of Life" << std::endl;

    std::cout << std::endl;

    // Game loop for start input
    while (!first_input_flag) {
        std::cout << "To start the game, type 'start' and press enter: ";
        std::cin >> input_text;
        CheckStartInput(input_text, first_input_flag);
    }
}

void InGame() {
    std::string input_text = "";

    // Display commands as soon as the game starts
    std::cout << std::endl;
    std::cout << "Welcome to Conway's Game of Life!" << std::endl;
    std::cout << "These are the available commands:" << std::endl;
    std::cout << "1. help - To know the rules about the game." << std::endl;
    std::cout << "2. create - To create a new grid." << std::endl;
    std::cout << "3. save - To save the grid." << std::endl;
    std::cout << "4. load - To load the grid." << std::endl;
    std::cout << "5. quit - To quit the game." << std::endl;
    std::cout << std::endl;

    // Ask the user if they want to run a normal simulation or an experiment
    std::cout << "Do you want to run (1) a normal simulation or (2) an experiment? (Enter 1 or 2): ";
    std::cin >> input_text;

    if (input_text == "1") {
        // Run the normal simulation
        std::cout << "Running a normal simulation..." << std::endl;
        std::cout << std::endl;

        std::cout << "Type 'create' to create a grid." << std::endl;
    }
    else if (input_text == "2") {
        // Run the experiment
        int target_shape = 0;
        std::cout << "Q2: Block or Beehive" << std::endl;
        std::cout << "Q3: Blinker or Toad" << std::endl;
        std::cout << "Q4: Glider or LWSS" << std::endl;

        std::cout << "Enter the question number (Q2, Q3, Q4): ";
        std::cin >> input_text;

        if (input_text == "Q2") {
            std::cout << "Running experiment to find Block or Beehive..." << std::endl;
            target_shape = 2;
        }
        else if (input_text == "Q3") {
            std::cout << "Running experiment to find Blinker or Toad..." << std::endl;
            target_shape = 3;
        }
        else if (input_text == "Q4") {
            std::cout << "Running experiment to find Glider or LWSS..." << std::endl;
            target_shape = 4;
        }
        else {
            std::cout << "Invalid choice. Exiting..." << std::endl;
            return; // Exit the function
        }

        std::cout << "Enter grid height (greater than 30): ";
        std::cin >> grid_height;
        std::cout << "Enter grid width (greater than 30): ";
        std::cin >> grid_width;
        std::cout << "Enter the number of starting alive squares (greater than 25): ";
        std::cin >> alive_squares;

        RunExperiment(grid_height, grid_width, alive_squares, 10, target_shape);  // Adjust the number of iterations
    }
    else {
        std::cout << "Invalid choice. Exiting..." << std::endl;
        return; // Exit the function
    }

    // Main game loop
    bool in_game = true;
    while (in_game) {
        std::cout << "Please type a command and press enter: ";
        std::cin >> input_text;

        if (input_text == "quit") {
            in_game = false;
            EndGame();
        }
        else if (input_text == "help") {
            std::cout << "The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970." << std::endl;
            std::cout << "The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input." << std::endl;
            std::cout << "One interacts with the Game of Life by creating an initial configuration and observing how it evolves." << std::endl;
            std::cout << "The rules of the game are as follows:" << std::endl;
            std::cout << "1. Any live cell with fewer than two live neighbors dies, as if by underpopulation." << std::endl;
            std::cout << "2. Any live cell with two or three live neighbors lives on to the next generation." << std::endl;
            std::cout << "3. Any live cell with more than three live neighbors dies, as if by overpopulation." << std::endl;
            std::cout << "4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction." << std::endl;
        }
        else if (input_text == "create") {
            std::cout << "Enter the height of the grid: ";
            std::cin >> grid_height;
            std::cout << "Enter the width of the grid: ";
            std::cin >> grid_width;
            std::cout << "Enter the number of alive squares: ";
            std::cin >> alive_squares;
            std::cout << "Enter the number of iterations: ";
            std::cin >> number_of_iterations;

            CreateGrid(grid_height, grid_width, alive_squares, number_of_iterations);
        }
        else if (input_text == "save") {
            if (grid.empty()) {
                std::cout << "Error: No grid to save. Please create a grid first." << std::endl;
            }
            else {
                std::cout << "Saving the grid..." << std::endl;
                SaveGrid(grid, grid_height, grid_width, number_of_iterations);
            }
        }
        else if (input_text == "load") {
            std::cout << "Loading the grid..." << std::endl;
            LoadGrid(grid, grid_height, grid_width, number_of_iterations);
        }
        else {
            std::cout << "Invalid command! Please type 'help', 'display', 'create', 'iterate', or 'quit' and press enter." << std::endl;
        }
    }
}


void EndGame() {
    std::cout << "Thank you for playing! The game has ended." << std::endl;
    exit(0);
}

void CheckStartInput(std::string input_text, bool& first_input_flag) {
    if (input_text == "start") {
        first_input_flag = true;  // Exit the start loop
        InGame();  // Enter the game mode
    }
    else {
        std::cout << std::endl;
        std::cout << "Invalid Input! Please type 'start' and press enter to start the game." << std::endl;
        std::cout << std::endl;
    }
}

void SaveGridCall(const std::vector<std::vector<char>>& grid, int grid_height, int grid_width, int number_of_iterations) {
    SaveGrid(grid, grid_height, grid_width, number_of_iterations);
}