#include "Declared_functions.h"
#include <algorithm>
#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//variable definitions & declarations
AmmoState shotgun[TOTAL_AMMO]; 
bool handsawUsed = false;
bool P1secondround;
bool P2secondround;
int p1shieldlife;
int p2shieldlife;

//function for performing what item cigarette does.
void item_cigarette(Player &player) {
  if (player.health < INITIAL_HEALTH) {
    player.health++; // Regain 1 health
    cout << player.name << " uses a Cigarette and regains 1 health!" << endl;
  } 
  else {
    cout << player.name << " already has full health and cannot regain more!" << endl;
  }
}

//function for performing what item handsaw does.
void item_handsaw(Player &player) {
  handsawUsed = true;
  cout << player.name << "'s next shoot will have doubled damage! Try not to miss!" << endl;
}

//function for performing what item handcuffs does.
void item_handcuffs() {
  if (P1_turn) {
    P1secondround = true;
  } else {
    P2secondround = true;
  }
  cout << "Handcuffs have been successfully used to your opponent!" << endl;
}

//function for performing what item shield does.
void item_shield(Player &player) {
  player.shielded = true;
  cout << player.name << " used shield and will be immune to next damage!" << endl;
  cout << "The effect of shield will be expired if no damage is taken within 2 round!" << endl;
}

//To determine which player take action first
bool random_initiatives() {
    cout << endl;
    cout << "player 1 is the one who sits on the left" << endl;
    cout << endl;
    cout << "We now will have a lucky draw to see who take action first, good luck!" << endl;
    cout << endl;
    cout << "Now lets see who get to play first! The one got a larger number take action first! " << endl;
    cout << endl;
  
    srand(time(0));

    int Dice1;
    int Dice2;
    while (true) {
        
        Dice1 = rand() % 6 + 1;
        Dice2 = rand() % 6 + 1;
        
        cout << "player one got:"<< Dice1 << " " << "player two got:" << Dice2 << endl;
        cout << endl;
        if (Dice1 == Dice2) { 
            cout << "Ahhhh, its a draw, lets do it again" << endl;
            cout << endl;
        }
        else{
            break;
        }
    }
      
    if (Dice1 > Dice2) {
      cout << "player 1 has the initiative!" << endl;
      cout << endl;
      return true;
    }
    else{
      cout << "player 2 has the initiative!" << endl;
      cout << endl;
      return false;
    }
}

//To print status of two player at the start of each round
void printStatus(const Player &player1, const Player &player2) {
    cout << endl;
    cout << player1.name << " Health: " << player1.health << " | Item: ";

    if (player1.item.empty()) {
        cout << "None" << endl;
    } else {
        for (size_t i = 0; i < player1.item.size(); i++) {
            switch (player1.item[i]) {
              case CIGARETTE:
                cout << "Cigarette ";
                break;
              case HANDSAW:
                cout << "Handsaw ";
                break;
              case HANDCUFFS:
                cout << "Handcuffs ";
                break;
              case SHIELD:
                cout << "Shield ";
                break;
              case NONE:
                cout << "no item left";
                break;
            }
        }
        cout << endl;
    }

    cout << player2.name << " Health: " << player2.health << " | Item: ";

    if (player2.item.empty()) {
        cout << "None" << endl;
    } else {
        for (size_t i = 0; i < player2.item.size(); i++) {
            switch (player2.item[i]) {
              case CIGARETTE:
                cout << "Cigarette ";
                break;
              case HANDSAW:
                cout << "Handsaw ";
                break;
              case HANDCUFFS:
                cout << "Handcuffs ";
                break;
              case SHIELD:
                cout << "Shield ";
                break;
              case NONE:
                cout << "no item left";
                break;
            }
        }
        cout << endl;
        cout << endl;
    }
}

//Handling shooting of shotgun. i.e. randomly choosing if the ammo is Live or empty,
//record down the ammo condition in the array.
bool shoot(Player &target) {
    // Randomly choose one of the ammo slots
    srand(time(0));
    int ammoIndex = rand() % TOTAL_AMMO;
    while (true) {
        if (shotgun[ammoIndex] == NON) {
            ammoIndex = rand() % TOTAL_AMMO;
        }
        else{
            break;
        }
    }
    int damage = 1;

    if (handsawUsed) {
        damage = 2;// double the damage by using handsaw item
    }
    
    // Check if the chosen ammo is live 
    if (shotgun[ammoIndex] == LIVE) {
      if (target.shielded) {
        cout << "damage is blocked by the shield!" << endl;
        cout << target.name << "'s shield is now broken" << endl;
        target.shielded = false;
      } else {
        // Hit the target
        target.health -= damage; // Decrease target's health by 1 or 2
        shotgun[ammoIndex] = NON; // Use this ammo
        return true; // Indicate a hit        
      }
    } 
    else {
        shotgun[ammoIndex] = NON; // Missed shot, use this ammo
        return false; // Indicate a miss
    }
    if (damage == 2) {
        damage = 1; // reset the demage to original
        handsawUsed = false; //reset handsawUsed varible
    }
return true;
}

//Resetting the shotgun condition.
void reloadShotgun() {
    for (int i = 0; i < TOTAL_AMMO; ++i) {
        shotgun[i] = (i < 3) ? LIVE : EMPTY; // First 3 slots are live, next 3 are empty
    }
}

//Handling the vector list for items and executing the items
//until it returns true, the system will ask for another input.
bool useItem(Player &player, vector<ItemType> &item) {
    char itemChoice; 
    cout << player.name << ", which item do you want to use? (C for Cigarette, H for Handsaw, U for HandCuffs, S for Shield, Q for stop using items): ";
    cin >> itemChoice;

    //handling cigarette usage
    if (itemChoice == 'C' || itemChoice == 'c') {
        int itemcount = count(item.begin(), item.end(), 0); // check existance of the item, 0 represent c
        if (itemcount > 0){
            auto finditem = find(item.begin(), item.end(), 0);
            int itemposition = distance(item.begin(), finditem);

            item.erase(item.begin() + itemposition); //clearing out the space for used item
            item_cigarette(player);//call item function
            return false;
        }
        else {
            cout << "You don't have this item in your bag!" << endl;
          return false;
        }
    } 
    else if (itemChoice == 'H' || itemChoice == 'h') {
        int itemcount = count(item.begin(), item.end(), 1); // check existance of the item, 1 represent h
        if (itemcount > 0){
            auto finditem = find(item.begin(), item.end(), 1);
            int itemposition = distance(item.begin(), finditem);

            item.erase(item.begin() + itemposition);
            item_handsaw(player); // call item function, not sure the pass by reference is correct********** 
            return false;
           
        } 
        else {
            cout << "You don't have this item in your bag!" << endl;
          return false;
        } 
    }
    else if (itemChoice == 'U' || itemChoice == 'u' ){
      int itemcount = count(item.begin(), item.end(), 2); // check existance of the item, 2 represent u
        if (itemcount > 0){
            auto finditem = find(item.begin(), item.end(), 2);
            int itemposition = distance(item.begin(), finditem);

            item.erase(item.begin() + itemposition);
            item_handcuffs();
            return false;
        } 
        else {
            cout << "You don't have this item in your bag!" << endl;
          return false;
        } 
    }
    else if (itemChoice == 'S' || itemChoice == 's' ){
      int itemcount = count(item.begin(), item.end(), 3); // check existance of the item, 3 represent s
      if (itemcount > 0){
          auto finditem = find(item.begin(), item.end(), 3);
          int itemposition = distance(item.begin(), finditem);

          item.erase(item.begin() + itemposition);
          item_shield(player);
          return false;
      } 
      else {
          cout << "You don't have this item in your bag!" << endl;
          return false;
      } 
    }
    else if (itemChoice == 'Q' || itemChoice == 'q') {
      return true;
    }
    else {
        cout << "Invalid choice! You can only choose C for Cigarette or H for Handsaw, U for HandCuffs, S for Shield, Q for stop using items" << endl;
        return false;
    }
}

//Similar to UseItem, but the choice of which Item used is randomly generated for the AI player.
bool AIuseItem(Player &player, vector<ItemType> &item) {
    cout << "he chose to use Item" << endl;
    int itemChoice;
    itemChoice = rand() % 5;

    if (itemChoice == 0) {
        cout << "he chose C" << endl;
        int itemcount = count(item.begin(), item.end(), 0);
        if (itemcount > 0){
            auto finditem = find(item.begin(), item.end(), 0);
            int itemposition = distance(item.begin(), finditem);

            item.erase(item.begin() + itemposition);
            item_cigarette(player);//call item function
            return false;
        }
        else {
            cout << "You don't have this item in your bag!" << endl;
          return false;
        }
    } 
    else if (itemChoice == 1) {
        cout << "he chose H" << endl;
        int itemcount = count(item.begin(), item.end(), 1);
        if (itemcount > 0){
            auto finditem = find(item.begin(), item.end(), 1);
            int itemposition = distance(item.begin(), finditem);

            item.erase(item.begin() + itemposition);
            item_handsaw(player); 
            return false;
           
        } 
        else {
            cout << "You don't have this item in your bag!" << endl;
          return false;
        } 
    }
    else if (itemChoice == 2) {
        cout << "he chose Q" << endl;
        return true;
    }
    else if (itemChoice == 3){
      cout << "he chose U" << endl;
      int itemcount = count(item.begin(), item.end(), 2);
        if (itemcount > 0){
            auto finditem = find(item.begin(), item.end(), 2);
            int itemposition = distance(item.begin(), finditem);

            item.erase(item.begin() + itemposition);
            item_handcuffs();
            return false;
        } 
        else {
            cout << "You don't have this item in your bag!" << endl;
          return false;
        } 
    }
    else{
      cout << "he chose S" << endl;
      int itemcount = count(item.begin(), item.end(), 3);
      if (itemcount > 0){
          auto finditem = find(item.begin(), item.end(), 3);
          int itemposition = distance(item.begin(), finditem);

          item.erase(item.begin() + itemposition);
          item_shield(player);
          return false;
      } 
      else {
          cout << "You don't have this item in your bag!" << endl;
          return false;
      } 
    }
}

void quitGame() {
    cout << "Exiting the game. Thanks for playing!" << endl;
    exit(0); // Exit the program
}

// Randomly return one item out of four
ItemType getRandomItem() {
    return static_cast<ItemType>(rand() % 4); // Generates 0 (CIGARETTE) or 1 (HANDSAW) or 2 (HANDCUFFS) or 3 (SHIELD)
}

//Ask for user to input, we handle the inputted value in Double_player/Single_player.
void promptForInput(const string &prompt, char &input, const string &validChoices) {
    while (true) {
        cout << prompt;
        cout << endl;
        cin >> input;

        // Convert to uppercase for easier comparison
        input = toupper(input);

        // Check if input is valid
        if (validChoices.find(input) != string::npos) {
            break; // Valid input; exit loop
        } 
        else {
            cout << "Invalid input! Please enter one of the following: " << validChoices << endl;
        }
    }
}

//Save the stat from the current game
void writePlayersStatsToFile(const Player &player1, const Player &player2, const string &filename) {
    fstream fout; // Using fstream to handle file output
    fout.open(filename, ios::out); // Open for writing

    if (!fout) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Write Player 1 stats
    fout << player1.name << " Stats:" << endl;
    fout << "Health: " << player1.health << endl;
    fout << "Items: ";
    
    for (const auto &item : player1.item) {
        if (item == CIGARETTE) {
            fout << "Cigarette ";
        } 
        else if (item == HANDSAW) {
            fout << "Handsaw ";
        }
    }
    fout << endl; // End the line after items are listed

    // Write Player 2 stats
    fout << player2.name << " Stats:" << endl;
    fout << "Health: " << player2.health << endl;
    fout << "Items: ";
    
    for (const auto &item : player2.item) {
        if (item == CIGARETTE) {
            fout << "Cigarette ";
        } 
        else if (item == HANDSAW) {
            fout << "Handsaw ";
        }
    }
    fout << endl; 

    // Write Shotgun state
    fout << "Shotgun State:" << endl;
    fout << "LIVE: " << count(shotgun, shotgun + TOTAL_AMMO, LIVE) << endl;
    fout << "EMPTY: " << count(shotgun, shotgun + TOTAL_AMMO, EMPTY) << endl;
    fout << "NON: " << count(shotgun, shotgun + TOTAL_AMMO, NON) << endl;


    fout.close(); // Close file after writing

    cout << "Player stats have been written to " << filename << endl;
}

//load player stat from last game
bool loadPlayersStatsFromFile(Player &player1, Player &player2, const string &filename) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error opening file for reading: " << filename << endl;
        return false; // Return false if file can't be opened
    }

    string line;
    // Read and parse Player 1 stats
    if (getline(inFile, line) && line.find("Player: ") != string::npos) {
        player1.name = line.substr(8); // Extract name from the line
    }
    if (getline(inFile, line) && line.find("Health: ") != string::npos) {
        player1.health = stoi(line.substr(8)); // Extract health and convert to int
    }
    if (getline(inFile, line) && line.find("Items: ") != string::npos) {
        player1.item.clear(); // Clear any existing items
        istringstream iss(line.substr(7)); // Start reading from items
        string item;
        while (iss >> item) {
            if (item == "Cigarette") {
                player1.item.push_back(CIGARETTE);
            } 
            else if (item == "Handsaw") {
                player1.item.push_back(HANDSAW);
            } 
        }
    }

    // Read and parse Player 2 stats
    if (getline(inFile, line) && line.find("Player: ") != string::npos) {
        player2.name = line.substr(8); // Extract name from the line
    }
    if (getline(inFile, line) && line.find("Health: ") != string::npos) {
        player2.health = stoi(line.substr(8)); // Extract health and convert to int
    }
    if (getline(inFile, line) && line.find("Items: ") != string::npos) {
        player2.item.clear(); // Clear any existing items
        istringstream iss(line.substr(7)); // Start reading from items
        string item;
        while (iss >> item) {
            if (item == "Cigarette") {
                player2.item.push_back(CIGARETTE);
            } 
            else if (item == "Handsaw") {
                player2.item.push_back(HANDSAW);
            } 
        }
    }

    if (getline(inFile, line) && line.find("Shotgun State:") != string::npos) {
        string shotgunLine;
        int liveCount;
        int emptyCount;
        int nonCount;
        while (getline(inFile, shotgunLine) && !shotgunLine.empty()) {
            if (shotgunLine.find("LIVE: ") != string::npos) {
                liveCount = stoi(shotgunLine.substr(6));
                for (int i = 0; i < liveCount; ++i) {
                    shotgun[i] = LIVE; // Assign LIVE ammo
                }
            } 
            else if (shotgunLine.find("EMPTY: ") != string::npos) {
                emptyCount = stoi(shotgunLine.substr(7));
                for (int i = 0; i < emptyCount; ++i) {
                    shotgun[liveCount + i] = EMPTY; // Assign EMPTY ammo starting after LIVE
                }
            } 
            else if (shotgunLine.find("NON: ") != string::npos) {
                nonCount = stoi(shotgunLine.substr(5));
                for (int i = 0; i < nonCount; ++i) {
                    shotgun[liveCount + emptyCount + i] = NON; // Assign NON ammo
                }
            }
        }
    }
    inFile.close(); // Close file after reading
    return true; // Return true indicating success
}


