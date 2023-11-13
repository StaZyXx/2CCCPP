#ifndef PROJECT_CASE_H
#define PROJECT_CASE_H

#include "Player.h"

class Case {
private:
    Player* player{};

    char type;
public:
    enum BonusType {EXCHANGE_TILE, STONE_TILE, ROBBERY_TILE, NONE};
    BonusType bonus;

    Case(BonusType bonus, Player *player, char type);

    Player *getPlayer() const;

    void setPlayer(Player *player);

    char getType() const;

    void setType(char type);

};


#endif //PROJECT_CASE_H
