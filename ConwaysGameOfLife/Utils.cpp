#include <iostream>
#include <string>

void CheckInput(std::string input_text, bool& first_input_flag);
void StartGame();
void InGame(std::string input_text);
void EndGame();

void StartGame() {
    bool first_input_flag = false;
    std::string input_text = "";

    std::cout << "Welcome to the Conway's Game of Life" << std::endl;
    std::cout << std::endl;

    // Game loop
    while (!first_input_flag) {
       
        std::cout << "To start the game, type 'start' and press enter: ";
        std::cin >> input_text;
        CheckInput(input_text, first_input_flag);
    }
}

void InGame(std::string input_text) {
    std::cout << std::endl;
    std::cout << "These are the following commands to play this game. Please type this command and press enter to execute these commands" << std::endl;
    std::cout << std::endl;
    std::cout << "1. help - To know the rules about the game." << std::endl;
    std::cout << "2. display - To display the grid." << std::endl;
    std::cout << "3. iterate - To iterate through the grid." << std::endl;
    std::cout << "4. quit - To quit the game." << std::endl;
    std::cout << std::endl;
    std::cout << "Please type the command and press enter: ";
    std::cin >> input_text;

    
}

void EndGame() {
    // End game logic
}

void CheckStartInput(std::string input_text, bool& first_input_flag) {
    if (input_text == "start") {
        InGame(input_text);
        first_input_flag = true;  // Exits the loop in StartGame
    }
    else {
        std::cout << std::endl;
        std::cout << "Invalid Input! Please type 'start' and press enter to start the game." << std::endl;
        std::cout << std::endl;
    }
}
    

void CheckInGameInput(std::string input_text) {
    if (input_text == "help") {
        std::cout << std::endl;
        std::cout << "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970." << std::endl;
        std::cout << "The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input." << std::endl;
        std::cout << "One interacts with the Game of Life by creating an initial configuration and observing how it evolves." << std::endl;
        std::cout << "It is Turing complete and can simulate a universal constructor or any other Turing machine." << std::endl;
        std::cout << "The game is played on a grid of cells, where each cell can be either alive or dead." << std::endl;
        std::cout << "The game follows these rules:" << std::endl;
        std::cout << "1. Any live cell with fewer than two live neighbours dies, as if by underpopulation." << std::endl;
        std::cout << "2. Any live cell with two or three live neighbours lives on to the next generation." << std::endl;
        std::cout << "3. Any live cell with more than three live neighbours dies, as if by overpopulation." << std::endl;
        std::cout << "4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction." << std::endl;
        std::cout << std::endl;
        std::cout << "Please type the command and press enter: ";
        std::cin >> input_text;
    }
    else if (input_text == "display") {
        // Display the grid
    }
    else if (input_text == "iterate") {
        // Iterate through the grid
    }
    else if (input_text == "quit") {
        EndGame();
    }
    else {
        std::cout << std::endl;
        std::cout << "Invalid Input! Please type 'help', 'display', 'iterate' or 'quit' and press enter to execute the command." << std::endl;
        std::cout << std::endl;
    }
}