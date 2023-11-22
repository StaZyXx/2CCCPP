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

    int tileExchangeBonus = 5;
    int stoneBonus = 5;
    int robberyBonus = 5;

public:
    string getPlayerColor();

    const string &getPlayerName() const;

    char getPlayerChar() const;

    Player(string PlayerColor, string PlayerName, char PlayerChar);

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
    bool operator() (const Player& lhs, const Player& rhs) const {
        // Implémentez votre logique de comparaison ici, par exemple, comparez les identifiants
        return lhs.getPlayerName() < rhs.getPlayerName();
    }
};


#endif //PROJECT_PLAYER_H
