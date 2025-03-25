#include "Board.h"
#include <cstdlib>  // For random placement
#include <ctime>    // For seeding randomness

#include "Board.h"
#include <cstdlib>

Board::Board() {
    // Initialize board with empty spaces
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j] = '.';
            hitMissGrid[i][j] = '.';
        }
    }
}

void Board::placeShip(Ship &ship) {
    bool placed = false;

    while (!placed) {
        int row = rand() % 10;  // Random row (0-9)
        int col = rand() % 10;  // Random column (0-9)
        bool horizontal = rand() % 2; // Random direction

        std::vector<std::pair<int, int>> coords;
        bool valid = true;

        for (int i = 0; i < ship.getSize(); i++) {
            int newRow = horizontal ? row : row + i;
            int newCol = horizontal ? col + i : col;

            if (newRow >= 10 || newCol >= 10 || grid[newRow][newCol] != '.') {
                valid = false;
                break;
            }
            coords.push_back({newRow, newCol});
        }

        if (valid) {
            for (auto &[r, c] : coords) {
                grid[r][c] = ship.getName()[0]; // Use first letter of ship name
            }
            ship.setPosition(coords);
            ships.push_back(ship); // Add ship to vector
            placed = true;
        }
    }
}

void Board::displayBoard() {
    std::cout << "  1 2 3 4 5 6 7 8 9 10\n";
    for (int i = 0; i < 10; i++) {
        std::cout << char('A' + i) << " ";
        for (int j = 0; j < 10; j++) {
            // If there's a hit or miss at this position, show it
            if (hitMissGrid[i][j] == 'X' || hitMissGrid[i][j] == 'O') {
                std::cout << hitMissGrid[i][j] << " ";
            } else {
                // Otherwise show the ship or empty space
                std::cout << grid[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool Board::processShot(int row, int col) {
    // Check if coordinates are valid
    if (row < 0 || row >= 10 || col < 0 || col >= 10) {
        return false;
    }
    
    // Check if this position was already shot at
    if (hitMissGrid[row][col] != '.') {
        return false;
    }
    
    // Check if it hits any ship
    for (Ship& ship : ships) {
        if (ship.checkHit(row, col)) {
            hitMissGrid[row][col] = 'X'; // Mark hit on overlay grid
            ship.markHit(row, col);      // Mark hit on ship
            return true;
        }
    }
    
    // If no ship was hit, mark as miss
    hitMissGrid[row][col] = 'O';
    return false;
}

bool Board::allShipsSunk() const {
    for (const Ship& ship : ships) {
        if (!ship.isSunk()) {
            return false;
        }
    }
    return !ships.empty(); // Return true only if there are ships and all are sunk
}