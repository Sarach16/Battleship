#include <iostream>
#include <ctime>
#include <string>
#include "Board.h"
#include "Ship.h"

// function to convert user input to board coordinates
bool parseCoordinates(const std::string& input, int& row, int& col) {
    if (input.length() < 2) return false;
    
    char rowChar = toupper(input[0]);
    if (rowChar < 'A' || rowChar > 'J') return false;
    row = rowChar - 'A';
    
    try {
        std::string colStr = input.substr(1);
        col = std::stoi(colStr) - 1; // Convert from 1-based to 0-based
        if (col < 0 || col >= 10) return false;
    } catch (...) {
        return false;
    }
    
    return true;
}

int main() {
    srand(time(0)); // Seed for random placement

    Board gameBoard;

    // Create ships
    Ship frigate("Frigate", 2);
    Ship sub("Sub", 3);
    Ship destroyer("Destroyer", 3);
    Ship battleship("Battleship", 4);
    Ship aircraftCarrier("Aircraft Carrier", 5);

    // Place ships on board
    gameBoard.placeShip(frigate);
    gameBoard.placeShip(sub);
    gameBoard.placeShip(destroyer);
    gameBoard.placeShip(battleship);
    gameBoard.placeShip(aircraftCarrier);

    // Game loop
    int turns = 0;
    bool gameOver = false;
    
    std::cout << "BATTLESHIP GAME\n";
    std::cout << " Enter coordinates to fire (example A5)\n";
    
    while (!gameOver) {
        // Display current board state
        gameBoard.displayBoard();
        
        // Get player input
        std::string input;
        int row, col;
        bool validInput = false;
        
        while (!validInput) {
            std::cout << "\nEnter target coordinates: ";
            std::cin >> input;
            
            if (parseCoordinates(input, row, col)) {
                validInput = true;
            } else {
                std::cout << "Invalid coordinates. Please use format like 'A5'.\n";
            }
        }
        
        // Process the shot
        bool hit = gameBoard.processShot(row, col);
        turns++;
        
        if (hit) {
            std::cout << "HIT!\n";
        } else {
            std::cout << "MISS!\n";
        }
        
        // Check if game is over
        if (gameBoard.allShipsSunk()) {
            gameOver = true;
            std::cout << "\nGame Over! You sank all ships in " << turns << " turns.\n";
        }
    }
    
    // Show final board state
    gameBoard.displayBoard();
    
    return 0;
}