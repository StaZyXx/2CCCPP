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

    vector<vector<char>> getTile();

    void display();
};


#endif //PROJECT_TILE_H
