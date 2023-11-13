#include "../headers/Player.h"

Player::Player(string PlayerColor, string PlayerName) {
    this->playerColor = PlayerColor;
    this->playerName = PlayerName;
}

string Player::getPlayerColor() {
    return playerColor;
}

string Player::getPlayerName() {
    return playerName;
}

