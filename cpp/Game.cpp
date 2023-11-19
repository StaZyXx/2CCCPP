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

const int MAX_ROUND = 9;

void Game::startGame() {
    //initPlayers();
    initDefault();
    while (getRound() != MAX_ROUND) {
        askAction();
        nextPlayer();
    }
}

void Game::initDefault() {
    amountPlayer = 2;
    players.push_back(Player("Rouge", "Joueur 1", '1'));
    players.push_back(Player("Bleu", "Joueur 2", '2'));
    currentPlayer = &players[0];
    createBoard();
    displayBoard();
    mixTiles();
    placePlayers();
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
    string *alphabet = new string[board.size()];

    for (int i = 0; i < board.size(); ++i) {
        alphabet[i] = (char) (i + 65);
    }
    cout << " " << endl;
    cout << "  ";
    for (int i = 0; i < board.size(); ++i) {
        cout << alphabet[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < board.size(); ++i) {
        cout << alphabet[i] << " ";
        for (int j = 0; j < board.size(); ++j) {
            cout << board[i][j].getType() << " ";
        }
        cout << endl;
    }
}

void Game::placePlayers() {
    for (int i = 0; i < players.size(); ++i) {
        string xChar, yChar;
        bool validPlacement = false;
        while (!validPlacement) {
            cout << "Joueur " << i << " placez votre case de depart" << endl;
            cin >> xChar >> yChar;
            int x = (int) xChar[0] - 65;
            int y = (int) yChar[0] - 65;
            if (checkPlacement(x, y)) {
                board[x][y].setPlayer(&players[i]);
                board[x][y].setType(players[i].getPlayerChar());
                board[x][y].setTouch(false);
                cout << allTiles.size() << endl;
                players[i].setTiles(allTiles);
                players[i].setCurrentTile(allTiles[0]);
                displayBoard();
                validPlacement = true;
            } else {
                cout << "Merci de rentrer un placement valide" << endl;
            }
        }
    }
}

void Game::placeTile(Tile tile, int x, int y) {
    for (int i = 0; i < tile.getTile().size(); ++i) {
        for (int j = 0; j < tile.getTile()[i].size(); ++j) {
            if (tile.getTile()[i][j] == '*') {
                board[x + i][y + j].setPlayer(currentPlayer);
                board[x + i][y + j].setType(currentPlayer->getPlayerChar());
                board[x + i][y + j].setTouch(false);
            }
        }
    }
}

bool Game::checkPlacementOfTile(Tile tile, int x, int y) {
    for (int i = 0; i < tile.getTile().size(); ++i) {
        for (int j = 0; j < tile.getTile()[i].size(); ++j) {
            if (tile.getTile()[i][j] == '*') {
                if (!checkPlacement(x + i, y + j)) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Game::checkPlacement(int x, int y) {
    // Le problème ici c'est que on check pas si la case +1 ou -1 est au joueur qui joue ducoup on peut pas coller les cases entre elles
    // Autre problème pas sur, mais si on colle 2 tile ensemble, on peut pas en mettre une autre a coté vu que c'est une case et donc qu'on peut pas la toucher

    //Check top-left corner
    if (x == 0 && y == 0) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) && board[x][y + 1].canTouch(currentPlayer);
    }
    //Check top-right corner
    if (x == 0 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) && board[x][y - 1].canTouch();
    }
    //Check bottom-right corner
    if (x == board.size() - 1 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x - 1][y].canTouch(currentPlayer) && board[x][y - 1].canTouch(currentPlayer);
    }
    //Check bottom-left corner
    if (x == board.size() - 1 && y == 0) {
        return board[x][y].canTouch() && board[x - 1][y].canTouch(currentPlayer) && board[x][y + 1].canTouch(currentPlayer);
    }
    //Check top side
    if (x == 0 && y != 0 && y != board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) && board[x][y + 1].canTouch(currentPlayer) &&
               board[x][y - 1].canTouch(currentPlayer);
    }
    //Check right side
    if (x != 0 && x != board.size() - 1 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) && board[x - 1][y].canTouch(currentPlayer) &&
               board[x][y - 1].canTouch(currentPlayer);
    }
    //Check bottom side
    if (x == board.size() - 1 && y != 0 && y != board.size() - 1) {
        return board[x][y].canTouch() && board[x - 1][y].canTouch(currentPlayer) && board[x][y + 1].canTouch(currentPlayer) &&
               board[x][y - 1].canTouch(currentPlayer);
    }
    //Check left side
    if (x != 0 && x != board.size() - 1 && y == 0) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) && board[x - 1][y].canTouch(currentPlayer) &&
               board[x][y + 1].canTouch();
    }
    //Except all sides and corners
    return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) && board[x - 1][y].canTouch(currentPlayer) &&
           board[x][y + 1].canTouch(currentPlayer) && board[x][y - 1].canTouch(currentPlayer);
}

void Game::mixTiles() {
    for (int i = 1; i <= 96; ++i) {
        string file = "../tiles/" + to_string(i) + ".txt";
        ifstream tileFileStream(file);
        if (!tileFileStream.is_open()) {
            cerr << "Error opening file: " << file << endl;
        }
        if (tileFileStream.is_open()) {
            string line;
            vector<string> lines;
            vector<vector<char>> tile;
            while (getline(tileFileStream, line)) {
                lines.push_back(line);
            }
            for (const auto &l: lines) {
                vector<char> temporary;
                for (char k: l) {
                    temporary.push_back(k);
                }
                tile.push_back(temporary);
            }
            Tile tile1(tile);
            allTiles.push_back(tile1);
        }
    }
    shuffle(allTiles.begin(), allTiles.end(),
            std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
}

void Game::askAction() {
    cout << "Joueur " << currentPlayer->getPlayerName() << " c'est a vous de jouer" << endl;
    cout << "1. Placer une tuile (P)" << endl;
    cout << "2. Echanger une tuile - " << currentPlayer->getTileExchangeBonus() << " restante (E)" << endl;
    cout << "3. Voler une tuile - " << currentPlayer->getRobberyBonus() << " restante (V)" << endl;
    cout << "4. Poser un pion - " << currentPlayer->getStoneBonus() << " restant (S)" << endl;

    bool validAction = false;

    while (!validAction) {
        string action;

        cin >> action;

        switch (tolower(action[0])) {
            case 'p':
                placeAction();
                validAction = true;
                break;
            case 'e':
                if (currentPlayer->getTileExchangeBonus() > 0) {
                    exchangeAction();
                    validAction = true;
                } else {
                    cout << "Vous n'avez plus de bonus d'echange" << endl;
                }
                break;
            case 'v':
                if (currentPlayer->getRobberyBonus() > 0) {
                    robberyAction();
                    validAction = true;
                } else {
                    cout << "Vous n'avez plus de bonus de vol" << endl;
                }
                break;
            case 's':
                if (currentPlayer->getStoneBonus() > 0) {
                    stoneAction();
                    validAction = true;
                } else {
                    cout << "Vous n'avez plus de bonus de pierre" << endl;
                }
                break;
        }
    }

}

void Game::placeAction() {
    string xChar, yChar;
    bool validPlacement = false;

    string action;
    while (!validPlacement) {
        cout << "La tuile a poser : " << endl;
        Tile tile = currentPlayer->getCurrentTile();
        tile.display();

        cout << "Que voulez vous faire ?" << endl;
        cout << "1. Rotation (R)" << endl;
        cout << "2. Flip (F)" << endl;
        cout << "3. Poser la tuile (P)" << endl;

        cin >> action;

        switch (tolower(action[0])) {
            case 'r':
                currentPlayer->setCurrentTile(tile.rotate());
                break;
            case 'f':
                currentPlayer->setCurrentTile(tile.flip());
                break;
            case 'p':
                while (!validPlacement) {
                    cout << "Entrez les coordonnees de la tuile :" << endl;
                    cin >> xChar >> yChar;
                    int x = (int) xChar[0] - 65;
                    int y = (int) yChar[0] - 65;

                    if (checkPlacementOfTile(tile, x, y)) {
                        placeTile(tile, x, y);
                        displayBoard();
                        validPlacement = true;
                    } else {
                        cout << "Merci de rentrer un placement valide" << endl;
                    }
                }
                break;
        }
    }
}

void Game::exchangeAction() {
    bool validExchange = false;

    while (!validExchange) {
        for (int i = 0; i < 5; ++i) {
            cout << "Tuile " << i + 1 << " : " << endl;
            currentPlayer->getTiles()[i].display();
        }

        int tileToExchange;

        cout << "Quelle tuile voulez vous echanger ?" << endl;

        cin >> tileToExchange;

        Tile tile = currentPlayer->takeTile(tileToExchange - 1);

        cout << "Tuile " << tileToExchange << " : " << endl;

        tile.display();

        cout << "êtes vous sur de vouloir echanger cette tuile ? (O/N)" << endl;

        string answer;

        cin >> answer;

        if (tolower(answer[0]) == 'o') {
            //FIX LA POSITION QUAND ON RE RAJOUTE LA TUILE
            currentPlayer->addTile(currentPlayer->getCurrentTile());
            currentPlayer->setCurrentTile(tile);
            currentPlayer->removeTile(tile);
            currentPlayer->setTileExchangeBonus(currentPlayer->getTileExchangeBonus() - 1);
        } else {
            currentPlayer->addTile(tile);
            askAction();
            break;
        }
    }

}

void Game::stoneAction() {
    bool validStone = false;

    while (!validStone) {
        string xChar, yChar;

        cout << "Entrez les coordonnees de la tuile :" << endl;
        cin >> xChar >> yChar;
        int x = (int) xChar[0] - 65;
        int y = (int) yChar[0] - 65;

        if (board[x][y].getType() == currentPlayer->getPlayerChar()) {
            //board[x][y].setStone(true);
            currentPlayer->setStoneBonus(currentPlayer->getStoneBonus() - 1);
            validStone = true;
        } else {
            cout << "Merci de rentrer un placement valide" << endl;
        }
    }
}

void Game::robberyAction() {
    bool validRobbery = false;

    while (!validRobbery) {
        string xChar, yChar;

        cout << "Entrez les coordonnees de la tuile :" << endl;
        cin >> xChar >> yChar;
        int x = (int) xChar[0] - 65;
        int y = (int) yChar[0] - 65;

        if (board[x][y].getType() != currentPlayer->getPlayerChar() && board[x][y].getType() != '.') {
            board[x][y].setPlayer(currentPlayer);
            board[x][y].setType(currentPlayer->getPlayerChar());
            board[x][y].setTouch(false);
            currentPlayer->setRobberyBonus(currentPlayer->getRobberyBonus() - 1);
            validRobbery = true;
        } else {
            cout << "Merci de rentrer un placement valide" << endl;
        }
    }
}

int Game::getRound() {
    return currentRound;
}

void Game::nextPlayer() {
    if (currentPlayer == nullptr) {
        currentPlayer = &players[0];
    } else {
        for (int i = 0; i < players.size(); ++i) {
            if (currentPlayer == &players[i]) {
                if (i == players.size() - 1) {
                    currentPlayer = &players[0];
                    currentRound++;
                } else {
                    currentPlayer = &players[i + 1];
                }
            }
        }
    }
}




