#ifndef PROJECT_TILE_H
#define PROJECT_TILE_H

#include <iostream>
#include <vector>

using namespace std;

class Tile {
private:
    vector<vector<char>> tile;
public:
    Tile(vector<vector<char>> tile);

    Tile(const Tile &other) {
        // Copy constructor implementation here
        this->tile = other.tile;  // Assuming your vector has a proper copy constructor
    }

    Tile &operator=(const Tile &other) {
        // Assignment operator implementation here
        if (this != &other) {
            this->tile = other.tile;  // Assuming your vector has a proper assignment operator
        }
        return *this;
    }

    vector<vector<char>> getTile();

    void display();

    Tile rotate();

    Tile flip();
};


#endif //PROJECT_TILE_H
