#include <utility>
#include <algorithm>
#include <windows.h>

#include "../headers/Tile.h"


using namespace std;
void Tile::setConsoleColor(int textColor, int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor +(bgColor * 16)));
}
void Tile::resetConsoleColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

Tile::Tile(int id, vector<vector<char>> tile) {
    this->id = id;
    this->tile = std::move(tile);
}

vector<vector<char>> Tile::getTile() const {
    return tile;
}

void Tile::display() {
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == '0') {
                cout << ' ';
            } else if (tile[i][j] == '1') {
                setConsoleColor(4, 4);
                cout << tile[i][j];
                resetConsoleColor();
            } else {
                setConsoleColor(8, 8);
                cout << tile[i][j];
                resetConsoleColor();
            }
        }
        cout << endl;
    }
}

void Tile::displayInline(int row) {
    for (int j = 0; j < tile[row].size(); ++j) {
        if (tile[row][j] == '0') {
            cout << ' ';
        } else if (tile[row][j] == '1') {
            setConsoleColor(4, 4);
            cout << tile[row][j];
            resetConsoleColor();
        } else {
            setConsoleColor(8, 8);
            cout << tile[row][j];
            resetConsoleColor();
        }
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
    return {id, newTile};
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
    return {id, newTile};
}

int Tile::getId() const {
    return id;
}
