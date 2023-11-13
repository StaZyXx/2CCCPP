#include "../headers/Game.h"
#include "../headers/Player.h"
#include "../headers/Case.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
void Game::startGame() {
    //initPlayers();
    createBoard();
    displayBoard();
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
    int boardSize;
    if (amountPlayer <= 4) {
        boardSize = 20;
    } else {
        boardSize = 30;
    }
    for (int i = 0; i < boardSize - 1; ++i) {
        vector<Case> line;
        for (int j = 0; j < boardSize - 1; ++j) {
            Case aCase(Case::NONE, nullptr, '.');
            line.push_back(aCase);
        }
        board.push_back(line);
    }
    int amountBonusExchangeTile = round(amountPlayer * 1.5);
    int amountBonusStoneTile = round(amountPlayer * 0.5);
    int amountBonusRobberyTile = amountPlayer;
    bool allBonusPlaced = false;
    while (!allBonusPlaced) {
        int x = rand() % boardSize;
        int y = rand() % boardSize;
        int bonusType = rand() % 3;
        if (board[x][y].bonus == Case::NONE) {
            if (bonusType == 0 && amountBonusExchangeTile > 0) {
                Case aCase(Case::EXCHANGE_TILE, nullptr, 'E');
                board[x][y] = aCase;
                amountBonusExchangeTile--;
            } else if (bonusType == 1 && amountBonusStoneTile > 0) {
                Case aCase(Case::STONE_TILE, nullptr, 'S');
                board[x][y] = aCase;
                amountBonusStoneTile--;
            } else if (bonusType == 2 && amountBonusRobberyTile > 0) {
                Case aCase(Case::ROBBERY_TILE, nullptr, 'R');
                board[x][y] = aCase;
                amountBonusRobberyTile--;
            }
        }
        if (amountBonusExchangeTile == 0 && amountBonusStoneTile == 0 && amountBonusRobberyTile == 0) {
            allBonusPlaced = true;
        }
    }
}

void Game::displayBoard() {
    for (auto & i : board) {
        for (int j = 0; j < board.size(); ++j) {
            cout << i[j].getType() << " ";
        }
        cout << endl;
    }
}