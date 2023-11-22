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

    Player* currentPlayer;

    int currentRound = 0;

public:
    void startGame();

    Game();

    void initPlayers();

    void createBoard();

    void displayBoard();

    void placePlayers();

    bool checkPlacement(int x, int y);

    void mixTiles();

    bool checkPlacementOfTile(Tile tile, int x, int y);

    void initDefault();

    void askAction();

    void placeAction();

    void exchangeAction();

    void stoneAction();

    void robberyAction();

    int getRound();

    void nextPlayer();

    void placeTile(Tile tile, int x, int y);

    void getBonus();
};


#endif //PROJECT_GAME_H
