#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

class Game {
private:
    int amountPlayer{};
public:
    void startGame();
    Game();

    void initPlayers();

    void createBoard();
};


#endif //PROJECT_GAME_H
