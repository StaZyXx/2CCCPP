#include <utility>
#include <algorithm>

#include "../headers/Tile.h"

Tile::Tile(vector<vector<char>> tile) {
    this->tile = std::move(tile);
}

vector<vector<char>> Tile::getTile() {
    return tile;
}

void Tile::display() {
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == '0'){
                cout << ' ';
            }else{
                cout << tile[i][j];
            }
        }
        cout << endl;
    }
}

Tile Tile::rotate() {
    vector<vector<char>> newTile;
    for (int i = 0; i < tile[0].size(); ++i) {
        vector<char> row;
        for (int j = tile.size() - 1; j >= 0; --j) {
            row.push_back(tile[j][i]);
        }
        newTile.push_back(row);
    }
    return {newTile};
}

Tile Tile::flip() {
    vector<vector<char>> newTile;
    for (auto & i : tile) {
        vector<char> row;
        row.reserve(i.size());
        for (int j = 0; j < i.size(); ++j) {
            row.push_back(i[i.size() - j - 1]);
        }
        newTile.push_back(row);
    }
    return {newTile};
}
