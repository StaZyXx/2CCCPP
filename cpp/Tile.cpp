#include "../headers/Tile.h"

Tile::Tile(vector<vector<char>> tile) {
    this->tile = tile;
}

vector<vector<char>> Tile::getTile() {
    return tile;
}

void Tile::display(){
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            cout << tile[i][j];
        }
        cout << endl;
    }
}
