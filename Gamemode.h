#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "Declared_functions.h" // Include any necessary headers

extern bool P1_turn;          // To track the turn of player 1
extern char choice;           // For user inputs and NPC choices
extern bool handsawUsed;
extern bool P1secondround;
extern bool P2secondround;
extern int p1shieldlife;
extern int p2shieldlife;

// Function declarations for single-player mode
void Single_Player(); // Declare the function to handle single-player mode

// Function declarations for double-player mode
void Double_Player(); // Declare the function to handle double-player mode

#endif // GAMEMODE_H
