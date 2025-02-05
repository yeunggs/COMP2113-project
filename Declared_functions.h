#ifndef DECLARED_FUNCTIONS_H
#define DECLARED_FUNCTIONS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

enum AmmoState { EMPTY, LIVE, NON };
enum ItemType { CIGARETTE, HANDSAW, HANDCUFFS, SHIELD, NONE }; // Define item types

struct Player {
    string name;
    int health;
    vector<ItemType> item; //vector of item list
    bool player_action;
    bool shielded;
};

const int TOTAL_AMMO = 6; // 3 live, 3 empty
const int INITIAL_HEALTH = 3; // Health for each player
extern bool handsawUsed;
extern bool P1secondround;
extern bool P2secondround;
extern AmmoState shotgun[TOTAL_AMMO];
extern int p1shieldlife;
extern int p2shieldlife;
extern bool P1_turn; // To track the turn of player 1

// Function prototypes
void item_cigarette(Player &player);
void item_handsaw(Player &player);
void item_handcuffs();
void item_shield(Player &player);
bool random_initiatives();
void initializeShotgun();
void printStatus(const Player &player1, const Player &player2);
bool shoot(Player &target);
void reloadShotgun();
bool useItem(Player &player,vector<ItemType> &item);
bool AIuseItem(Player &player, vector<ItemType> &item);
ItemType getRandomItem();
void quitGame();
void promptForInput(const string &prompt, char &input, const string &validChoices);
void writePlayersStatsToFile(const Player &player1, const Player &player2, const string &filename);
bool loadPlayersStatsFromFile(Player &player1, Player &player2, const string &filename);

#endif // DECLARED_FUNCTIONS_H
