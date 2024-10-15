#include <iostream>
#include <string>
#include "Grid.hpp"

void CheckStartInput(std::string input_text, bool& first_input_flag);
void StartGame();
void InGame();
void EndGame();
void CheckInGameInput(std::string input_text, int &grid_size, int &alive_squares, int &number_of_iterations);
void CreateGridCall(int grid_size, int alive_squares, int number_of_iterations);

void StartGame() {
    bool first_input_flag = false;
    std::string input_text = "";

    std::cout << "Welcome to the Conway's Game of Life" << std::endl;
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
    
    // Variables to be filled by user
    int grid_size = 0;
    int alive_squares = 0;
    int number_of_iterations = 0;

    std::cout << std::endl;
    std::cout << "These are the following commands to play this game. Please type a command and press enter to execute:" << std::endl;
    std::cout << "1. help - To know the rules about the game." << std::endl;
    std::cout << "2. create - To create a new grid." << std::endl;
    std::cout << "3. display - To display the grid." << std::endl;
    std::cout << "4. iterate - To iterate through the grid." << std::endl;
    std::cout << "5. quit - To quit the game." << std::endl;
    std::cout << std::endl;

    // Loop to allow continuous input until 'quit' is entered
    bool in_game = true;
    while (in_game) {
        std::cout << "Please type the command and press enter: ";
        std::cin >> input_text;
        if (input_text == "quit") {
            in_game = false;
            EndGame();
        }
        else {
            // Pass the grid variables to the command handler
            CheckInGameInput(input_text, grid_size, alive_squares, number_of_iterations);
        }
    }
}

void EndGame() {
    std::cout << "Thank you for playing! The game has ended." << std::endl;
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

void CheckInGameInput(std::string input_text, int& grid_size, int& alive_squares, int& number_of_iterations) {
    if (input_text == "help") {
        std::cout << std::endl;
        std::cout << "The Game of Life, also known simply as Life, is a cellular automaton devised by John Horton Conway in 1970." << std::endl;
        std::cout << "Rules of the game:" << std::endl;
        std::cout << "1. Any live cell with fewer than two live neighbours dies (underpopulation)." << std::endl;
        std::cout << "2. Any live cell with two or three live neighbours lives on to the next generation." << std::endl;
        std::cout << "3. Any live cell with more than three live neighbours dies (overpopulation)." << std::endl;
        std::cout << "4. Any dead cell with exactly three live neighbours becomes a live cell (reproduction)." << std::endl;
        std::cout << std::endl;
    }
    else if (input_text == "create") {
        // Ask the user for grid parameters
        std::cout << "Enter grid size: ";
        std::cin >> grid_size;
        std::cout << "Enter the number of alive squares: ";
        std::cin >> alive_squares;
        std::cout << "Enter the number of iterations: ";
        std::cin >> number_of_iterations;

        std::cout << "Creating the grid..." << std::endl;

        // Call the function to create the grid with user inputs
        CreateGridCall(grid_size, alive_squares, number_of_iterations);
    }
    else if (input_text == "display") {
        // Code to display the grid
        std::cout << "Displaying the grid..." << std::endl;
    }
    else if (input_text == "iterate") {
        // Code to iterate through the grid
        std::cout << "Iterating through the grid..." << std::endl;
    }
    else {
        std::cout << std::endl;
        std::cout << "Invalid command! Please type 'help', 'display', 'create', 'iterate', or 'quit' and press enter." << std::endl;
        std::cout << std::endl;
    }
}

void CreateGridCall(int grid_size, int alive_squares, int number_of_iterations) {
    CreateGrid(grid_size, alive_squares, number_of_iterations);
}
