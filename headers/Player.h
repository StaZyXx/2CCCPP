#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H
#include <iostream>
#include <vector>

using namespace std;

class Player {
private:
    string playerColor;
    string playerName;
public:
    string getPlayerColor();

    string getPlayerName();

public:
    Player(string PlayerColor, string PlayerName);
};


#endif //PROJECT_PLAYER_H
