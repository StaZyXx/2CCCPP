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
            cout << tile[i][j];
        }
        cout << endl;
    }
}

Tile Tile::rotate() {
    vector<vector<char>> newTile;

    // Find the new dimensions after rotation
    size_t newRows = tile[0].size();
    size_t newCols = tile.size();

    for (size_t i = 0; i < newRows; ++i) {
        vector<char> row;
        bool keepSpaces = false;  // Flag to determine whether to keep spaces for the current row

        for (size_t j = 0; j < newCols; ++j) {
            char t = (i < tile[j].size()) ? tile[j][tile[j].size() - i - 1] : ' ';

            if (t == '*') {
                keepSpaces = true;  // Set the flag to true if '*' is encountered
                break;  // Exit the loop once '*' is found in the current row
            }
        }

        // Process the current row based on the keepSpaces flag
        for (size_t j = 0; j < newCols; ++j) {
            char t = (i < tile[j].size()) ? tile[j][tile[j].size() - i - 1] : ' ';

            if (keepSpaces || t == '*') {
                row.push_back(t);
            }
        }

        if (!row.empty())
            newTile.push_back(row);
    }

    // Update the tile after rotation
    tile = newTile;
    return *this;
}

Tile Tile::flip() {
    vector<vector<char>> newTile;
    for (int i = 0; i < tile.size(); ++i) {
        vector<char> row;
        row.reserve(tile[i].size());
        for (int j = 0; j < tile[i].size(); ++j) {
            row.push_back(tile[i][tile[i].size() - j - 1]);
        }
        newTile.push_back(row);
    }
    return Tile(newTile);
}
