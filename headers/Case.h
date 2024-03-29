#ifndef PROJECT_CASE_H
#define PROJECT_CASE_H

#include "Player.h"

class Case {
private:
    Player* player{};

    char type;

    bool touch = false;

    bool isStone = false;
public:
    enum BonusType {EXCHANGE_TILE, STONE_TILE, ROBBERY_TILE, NONE};
    BonusType bonus;

    Case(BonusType bonus, Player *player, char type);

    bool canTouch();

    void setTouch(bool touch);

    Player *getPlayer() const;

    void setPlayer(Player *player);

    char getType() const;

    void setType(char type);

    bool canTouch(Player *currentPlayer);

    void setStone(bool value);

    bool getIsStone() const;
};


#endif //PROJECT_CASE_H
