#include "../headers/Game.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

Game::Game() = default;

const int MAX_ROUND = 3;

void Game::startGame() {
    //initPlayers();
    initDefault();
    while (getRound() != MAX_ROUND) {
        askAction();
        getBonus();
        nextPlayer();
    }
    placeLastTile();
    checkWinner();
}

void Game::initDefault() {
    amountPlayer = 2;

    players.push_back(Player("Rouge", "Joueur 1", '1'));
    players.push_back(Player("Bleu", "Joueur 2", '2'));
    currentPlayer = &players[0];
    createBoard();
    mixTiles();
    displayBoard();
    placePlayers();

    /*for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 2; ++j) {

            board[i][j].setTouch(false);
            board[i][j].setPlayer(&players[0]);
            board[i][j].setType(players[0].getPlayerChar());
        }
    }

    for (int i = 10; i < 16; ++i) {
        for (int j = 10; j < 16; ++j) {

            board[i][j].setTouch(false);
            board[i][j].setPlayer(&players[1]);
            board[i][j].setType(players[1].getPlayerChar());
        }
    }*/
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
}

void Game::createBoard() {
    int boardSize;
    if (amountPlayer <= 4) {
        boardSize = 20;
    } else {
        boardSize = 30;
    }
    for (int i = 0; i < boardSize; ++i) {
        vector<Case> line;
        for (int j = 0; j < boardSize; ++j) {
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

void Game::display5Tiles() {
    // Trouver la hauteur maximale et la largeur maximale parmi toutes les tuiles
    int maxHeight = 0;
    int maxWidth = 0;
    for (const Tile &tile: allTiles) {
        int tileHeight = tile.getTile().size();
        int tileWidth = tile.getTile()[0].size(); // On suppose que toutes les lignes de la tuile ont la même largeur
        if (tileHeight > maxHeight) {
            maxHeight = tileHeight;
        }
        if (tileWidth > maxWidth) {
            maxWidth = tileWidth;
        }
    }

    // Afficher les tuiles
    for (int i = 0; i < maxHeight; ++i) {
        for (int j = 0; j < 5; ++j) {
            vector<vector<char>> currentTile = allTiles[j].getTile();

            if (i < currentTile.size()) {
                int spaces = maxWidth - currentTile[i].size();
                allTiles[j].displayInline(i);
                for (int k = 0; k < spaces; ++k) {
                    cout << " "; // Ajouter des espaces pour aligner les tuiles
                }
            } else {
                // Si la tuile est plus petite que maxSize, afficher des espaces
                for (int k = 0; k < maxWidth; ++k) {
                    cout << " ";
                }
            }
            cout << "    "; // Ajouter de l'espace entre les tuiles
        }
        cout << endl;
    }
}

void Game::displayBoard() {
    cout << " " << endl;
    cout << string(to_string(board.size()).length() + 1, ' ');
    for (int i = 0; i < board.size(); ++i) {
        int amountSpace = 3 - to_string(i).length();
        cout << i << string(amountSpace, ' ');
    }
    cout << endl;
    for (int i = 0; i < board.size(); ++i) {
        int amountSpace = 3 - to_string(i).length();
        cout << i << string(amountSpace, ' ');
        for (int j = 0; j < board.size(); ++j) {
            cout << board[i][j].getType() << "  ";
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
                cout << allTiles.size() << endl;
                displayBoard();
                validPlacement = true;
            } else {
                cout << "Merci de rentrer un placement valide" << endl;
            }
        }
    }
}

void Game::placeTile(Tile tile, int x, int y) {
    currentPlayer->addTile(tile);

    int startX = -1;
    int startY = -1;
    for (int i = 0; i < tile.getTile().size(); ++i) {
        for (int j = 0; j < tile.getTile()[i].size(); ++j) {
            if (tile.getTile()[i][j] == '1') {
                startX = i;
                startY = j;
                break;
            }
        }
        if (startX != -1) {
            break;
        }
    }
    for (int i = 0; i < tile.getTile().size(); ++i) {
        for (int j = 0; j < tile.getTile()[i].size(); ++j) {
            if (tile.getTile()[i][j] != '0') {
                board[x + i - startX][y + j - startY].setPlayer(currentPlayer);
                board[x + i - startX][y + j - startY].setType(currentPlayer->getCurrentChar());
                board[x + i - startX][y + j - startY].setTouch(false);
            }
        }
    }

    removeTile(tile);
    currentTile = takeFirstTile();
}

bool Game::checkPlacementOfTile(Tile tile, int x, int y) {
    for (int i = 0; i < tile.getTile().size(); ++i) {
        for (int j = 0; j < tile.getTile()[i].size(); ++j) {
            if (tile.getTile()[i][j] != '0') {
                int startX = -1;
                int startY = -1;
                for (int k = 0; k < tile.getTile().size(); ++k) {
                    for (int l = 0; l < tile.getTile()[k].size(); ++l) {
                        if (tile.getTile()[k][l] == '1') {
                            startX = k;
                            startY = l;
                            break;
                        }
                    }
                    if (startX != -1) {
                        break;
                    }
                }
                if (isInBoard(x + i - startX, y + j - startY) || isInBoard(x - startX + 1, y - startY + 1) ||
                    !checkPlacement(x + i, y + j)) {
                    cout << "La tuile ne peut pas etre placee ici" << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

bool Game::isInBoard(int x, int y) {
    return x >= 0 && x < board.size() && y >= 0 && y < board.size();
}

bool Game::checkPlacement(int x, int y) {
    //Check top-left corner
    if (x == 0 && y == 0) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) &&
               board[x][y + 1].canTouch(currentPlayer);
    }
    //Check top-right corner
    if (x == 0 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) && board[x][y - 1].canTouch();
    }
    //Check bottom-right corner
    if (x == board.size() - 1 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x - 1][y].canTouch(currentPlayer) &&
               board[x][y - 1].canTouch(currentPlayer);
    }
    //Check bottom-left corner
    if (x == board.size() - 1 && y == 0) {
        return board[x][y].canTouch() && board[x - 1][y].canTouch(currentPlayer) &&
               board[x][y + 1].canTouch(currentPlayer);
    }
    //Check top side
    if (x == 0 && y != 0 && y != board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) &&
               board[x][y + 1].canTouch(currentPlayer) &&
               board[x][y - 1].canTouch(currentPlayer);
    }
    //Check right side
    if (x != 0 && x != board.size() - 1 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) &&
               board[x - 1][y].canTouch(currentPlayer) &&
               board[x][y - 1].canTouch(currentPlayer);
    }
    //Check bottom side
    if (x == board.size() - 1 && y != 0 && y != board.size() - 1) {
        return board[x][y].canTouch() && board[x - 1][y].canTouch(currentPlayer) &&
               board[x][y + 1].canTouch(currentPlayer) &&
               board[x][y - 1].canTouch(currentPlayer);
    }
    //Check left side
    if (x != 0 && x != board.size() - 1 && y == 0) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) &&
               board[x - 1][y].canTouch(currentPlayer) &&
               board[x][y + 1].canTouch();
    }
    //Except all sides and corners
    if (x != 0 && x != board.size() - 1 && y != 0 && y != board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) &&
               board[x - 1][y].canTouch(currentPlayer) && board[x][y + 1].canTouch(currentPlayer) &&
               board[x][y - 1].canTouch(currentPlayer);
    }
    cout << "La tuile ne peut pas etre placee ici" << endl;
    return false;
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
            Tile tile1(i, tile);
            allTiles.push_back(tile1);
        }
    }
    shuffle(allTiles.begin(), allTiles.end(),
            default_random_engine(chrono::system_clock::now().time_since_epoch().count()));

    currentTile = takeFirstTile();
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
    int x, y;
    bool validPlacement = false;

    string action;
    while (!validPlacement) {
        cout << "La tuile a poser : " << endl;
        currentTile.display();

        cout << "Que voulez vous faire ?" << endl;
        cout << "1. Rotation (R)" << endl;
        cout << "2. Flip (F)" << endl;
        cout << "3. Poser la tuile (P)" << endl;

        cin >> action;

        switch (tolower(action[0])) {
            case 'r':
                currentTile = currentTile.rotate();
                break;
            case 'f':
                currentTile = currentTile.flip();
                break;
            case 'p':
                while (!validPlacement) {
                    cout << "Entrez les coordonnees de la tuile :" << endl;
                    cin >> x >> y;

                    if (checkPlacementOfTile(currentTile, x, y)) {
                        placeTile(currentTile, x, y);
                        display5Tiles();
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
            allTiles[i].display();
        }
        int tileToExchange;
        cout << "Quelle tuile voulez vous echanger ?" << endl;
        cin >> tileToExchange;
        Tile tile = takeTile(tileToExchange - 1);
        currentTile = tile;
        currentPlayer->setTileExchangeBonus(currentPlayer->getTileExchangeBonus() - 1);
    }
}

void Game::stoneAction() {
    bool validStone = false;

    while (!validStone) {
        int x, y;

        cout << "Entrez les coordonnees de la tuile :" << endl;
        cin >> x >> y;

        if (board[x][y].getPlayer()->getPlayerName() != currentPlayer->getPlayerName()) {
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
        int x, y;

        cout << "Entrez les coordonnees de la tuile :" << endl;
        cin >> x >> y;

        if (board[x][y].getPlayer()->getPlayerName() != currentPlayer->getPlayerName()) {
            char type = board[x][y].getType();
            Player *player = board[x][y].getPlayer();

            player->getTile(type).display();

            currentTile = player->getTile(type);
            currentPlayer->setRobberyBonus(currentPlayer->getRobberyBonus() - 1);
            validRobbery = true;
            deleteTile(player->getTile(type), x, y);
            cout << "La tuile a ete volee" << endl;
            askAction();
        } else {
            cout << "Merci de rentrer un placement valide" << endl;
        }
    }
}

int Game::getRound() {
    return currentRound;
}

void Game::nextPlayer() {
    if (currentPlayer == &players[players.size() - 1]) {
        currentPlayer = &players[0];
        currentRound++;
    } else {
        currentPlayer = &players[players.size() - 1];
    }
}

// a tester
void Game::getBonus() {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board.size(); ++j) {
            if (board[i][j].bonus == Case::EXCHANGE_TILE || board[i][j].bonus == Case::ROBBERY_TILE ||
                board[i][j].bonus == Case::STONE_TILE) {
                if (board[i + 1][j].getPlayer() == currentPlayer &&
                    board[i - 1][j].getPlayer() == currentPlayer &&
                    board[i][j + 1].getPlayer() == currentPlayer &&
                    board[i][j - 1].getPlayer() == currentPlayer &&
                    board[i + 1][j + 1].getPlayer() == currentPlayer &&
                    board[i - 1][j - 1].getPlayer() == currentPlayer &&
                    board[i + 1][j - 1].getPlayer() == currentPlayer &&
                    board[i - 1][j + 1].getPlayer() == currentPlayer) {
                    if (board[i][j].bonus == Case::EXCHANGE_TILE) {
                        currentPlayer->setTileExchangeBonus(currentPlayer->getTileExchangeBonus() + 1);
                        cout << "Le joueur " << currentPlayer->getPlayerName() << " a recu un bonus d'echange" << endl;
                        board[i][j].bonus = Case::NONE;
                    } else if (board[i][j].bonus == Case::ROBBERY_TILE) {
                        currentPlayer->setRobberyBonus(currentPlayer->getRobberyBonus() + 1);
                        cout << "Le joueur " << currentPlayer->getPlayerName() << " a recu un bonus de vol" << endl;
                        board[i][j].bonus = Case::NONE;
                    } else if (board[i][j].bonus == Case::STONE_TILE) {
                        currentPlayer->setStoneBonus(currentPlayer->getStoneBonus() + 1);
                        cout << "Le joueur " << currentPlayer->getPlayerName() << " a recu un bonus de pierre" << endl;
                        board[i][j].bonus = Case::NONE;
                    }
                }
            }
        }
    }

}

Tile Game::getCurrentTile() const {
    return currentTile;
}

void Game::setCurrentTile(Tile currentTile) {
    Game::currentTile = currentTile;
}

Tile Game::takeFirstTile() {
    return allTiles[0];
}

Tile Game::takeTile(int index) {
    return allTiles[index];
}

void Game::setTile(Tile tile, int index) {
    allTiles.insert(allTiles.begin() + index, tile);
}

void Game::setFirstTile(const Tile &tile) {
    allTiles.insert(allTiles.begin(), tile);
}

void Game::removeTile(const Tile &tile) {
    cout << allTiles.size() << endl;
    for (int i = 0; i < allTiles.size(); ++i) {
        if (allTiles[i].getId() == tile.getId()) {
            allTiles.erase(allTiles.begin() + i);
        }
    }
    cout << allTiles.size() << endl;
}


Player Game::checkWinner() {
    map<Player, int, PlayerCompare> scores;
    for (const auto &item: players) {
        int maxScore = 0;
        cout << item.getPlayerName() << endl;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board.size(); ++j) {
                bool continueLoop = true;
                int radius = 2;
                while (continueLoop) {

                    for (int k = 0; k < radius; ++k) {
                        for (int l = 0; l < radius; ++l) {
                            if (i + k < board.size() && j + l < board.size()) {
                                Player *player = board[i + k][j + l].getPlayer();
                                if (player == nullptr || player->getPlayerName() != item.getPlayerName()) {
                                    continueLoop = false;
                                }
                            }
                        }
                    }
                    if (continueLoop) {
                        radius += 1;
                        if (maxScore < radius)
                            maxScore = radius - 1;
                    }
                }
            }
        }
        scores[item] = maxScore;
    }
    for (const auto &item: scores) {
        cout << item.first.getPlayerName() << " a " << item.second << " points" << endl;
    }

    return scores.begin()->first;
}

void Game::deleteTile(Tile tile, int x, int y) {
    int startX = -1;
    int startY = -1;
    for (int i = 0; i < tile.getTile().size(); ++i) {
        for (int j = 0; j < tile.getTile()[i].size(); ++j) {
            if (tile.getTile()[i][j] == '1') {
                startX = i;
                startY = j;
                break;
            }
        }
        if (startX != -1) {
            break;
        }
    }
    for (int i = 0; i < tile.getTile().size(); ++i) {
        for (int j = 0; j < tile.getTile()[i].size(); ++j) {
            if (tile.getTile()[i][j] != '0') {
                board[x + i - startX][y + j - startY].setPlayer(nullptr);
                board[x + i - startX][y + j - startY].setType('.');
                board[x + i - startX][y + j - startY].setTouch(true);
            }
        }
    }
}

void Game::placeLastTile() {
    int x, y;
    for (int i = 0; i < players.size(); ++i) {
        while (players[i].getTileExchangeBonus() > 0) {
            cout << "Joueur " << i << " il vous reste " << players[i].getTileExchangeBonus() << " bonus d'échange"
                 << endl;
            cout << "Entrez les coordonnees de la tuile 1x1 dont vous disposez :";
            cin >> x >> y;
            if (checkPlacement(x, y)) {
                board[x][y].setPlayer(&players[i]);
                board[x][y].setType(players[i].getPlayerChar());
                board[x][y].setTouch(false);
                players[i].setTileExchangeBonus(players[i].getTileExchangeBonus() - 1);
            } else {
                cout << "Merci de rentrer un placement valide" << endl;
            }
        }

    }
}