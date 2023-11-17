#include "../headers/Game.h"
#include "../headers/Tile.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

Game::Game() = default;

void Game::startGame() {
    //initPlayers();
    //createBoard();
    //displayBoard();
    //placePlayers();
    mixTiles();
}

void Game::initPlayers() {
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
        players.push_back(Player(playerColor, playerName, playerName[0]));
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
            aCase.setTouch(true);
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
                aCase.setTouch(true);
                board[x][y] = aCase;
                amountBonusExchangeTile--;
            } else if (bonusType == 1 && amountBonusStoneTile > 0) {
                Case aCase(Case::STONE_TILE, nullptr, 'S');
                aCase.setTouch(true);
                board[x][y] = aCase;
                amountBonusStoneTile--;
            } else if (bonusType == 2 && amountBonusRobberyTile > 0) {
                Case aCase(Case::ROBBERY_TILE, nullptr, 'R');
                aCase.setTouch(true);
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
    for (auto &i: board) {
        for (int j = 0; j < board.size(); ++j) {
            cout << i[j].getType() << " ";
        }
        cout << endl;
    }
}

void Game::placePlayers() {
    for (int i = 0; i < players.size(); ++i) {
        int x, y;
        bool validPlacement = false;
        while (!validPlacement) {
            cout << "Joueur " << i << " placez votre case de depart" << endl;
            cin >> x >> y;
            if (checkPlacement(x, y)) {
                board[x][y].setPlayer(&players[i]);
                board[x][y].setType(players[i].getPlayerChar());
                board[x][y].setTouch(false);
                displayBoard();
                validPlacement = true;
            } else {
                cout << "Merci de rentrer un placement valide" << endl;
            }
        }
    }
}


bool Game::checkPlacement(int x, int y) {
    //Check top-left corner
    if (x == 0 && y == 0) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch() && board[x][y + 1].canTouch();
    }
    //Check top-right corner
    if (x == 0 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch() && board[x][y - 1].canTouch();
    }
    //Check bottom-right corner
    if (x == board.size() - 1 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x - 1][y].canTouch() && board[x][y - 1].canTouch();
    }
    //Check bottom-left corner
    if (x == board.size() - 1 && y == 0) {
        return board[x][y].canTouch() && board[x - 1][y].canTouch() && board[x][y + 1].canTouch();
    }
    //Check top side
    if (x == 0 && y != 0 && y != board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch() && board[x][y + 1].canTouch() && board[x][y - 1].canTouch();
    }
    //Check right side
    if (x != 0 && x != board.size() - 1 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch() && board[x - 1][y].canTouch() && board[x][y - 1].canTouch();
    }
    //Check bottom side
    if (x == board.size() - 1 && y != 0 && y != board.size() - 1) {
        return board[x][y].canTouch() && board[x - 1][y].canTouch() && board[x][y + 1].canTouch() && board[x][y - 1].canTouch();
    }
    //Check left side
    if (x != 0 && x != board.size() - 1 && y == 0) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch() && board[x - 1][y].canTouch() && board[x][y + 1].canTouch();
    }
    //Except all sides and corners
    return board[x][y].canTouch() && board[x + 1][y].canTouch() && board[x - 1][y].canTouch() && board[x][y + 1].canTouch() && board[x][y - 1].canTouch();
}

void Game::mixTiles() {
    for (int i = 1; i <= 96; ++i) {
        string file = "../tiles/" + to_string(i) + ".txt";
        ifstream myfile(file);
        if (!myfile.is_open()) {
            cerr << "Error opening file: " << file << endl;
        }
        if (myfile.is_open()) {
            string line;
            vector<string> lines;
            vector<vector<char>> tile;
            while (getline(myfile, line)) {
                lines.push_back(line);
            }
            for (int j = 0; j < lines.size(); ++j) {
                string l = lines[j];
                vector<char> temporary;
                for (int k = 0; k < l.length(); ++k) {
                    temporary.push_back(l[k]);
                }
                tile.push_back(temporary);
            }
            Tile tile1(tile);
            allTiles.push_back(tile1);
        }
    }
    shuffle(allTiles.begin(), allTiles.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
}
