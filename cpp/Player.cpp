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

int Player::getTileExchangeBonus() const {
    return tileExchangeBonus;
}

void Player::setTileExchangeBonus(int tileExchangeBonus) {
    Player::tileExchangeBonus = tileExchangeBonus;
}

int Player::getStoneBonus() const {
    return stoneBonus;
}

void Player::setStoneBonus(int stoneBonus) {
    Player::stoneBonus = stoneBonus;
}

int Player::getRobberyBonus() const {
    return robberyBonus;
}

void Player::setRobberyBonus(int robberyBonus) {
    Player::robberyBonus = robberyBonus;
}



