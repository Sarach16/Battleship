#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>

class Ship {
private:
    std::string name;
    int size;
    std::vector<std::pair<int, int>> coordinates; // Stores ship location
    std::vector<bool> hitStatus; // Track which parts of the ship are hit

public:
    Ship(std::string name, int size); // Constructor
    void setPosition(std::vector<std::pair<int, int>> coords);
    std::vector<std::pair<int, int>> getPosition() const;
    std::string getName() const;
    int getSize() const; // New method
    
    // New methods for hit tracking
    bool checkHit(int row, int col); // Returns true if position matches a ship segment
    void markHit(int row, int col); // Mark a position as hit
    bool isSunk() const; // Check if all segments are hit
};

#endif