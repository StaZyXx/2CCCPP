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

Tile Player::getCurrentTile() const {
    return currentTile;
}

void Player::setCurrentTile(Tile currentTile) {
    this->currentTile = currentTile;
}

vector<Tile> Player::getTiles() {
    return tiles;
}

vector<Tile> Player::getTiles(int amount) {
    vector<Tile> tiles;
    tiles.reserve(amount);
    for (int i = 0; i < amount; ++i) {
        tiles.push_back(this->tiles[i]);
    }
    return tiles;
}

void Player::setTiles(vector<Tile> tiles) {
    this->tiles = std::move(tiles);
}

void Player::addTile(Tile tile) {
    this->tiles.push_back(tile);
}

void Player::removeTile(Tile tile) {
    for (int i = 0; i < tiles.size(); ++i) {
        if (tiles[i].getTile() == tile.getTile()) {
            tiles.erase(tiles.begin() + i);
            break;
        }
    }
}

Tile Player::takeTile(int index) {
    Tile tile = tiles[index];
    tiles.erase(tiles.begin() + index);
    return tile;
}

Tile Player::takeFirstTile() {
    Tile tile = tiles[0];
    tiles.erase(tiles.begin());
    return tile;
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



