#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "Case.h"

class Game {
private:
    vector<vector<Case>> board;

    int amountPlayer;

    vector<Player> players;

public:
    void startGame();

    Game();

    void initPlayers();

    void createBoard();

    void displayBoard();

    void placePlayers();

    bool checkPlacement(int x, int y);
};


#endif //PROJECT_GAME_H
