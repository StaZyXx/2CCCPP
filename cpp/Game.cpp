#include <windows.h>
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

const int MAX_ROUND = 2;

const map<string, int> colors = {
        {"Rouge",     4},
        {"Bleu",      9},
        {"Vert",      10},
        {"Jaune",     14},
        {"Violet",    5},
        {"Blanc",     15},
        {"Rose",      13},
        {"Orange",    6},
        {"Turquoise", 11}
};

// startGame() is a function that starts the game
void Game::startGame() {
    initPlayers();
    createBoard();
    mixTiles();
    displayBoard();
    placePlayers();
    while (getRound() != MAX_ROUND) {
        askAction();
        getBonus();
        nextPlayer();
    }
    placeLastTile();
    checkWinner();
}

// initPlayers() is a function that initializes the players
void Game::initPlayers() {
    vector<string> colors = {"Rouge", "Bleu", "Vert", "Jaune", "Violet", "Blanc", "Rose", "Orange", "Turquoise"};
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
    currentPlayer = &players[0];
}

// createBoard() is a function that creates the board
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

// display5Tiles() is a function that displays the 5 tiles that the player can choose from
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

// displayBoard() is a function that displays the board
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
            Case currentCase = board[i][j];
            if (currentCase.getPlayer() != nullptr) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        (colors.at(currentCase.getPlayer()->getPlayerColor()) + (0 * 16)));
            }
            cout << board[i][j].getType() << "  ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        cout << endl;
    }
}

// placePlayers() is a function that places the players on the board
void Game::placePlayers() {
    for (int i = 0; i < players.size(); ++i) {
        int x, y;
        bool validPlacement = false;
        while (!validPlacement) {
            cout << "Joueur " << i + 1 << " placez votre case de depart" << endl;
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

// placeTile() is a function that places a tile on the board
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

// checkPlacementOfTile() is a function that checks if a tile can be placed on the board
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
                if (!isInBoard(x + i - startX, y + j - startY) || !isInBoard(x - startX + 1, y - startY + 1) ||
                    !checkPlacement(x + i - startX, y + j - startY) ||
                    board[x + i - startX][y + j - startY].getIsStone()) {
                    cout << "La tuile ne peut pas etre placee ici" << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

// isInBoard() is a function that checks if a location is in the board
bool Game::isInBoard(int x, int y) {
    return x >= 0 && x < board.size() && y >= 0 && y < board.size();
}

// checkPlacement() is a function that checks if a tile can be placed on the board
bool Game::checkPlacement(int x, int y) {
    //Check top-left corner
    if (x == 0 && y == 0) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) &&
               board[x][y + 1].canTouch(currentPlayer);
    }
    //Check top-right corner
    if (x == 0 && y == board.size() - 1) {
        return board[x][y].canTouch() && board[x + 1][y].canTouch(currentPlayer) &&
               board[x][y - 1].canTouch(currentPlayer);
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
               board[x][y + 1].canTouch(currentPlayer);
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

// mixTiles() is a function that mixes all the tiles get from the files
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

// askAction() is a function that asks the player what action he wants to do
void Game::askAction() {
    cout << "Joueur " << currentPlayer->getPlayerName() << " c'est a vous de jouer" << endl;
    cout << "1. Placer une tuile (P)" << endl;
    cout << "2. Echanger une tuile - " << currentPlayer->getTileExchangeBonus() << " restante (E)" << endl;
    cout << "3. Voler une tuile - " << currentPlayer->getRobberyBonus() << " restante (V)" << endl;
    cout << "4. Poser un pion - " << currentPlayer->getStoneBonus() << " restant (S)" << endl;
    cout << "5. Retirer une tuile en stone (1 coupon d'echange) - " << currentPlayer->getTileExchangeBonus()
         << " restant (D)" << endl;

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
            case 'd':
                if (currentPlayer->getTileExchangeBonus() > 0) {
                    removeStone();
                    validAction = true;
                } else {
                    cout << "Vous n'avez plus de bonus d'echange" << endl;
                }
            default:
                cout << "Merci de rentrer une action valide" << endl;
                break;
        }
    }
}

// placeAction() is a function that allows the player to place a tile
void Game::placeAction() {
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
                    int x, y;
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
            default:
                cout << "Merci de rentrer une action valide" << endl;
                break;
        }
    }
}

// exchangeAction() is a function that allows the player to exchange a tile
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
        validExchange = true;
        cout << "La tuile a ete echangee" << endl;
    }
}

// stoneAction() is a function that allows the player to place a stone on a tile
void Game::stoneAction() {
    bool validStone = false;

    while (!validStone) {
        int x, y;
        cout << "Entrez les coordonnees de la tuile :" << endl;
        cin >> x >> y;

        if (isInBoard(x, y) && board[x][y].getType() == '.') {
            board[x][y].setType('X');
            board[x][y].setStone(true);
            currentPlayer->setStoneBonus(currentPlayer->getStoneBonus() - 1);
            validStone = true;
            displayBoard();
        } else {
            cout << "Merci de rentrer un placement valide" << endl;
        }
    }
}

// removeStone() is a function that allows the player to remove a stone from the board
void Game::removeStone() {
    bool validStone = false;

    while (!validStone) {
        int x, y;
        cout << "Entrez les coordonnees de la tuile :" << endl;
        cin >> x >> y;

        if (isInBoard(x, y) && board[x][y].getIsStone()) {
            board[x][y].setStone(false);
            currentPlayer->setTileExchangeBonus(currentPlayer->getTileExchangeBonus() - 1);
            validStone = true;
        } else {
            cout << "Merci de rentrer un placement valide" << endl;
        }
    }
}

// robberyAction() is a function that allows the player to steal a tile from another player
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

// getRound() is a function that returns the current round
int Game::getRound() {
    return currentRound;
}

// nextPlayer() is a function that changes the current player
void Game::nextPlayer() {
    if (currentPlayer == &players[players.size() - 1]) {
        currentPlayer = &players[0];
        currentRound++;
    } else {
        currentPlayer = &players[players.size() - 1];
    }
}

// getBonus() is a function that checks if a player has a bonus
void Game::getBonus() {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board.size(); ++j) {
            if (board[i][j].bonus == Case::EXCHANGE_TILE || board[i][j].bonus == Case::ROBBERY_TILE ||
                board[i][j].bonus == Case::STONE_TILE) {
                if (board[i + 1][j].getPlayer() == currentPlayer &&
                    board[i - 1][j].getPlayer() == currentPlayer &&
                    board[i][j + 1].getPlayer() == currentPlayer &&
                    board[i][j - 1].getPlayer() == currentPlayer) {
                    board[i][j].setTouch(false);
                    board[i][j].setType(currentPlayer->getCurrentChar());
                    board[i][j].setPlayer(currentPlayer);
                    if (board[i][j].bonus == Case::EXCHANGE_TILE) {
                        currentPlayer->setTileExchangeBonus(currentPlayer->getTileExchangeBonus() + 1);
                        cout << "Le joueur " << currentPlayer->getPlayerName() << " a recu un bonus d'echange" << endl;
                        board[i][j].bonus = Case::NONE;
                    } else if (board[i][j].bonus == Case::ROBBERY_TILE) {
                        currentPlayer->setRobberyBonus(currentPlayer->getRobberyBonus() + 1);
                        cout << "Le joueur " << currentPlayer->getPlayerName() << " a recu un bonus de vol" << endl;
                        board[i][j].bonus = Case::NONE;
                        robberyAction();
                    } else if (board[i][j].bonus == Case::STONE_TILE) {
                        currentPlayer->setStoneBonus(currentPlayer->getStoneBonus() + 1);
                        cout << "Le joueur " << currentPlayer->getPlayerName() << " a recu un bonus de pierre" << endl;
                        board[i][j].bonus = Case::NONE;
                        stoneAction();
                    }
                }
            }
        }
    }

}

// takeFirstTile() is a function for taking the first tile from the vector of all tiles
Tile Game::takeFirstTile() {
    return allTiles[0];
}

// takeTile() is a function for taking a tile from the vector of all tiles
Tile Game::takeTile(int index) {
    return allTiles[index];
}

// removeTile() is a function for removing a tile from the vector of all tiles
void Game::removeTile(const Tile &tile) {
    for (int i = 0; i < allTiles.size(); ++i) {
        if (allTiles[i].getId() == tile.getId()) {
            allTiles.erase(allTiles.begin() + i);
        }
    }
}

// checkWinner() is a function that checks the winner of the game
// Check each case and increment the score of the player if he has the most tiles around him
Player Game::checkWinner() {
    map<Player, int, PlayerCompare> scores;
    for (const auto &item: players) {
        int maxScore = 0;
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

// deleteTile() is a function for deleting a tile from the board (used for the robbery bonus)
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

// placeLastTile() is a function that allows the player to place the last tile of the game (the 1x1 tile)
// It is called when all players have placed their tiles and have no more tile exchange bonus
void Game::placeLastTile() {
    bool validPlacement = false;
    while (!validPlacement) {
        bool hasPlaced = false;
        for (int i = 0; i < players.size(); ++i) {
            while (!hasPlaced && players[i].getTileExchangeBonus() > 0) {
                int exchangeBonus = players[i].getTileExchangeBonus();
                if (exchangeBonus == 0) {
                    continue;
                }
                displayBoard();
                int x, y;
                cout << "Joueur " << i << " il vous reste " << exchangeBonus << " bonus d'echange"
                     << endl;
                cout << "Entrez les coordonnees de la tuile 1x1 dont vous disposez :";
                cin >> x >> y;
                if (checkPlacement(x, y)) {
                    hasPlaced = true;
                    board[x][y].setPlayer(&players[i]);
                    board[x][y].setType(players[i].getPlayerChar());
                    board[x][y].setTouch(false);
                    players[i].setTileExchangeBonus(players[i].getTileExchangeBonus() - 1);
                } else {
                    cout << "Merci de rentrer un placement valide" << endl;
                }
            }
        }
        if (!hasPlaced) {
            validPlacement = true;
        }
    }

}