# COMP2113_Group-34 (Splitted group from group 13. Similar game)

## Team Members:
- Li Yixuan, UID: 3036267111
- Yang Jingcheng, UID: 3036219114

## Description of the Project:
### Title:
- Demon Roulette

### In Menu:
We have two modes of playing:
1. Single-player mode. (Human-machine)
2. Double-player mode.
3. This is a game which two players duel in a life or death gamble.

### Description of the Rules:
- Both players start with 3 HP.
- Each player will get two random items when:
1.The game starts.
2.Each player takes at least one action.
- There is a gun with 6 bullets: 3 live and 3 empty.
- The gun will reload automatically after all ammo has been used up.

### Within a Round (in sequence):

- Before choosing to shoot, players can use an unlimited number of items (Item functionalities will be listed below).
- The player in action can choose to use the gun to shoot themself or the opponent.
- If a bullet is live ammunition, the HP of the player who got shot decreases by 1.
- Shooting oneself with an empty bullet or shooting the opponent with live ammo will grant the player another action round.
- The opponent gets to take action next round otherwise.
- The game is over when either side has their health reduced to 0.

### Usage of Items:
- **Handsaw**: This item doubles the damage for the round, meaning that if the bullet is live ammunition, the HP of the player shot by the bullet decreases by 2 instead of 1.
- **Cigarette**: This item helps the person regain 1 HP immediately.
- **Handcuffs**: This item will ban your opponent for next round, so no matter you miss or hit, you will have two consecutive rounds.
- **shield**: This item will generate a shield valid in two-round, and it can block any damage once for you.

## Compilation and Execution Instructions:
1. Download all necessary files to your computer.
2. Open the terminal and navigate to the working directory containing the files.
3. Run the command: `make`.
4. Then run the command: `./game` to play the game.

## Code Requirements

### Generation of Random Events:
- Items are assigned randomly.
- The method for determining who takes action first is random.
- Which bullet shot is random.
- Single_player mode's AI player's action is completely randomized.

### Data Structures for Storing Data:
- The stats of each player are stored after each action and will be displayed at the start of every round, including health and items.

### Dynamic Memory Management:
- The use of `vector` for storing items, clearing the vector list after deletion of items. The vector list will expand once full.

### File Input/Output (e.g., for loading/saving data):
- The game will handle data output and input for saving the progress of the running game, and reloading the game with a given saved file that contains data from the last game played.

### Program Code in Multiple Files:
- We separated our code into several files: `main.cpp` as the game menu, `double_player.cpp` for the code running the game, and functions used in another file 'Declared_functions.cpp'.

### Features:
- The game can be played under both Single_player and Double_player mode.
- Automatic saving is present, you can load into your previously saved game if wanted.
- A game requires both luck and skills, making it entertaining.

## Shout out to the game which inspired our creation, Buckshot Roulette.
##Video link
- https://youtu.be/RjL1kh1Vnws

