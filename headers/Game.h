#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "Case.h"

class Game {
private:
    vector<vector<Case>> board;
    int amountPlayer;

public:
    void startGame();

    Game();

    void initPlayers();

    void createBoard();

    void displayBoard();
};


#endif //PROJECT_GAME_H
