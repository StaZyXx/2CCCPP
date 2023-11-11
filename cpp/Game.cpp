#include "../headers/Game.h"
#include "../headers/Player.h"
#include <iostream>
#include <vector>

using namespace std;

Game::Game() = default;

void Game::startGame() {
    vector<Player> players;
    vector<string> colors = {"Rouge", "Bleu", "Vert", "Jaune", "Violet", "Blanc", "Rose", "Orange", "Marron"};
    cout << "Entrez le nombre de joueurs :";
    cin >> amountPlayer;
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
    for (int i = 0; i < players.size(); ++i) {
        cout << "Player" << i + 1 << " : " << players[i].getPlayerName() << "Couleur : " << players[i].getPlayerColor() << endl;
    }
}