#include <iostream>

void CheckInput(std::string input_text, bool first_input_flag);
void StartGame();
void InGame();
void EndGame();

void StartGame() {
	bool first_input_flag = false;
	std::string input_text = "";

	if (!first_input_flag) {
		std::cout << "Welcome to the Conway's Game of Life" << std::endl;
		std::cout << std::endl;
		std::cout << "To start the game, type 'start' and press enter";
		std::cout << std::endl;
		std::cin >> input_text;
		CheckInput(input_text, first_input_flag);
	}
	else {
		std::cin >> input_text;
		CheckInput(input_text, first_input_flag);
	}
}

void InGame() {
	std::cout << "Game has started" << std::endl;
	std::cout << "Game has started" << std::endl;
}

void EndGame() {

}

void CheckInput(std::string input_text, bool first_input_flag) {
	if (input_text == "start") {
		InGame();
	}
	else {
		first_input_flag = true;
		std::cout << "Invalid Input! Please type 'start' and press enter to start the game.";
		std::cout << std::endl;
		StartGame();
	}
}


