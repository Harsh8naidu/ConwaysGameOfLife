// ConwaysGameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "Grid.hpp"
#include "Utils.hpp"

int main()
{
    StartGame();

    // Lowest ERN for block: 30, 30, 25 = 85
	// Lowest ERN for Beehive: 30, 30, 25 = 85
	// Lowest ERN for Blinker: 30, 30, 25 = 85
	// Lowest ERN for Glider: 34, 34, 60 = 128
	// Lowest ERN for Toad: 30, 30, 40 = 100
	// Unfortunately, I did not get LWSS to work. I tried different grid sizes and starting alive squares, but it did not work.

    return 0;
}
