#include "Gamemode.h"
#include "Declared_functions.h"
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>  
using namespace std;

char NPC_2choice (char a, char b) {
    
    srand(time(0));
    
    int choose;
    choose = rand() % 2;

    if (choose == 0) {
        return a;
    }
    else {
        return b;
    }
}

bool P1_round_single(Player &player1, Player &player2) {

    player1.player_action = true;
    handsawUsed = false; //reset handsaw usage at the beginning of every round
    P1secondround = false; //reset handcuffs usage for p1

    
    promptForInput(player1.name + ", do you want to use your item? (Y/N, Q to quit): ", choice, "YNQ");

    // Handling quit
    if (choice == 'Q' || choice == 'q') {
        writePlayersStatsToFile(player1, player2, "saved_game");
        quitGame();
    }

    if (choice == 'Y' || choice == 'y') {
        if (player1.item.empty()) {
            cout << "You have No items left!" << endl;
        }
        else {
            while (!useItem(player1,player1.item)) {
                if (player1.item.empty()) {
                    cout << "You have No items left!" << endl;
                    break;
                }
                printStatus(player1, player2);
            }
        }
    }


    // Player 1's turn to shoot
    promptForInput(player1.name + ", would you like to shoot (other player or yourself)? (O/S, Q to quit): ", choice, "OSQ");

    // Handling quit
    if (choice == 'Q' || choice == 'q') {
        writePlayersStatsToFile(player1, player2, "saved_game");
        quitGame();
    }

    if (choice == 'O' || choice == 'o') {
        if (shoot(player2)) {
            cout << player2.name << " was hit!" << endl;
            P1_turn = true;
        } else {
            cout << player2.name << " was missed!" << endl;
            P1_turn = false;
        }
    } else {
        if (shoot(player1)) {
            cout << player1.name << " shot themselves and was hit!" << endl;
            P1_turn = false;
        } else {
            cout << player1.name << " shot themselves and missed!" << endl;
            P1_turn = true;
        }
    }
   
    if (P1secondround) {
        P1_turn = true;
        cout << player1.name << " used handcuffs to " << player2.name << ", and he will have one more round!" << endl;
    }
    
 //shield lifetime checking   
    if (player1.shielded) {
        p1shieldlife++;
    } else {
        p1shieldlife = 0; //reset lifetime if shield is broken
    }
    if (p1shieldlife == 2) {
        player1.shielded = false;
        cout << player1.name << "\'s shield disappear after 2 round!" <<endl;
        p1shieldlife = 0;
    }
    if (player2.shielded) {
        p2shieldlife++;
    } else {
        p2shieldlife = 0; //reset lifetime if shield is broken
    }
    if (p2shieldlife == 2) {
        player2.shielded = false;
        cout << player2.name << "\'s shield disappear after 2 round!" <<endl;
        p2shieldlife = 0;
    }

    // Check if Player 2 is out of health immediately after shooting
    if (player2.health <= 0) {
        cout << player2.name << " is dead " << player1.name << " wins!" << endl;
        return true;
    }
    else if (player1.health <= 0) {
        cout << player1.name << " is dead " << player2.name << " wins!" << endl;
        return true;
    }
    return false;
}

bool P2_round_single(Player &player1, Player &player2) {
    
    player2.player_action = true;
    handsawUsed = false; //reset handsaw usage at the beginning of every round
    P2secondround = false; //reset handcuffs usage for p2
    
    choice = NPC_2choice('Y','N');

    // Handling quit
    if (choice == 'Q' || choice == 'q') {
        writePlayersStatsToFile(player1, player2, "saved_game");
        quitGame();
    }

    if (choice == 'Y' || choice == 'y') {
        if (player2.item.empty()) {
            cout << "You have No items left!" << endl;
        }
        else {
            while (!AIuseItem(player2,player2.item)) {
                if (player2.item.empty()) {
                    cout << "You have No items left!" << endl;
                    break;
                }
                printStatus(player1, player2);
            }
        }
    }


   choice = NPC_2choice('O','S');

    // Handling quit
    if (choice == 'Q' || choice == 'q') {
        writePlayersStatsToFile(player1, player2, "saved_game");
        quitGame();
    }

    if (choice == 'O' || choice == 'o') {
        if (shoot(player1)) {
            cout << player1.name << " was hit!" << endl;
            P1_turn = false;
        } else {
            cout << player1.name << " was missed!" << endl;
            P1_turn = true;
        }
    } else {
        if (shoot(player2)) {
            cout << player2.name << " shot themselves and was hit!" << endl;
            P1_turn = true;
        } else {
            cout << player2.name << " shot themselves and missed!" << endl;
            P1_turn = false;
        }
    }

    if (P2secondround) {
        P1_turn = false;
        cout << player2.name << " used handcuffs to " << player1.name << ", and he will have one more round!" << endl;
    }
    
 //shield lifetime checking   
    if (player1.shielded) {
        p1shieldlife++;
    } else {
        p1shieldlife = 0; //reset lifetime if shield is broken
    }
    if (p1shieldlife == 2) {
        player1.shielded = false;
        cout << player1.name << "\'s shield disappear after 2 round!" <<endl;
        p1shieldlife = 0;
    }
    if (player2.shielded) {
        p2shieldlife++;
    } else {
        p2shieldlife = 0; //reset lifetime if shield is broken
    }
    if (p2shieldlife == 2) {
        player2.shielded = false;
        cout << player2.name << "\'s shield disappear after 2 round!" <<endl;
        p2shieldlife = 0;
    }
    
    // Check if Player 2 is out of health immediately after shooting
    if (player2.health <= 0) {
        cout << player2.name << " is dead " << player1.name << " wins!" << endl;
        return true;
    }
    else if (player1.health <= 0) {
        cout << player1.name << " is dead " << player2.name << " wins!" << endl;
        return true;
    }
    return false;
}

void Single_Player() {
    
    Player player1, player2;
    player1.name = "Player 1";
    player1.health = INITIAL_HEALTH;
    player1.player_action = true;
    player1.shielded = false;

    player2.name = "Ai Player";
    player2.health = INITIAL_HEALTH;
    player2.player_action = true;
    player2.shielded = false;

    p1shieldlife = 0;
    p2shieldlife = 0;

    int allUsedUp = 0;
    bool gameOver = false;
    // Initialize the shotgun
    reloadShotgun();
    
    promptForInput("Would you like to load in your saved game? Y for Yes, N for No", choice, "YN");
    if (choice == 'Y' || choice == 'y') {
        if (loadPlayersStatsFromFile(player1, player2, "saved_game")){
            cout << "game succesfully loaded" << endl;
        }
    }
    
    if (random_initiatives()){
        P1_turn = true;
    }

    while (!gameOver) {
       
        // Both players start with a new random item at the beginning of each round
        if (player1.player_action == true && player2.player_action == true) {
            player1.item.push_back(getRandomItem());
            player1.item.push_back(getRandomItem());
            player2.item.push_back(getRandomItem());
            player2.item.push_back(getRandomItem());
            player1.player_action = false;
            player2.player_action = false;
        }
        
        // Display player status before each round
        printStatus(player1, player2);

        //Determine which player take action this round
        if (P1_turn == true) {
            if (P1_round_single(player1,player2)) {
                gameOver = true;
            }
        }
        else{
            if (P2_round_single(player1,player2)) {
                gameOver = true;
            }
        }
        
        // Check if the shotgun needs to be reloaded (i.e., all ammo has been used)
        for (int i = 0; i < TOTAL_AMMO; i++) {
            if (shotgun[i] == NON) {
                allUsedUp++; // If there is any live ammo, not all used up
                // allUsedUP is to count how many none, i.e. how many ammos have been shot
            }
        }
        if (allUsedUp == 6) {
            cout << "All ammo has been used up. Reloading the shotgun!" << endl;
            reloadShotgun();
        }
        allUsedUp = 0;     
    }
}
