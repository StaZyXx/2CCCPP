#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <iostream>
#include <vector>
#include "Tile.h"

using namespace std;

class Player {
private:
    string playerColor;

    string playerName;

    char playerChar;

    Tile currentTile = Tile({});

    vector<Tile> tiles;

    int tileExchangeBonus = 0;
    int stoneBonus = 0;
    int robberyBonus = 0;

public:
    string getPlayerColor();

    const string &getPlayerName() const;

    char getPlayerChar() const;

    Player(string PlayerColor, string PlayerName, char PlayerChar);

    Tile getCurrentTile() const;

    void setCurrentTile(Tile currentTile);

    vector<Tile> getTiles();

    vector<Tile> getTiles(int amount);

    void setTiles(vector<Tile> tiles);

    void addTile(Tile tile);

    void removeTile(Tile tile);

    Tile takeTile(int index);

    Tile takeFirstTile();

    int getTileExchangeBonus() const;

    void setTileExchangeBonus(int tileExchangeBonus);

    int getStoneBonus() const;

    void setStoneBonus(int stoneBonus);

    int getRobberyBonus() const;

    void setRobberyBonus(int robberyBonus);
};


#endif //PROJECT_PLAYER_H
