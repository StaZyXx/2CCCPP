#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H
#include <iostream>
#include <vector>

using namespace std;

class Player{
private:
    vector<Player> players;

    string playerColor;

    string playerName;

    char playerChar;
public:
    string getPlayerColor();

    const string &getPlayerName() const;

    char getPlayerChar() const;

    Player(string PlayerColor, string PlayerName, char PlayerChar);
};


#endif //PROJECT_PLAYER_H
