#include "../headers/Game.h"
#include "../headers/Player.h"
#include "../headers/Case.h"
#include <iostream>
#include <vector>

using namespace std;

Game::Game() = default;

void Game::startGame() {
    initPlayers();
    createBoard();

}

void Game::initPlayers() {
    vector<Player> players;
    vector<string> colors = {"Rouge", "Bleu", "Vert", "Jaune", "Violet", "Blanc", "Rose", "Orange", "Marron"};
    bool validPlayerAmount = false;
    while (!validPlayerAmount) {
        cout << "Entrez le nombre de joueurs :";
        cin >> amountPlayer;
        if (amountPlayer >= 2 && amountPlayer <= 9) {
            validPlayerAmount = true;
        } else {
            validPlayerAmount = false;
            cout << "Merci de rentrer un chiffre entre 2 et 9 joueurs." << endl;
        }
    }
    for (int i = 0; i < amountPlayer; ++i) {
        string playerName;
        cout << "Entrez le nom du joueur " << i + 1 << " :";
        cin >> playerName;
        cout << "Voici les couleurs restantes: " << endl;
        for (int j = 0; j < colors.size(); ++j) {
            if (j == colors.size() - 1) {
                cout << colors[j] << endl;
            } else {
                cout << colors[j] << ", ";
            }
        }
        bool colorExist = false;
        string playerColor;
        while (!colorExist) {
            cout << "Entrez la couleur du joueur " << i + 1 << " :";
            cin >> playerColor;
            for (int j = 0; j < colors.size(); ++j) {
                if (playerColor == colors[j]) {
                    colorExist = true;
                    colors.erase(colors.begin() + j);
                }
            }
            if (!colorExist) {
                cout << "Cette couleur n'existe pas" << endl;
            }
        }
        players.push_back(Player(playerColor, playerName));
    }
    for (auto &player: players) {
        cout << "Name: " << player.getPlayerName() << " | Color: " << player.getPlayerColor() << endl;
    }
}

void Game::createBoard() {
    vector<vector<Case>> board;
    int boardSize;
    if (amountPlayer <= 4) {
        boardSize = 20;
    } else {
        boardSize = 30;
    }
    for (int i = 0; i < boardSize - 1; ++i) {
        for (int j = 0; j < boardSize - 1; ++j) {
            Case aCase;
            board[i].push_back(aCase.setPlayerChar('.'));

        }


    }

}
