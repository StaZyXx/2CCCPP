#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "Case.h"
#include "Tile.h"

class Game {
private:
    vector<vector<Case>> board;

    Tile currentTile = Tile(0, {});

    vector<Tile> allTiles;

    int amountPlayer;

    vector<Player> players;

    Player *currentPlayer;

    int currentRound = 0;

public:
    void startGame();

    Game();

    Tile getCurrentTile() const;

    void setCurrentTile(Tile currentTile);

    Tile takeFirstTile();

    Tile takeTile(int index);

    void setTile(Tile tile, int index);

    void setFirstTile(const Tile& tile);

    void removeTile(const Tile& tile);

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
    void deleteTile(Tile tile, int x, int y);

    void getBonus();

    Player checkWinner();

    void display5Tiles();

    void placeLastTile();

    bool isInBoard(int x, int y);
};


#endif //PROJECT_GAME_H
