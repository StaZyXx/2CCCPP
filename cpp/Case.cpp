#include "../headers/Case.h"

Case::Case() = default;

Player *Case::getPlayer() const {
    return player;
}

void Case::setPlayer(Player *player) {
    Case::player = player;
}

char Case::getPlayerChar() const {
    return playerChar;
}

void Case::setPlayerChar(char playerChar) {
    Case::playerChar = playerChar;
}

