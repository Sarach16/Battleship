#include "Ship.h"

Ship::Ship(std::string name, int size) : name(name), size(size) {}

void Ship::setPosition(std::vector<std::pair<int, int>> coords) {
    coordinates = coords;
    hitStatus.resize(size, false); // Initialize all segments as not hit
}

std::vector<std::pair<int, int>> Ship::getPosition() const {
    return coordinates;
}

std::string Ship::getName() const {
    return name;
}

int Ship::getSize() const {
    return size;
}

bool Ship::checkHit(int row, int col) {
    for (const auto& coord : coordinates) {
        if (coord.first == row && coord.second == col) {
            return true;
        }
    }
    return false;
}

void Ship::markHit(int row, int col) {
    for (size_t i = 0; i < coordinates.size(); i++) {
        if (coordinates[i].first == row && coordinates[i].second == col) {
            hitStatus[i] = true;
            break;
        }
    }
}

bool Ship::isSunk() const {
    for (bool hit : hitStatus) {
        if (!hit) return false;
    }
    return true;
}