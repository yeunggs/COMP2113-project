#include <iostream>
#include "Gamemode.h"

using namespace std;

bool P1_turn = false;
char choice;

//menu page, handling which game mode the grogramme is going to run.
int main(){
  int player_num;
  char playagain;
  while (true){
    cout << "Choose the number of Player" << endl << "1 for single player, 2 for double player" << endl;
    cin >> player_num;
    while (true){
      if (player_num == 1){
        Single_Player();
        break;
      }
      if(player_num == 2){
        Double_Player();
        break;
      }
      cout << "Invalid input, please enter 1 or 2 for single player or double player mode." << endl;
      cin >> player_num;
    }
    //handling if player want to play again
    cout << "Do you want to play again? Y for Yes and any single character for No" << endl;
    cin >> playagain;
    if (playagain == 'Y'){
      cout << "Wish you luck!" << endl;
      continue;
    }
    else{
      break;
    }
  }
    cout << "Thank you for playing" << endl;
  return 0;
}
  
