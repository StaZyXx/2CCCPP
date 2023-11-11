#ifndef PROJECT_CASE_H
#define PROJECT_CASE_H

#include "Player.h"

class Case {
private:
    Player* player;
    char playerChar;

public:
    Case();

    Player *getPlayer() const;

    void setPlayer(Player *player);

    char getPlayerChar() const;

    void setPlayerChar(char playerChar);
};


#endif //PROJECT_CASE_H
