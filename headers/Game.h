#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "Case.h"
#include "Tile.h"

class Game {
private:
    vector<vector<Case>> board;

    vector<Tile> allTiles;

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

    void mixTiles();
};


#endif //PROJECT_GAME_H
