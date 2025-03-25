#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "Ship.h"

class Board {
private:
    char grid[10][10]; // 10x10 Board
    char hitMissGrid[10][10]; // Track hits and misses
    std::vector<Ship> ships; // Stores all ships

public:
    Board();
    void placeShip(Ship &ship); // Places a ship randomly
    void displayBoard(); // Displays the board
    
    // New methods
    bool processShot(int row, int col); // Process a shot, return true if hit
    bool allShipsSunk() const; // Check if all ships are sunk
};

#endif
