#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <iostream>
#include <vector>
#include <map>
#include "Tile.h"

using namespace std;

class Player {
private:
    string playerColor;

    string playerName;

    char playerChar;

    int tileExchangeBonus = 0;
    int stoneBonus = 0;
    int robberyBonus = 0;

    map<char, Tile> tiles;

public:
    string getPlayerColor();

    const string &getPlayerName() const;

    char getPlayerChar() const;

    Player(string PlayerColor, string PlayerName, char PlayerChar);

    char getCurrentChar() const;

    void addTile(const Tile &tile);

    void removeTile(char id);

    Tile getTile(char id);

    int getTileExchangeBonus() const;

    void setTileExchangeBonus(int tileExchangeBonus);

    int getStoneBonus() const;

    void setStoneBonus(int stoneBonus);

    int getRobberyBonus() const;

    void setRobberyBonus(int robberyBonus);

    bool operator()(const Player &lhs, const Player &rhs) const {
        return lhs.getPlayerName() < rhs.getPlayerName();
    }


};

struct PlayerCompare {
    bool operator()(const Player &lhs, const Player &rhs) const {
        // Implémentez votre logique de comparaison ici, par exemple, comparez les identifiants
        return lhs.getPlayerName() < rhs.getPlayerName();
    }
};


#endif //PROJECT_PLAYER_H
