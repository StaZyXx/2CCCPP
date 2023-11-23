#ifndef PROJECT_TILE_H
#define PROJECT_TILE_H

#include <iostream>
#include <vector>

using namespace std;

class Tile {
private:
    int id;
    vector<vector<char>> tile;
public:
    Tile(int id, vector<vector<char>> tile);

    int getId() const;

    vector<vector<char>> getTile() const;


    void display();

    Tile rotate();

    Tile flip();

    void displayInline(int row);

    void setConsoleColor(int textColor, int bgColor);

    void resetConsoleColor();
};


#endif //PROJECT_TILE_H
