#include <iostream>
#include <windows.h>
#include "headers/Game.h"

#pragma comment(lib, "winmm.lib")

int main() {
    Game game = Game();
    //PlaySound("songs/mysound.wav", NULL, SND_FILENAME | SND_SYNC);
    game.startGame();
    /*Player *player;
    player = new Player("red", "player1", '1');

    Tile tile = Tile({{' ', '*', ' '},
                      {'*', '*'},
                      {'*'},
                      {'*'},
                      {'*'},
                      {'*'}
                     });

    player->setCurrentTile(tile);

    player->getCurrentTile().display();

    player->setCurrentTile(player->getCurrentTile().rotate());

    player->getCurrentTile().display();

    player->setCurrentTile(player->getCurrentTile().rotate());
    player->getCurrentTile().display();
    player->setCurrentTile(player->getCurrentTile().rotate());
    player->getCurrentTile().display();
    player->setCurrentTile(player->getCurrentTile().rotate());
    player->getCurrentTile().display();*/
    return 0;
}
