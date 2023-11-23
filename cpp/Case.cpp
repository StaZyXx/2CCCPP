#include "../headers/Case.h"


Player *Case::getPlayer() const {
    return player;
}

void Case::setPlayer(Player *player) {
    Case::player = player;
}

Case::Case(Case::BonusType bonus, Player *player, char type) {
    this->bonus = bonus;
    this->player = player;
    this->type = type;
}

char Case::getType() const {
    return type;
}

void Case::setType(char type) {
    Case::type = type;
}

bool Case::canTouch() {
    return touch;
}

bool Case::canTouch(Player *currentPlayer){
    if (this->player == nullptr) {
        return canTouch();
    } else if (this->player->getPlayerName() == currentPlayer->getPlayerName()) {
        return true;
    } else {
        return false;
    }
}

void Case::setTouch(bool touch) {
    this->touch = touch;
}

bool Case::getIsStone() {
    return isStone;
}

void Case::setStone(bool value) {
    this->isStone = value;
}


