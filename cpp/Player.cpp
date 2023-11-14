#include "../headers/Player.h"

Player::Player(string PlayerColor, string PlayerName, char PlayerChar) {
    this->playerColor = PlayerColor;
    this->playerName = PlayerName;
    this->playerChar = PlayerChar;
}

string Player::getPlayerColor() {
    return playerColor;
}

const string &Player::getPlayerName() const {
    return playerName;
}

char Player::getPlayerChar() const {
    return playerChar;
}



