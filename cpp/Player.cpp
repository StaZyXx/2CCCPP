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

char Player::getCurrentChar() const {
    return tiles.size() + 64;
}

void Player::addTile(const Tile& tile) {
    tiles.insert(pair<char, Tile>(65 - tiles.size(), tile));
}

void Player::removeTile(char id) {
    tiles.erase(id);
}

Tile Player::getTile(char id) {
    return tiles.at(id);
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



