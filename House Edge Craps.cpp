/* 
dice_program.cpp 
Alex Coulson
CS250 Fall 2025 Mitch Priestley
Week 8 Dice Program

Purpose: Run many trails of a casino game to prove (or disprove) that the casino
has an unfair advantage or house edge.

Specification: Get a random seed. Welcome users to the program. Run 10,000
trails of the casino game. In each game randomly generate a roll of two dice.
If the dice value == 2,3,12 then increase the casino earnings by the bet. If
the dice value == 7 or 11 then decrease the casino earnings by the bet amount.
Else go to a point game. Roll dice again. If the dice value == 7 increases
casino earnings by the bet amount. If the dice value == point then decrease
casino earnings by the bet amount. Else recall the point game function. Once
the casino earns or loses money, the next trail is run. After all trials are
run, report finds of casino earnings. Wrap up by displaying a sign off
message, clearing all variables, and ending normally.
*/
#include <iostream>
#include <ctime>
using namespace std;

// Function Prototypes
int roll();
void first_game(int&);
void point_game(int&, int);

// Declare Constants
const int TRIALS = 10'000;     // Number of trails that are ran
const int BET = 1;            // Amount bet by player and casino per trail


int main() {
    int casino_winnings = 0;  // Amount the casino has won or lost in the trails
    // Make rng 
    srand(time(0));
    // Welcome user to program
    cout << "Welcome to the Dice Program!\nNow running trials...\n";
    // Run trials
    for (int i = 0; i < TRIALS; ++i)
        first_game(casino_winnings);
    // Report findings
    cout << "After " << TRIALS << " trials the casinos returns are $" 
         << casino_winnings << endl;
    // sign off
    cout << "Goodbye, the program is now over.\n";
    // Clear data
    casino_winnings = 0;
    // End normally
    return 0;
}


// Purpose: Roll two randomly dice and get their value 
// Arguments: None
// Return: Value of dice roll 
int roll() {
    int roll_value = 0;   // Value of both of the dice  2-12
    int die_a = 0;        // Roll Value of the first die 1-6
    int die_b = 0;        // Roll Value of the second die 1-6     
    // Roll die_a
    die_a =  rand() % 6 + 1;
    // Roll die_b
    die_b =  rand() % 6 + 1;
    // Calulate roll amount and return
    roll_value = die_a + die_b;
    return roll_value;
}


// Purpose: Play the first game of trail 
// Arguments: Int&: Casino winnings to increase or decrease (or neither) based 
//            on outcome of game
// Return: None
void first_game(int& winnings) {
    int dice_value = 0;     // Holds value of dice roll
    // roll dice
    dice_value = roll(); 
    // if roll 2,3,12 casino wins
    if (dice_value == 2 || dice_value == 3|| dice_value == 12)
        winnings += BET;
    // else if roll 7 or 11 casino lose
    else if (dice_value == 7 || dice_value == 11)
        winnings -= BET;
    // else go to point game
    else 
       point_game(winnings, dice_value);
}


// Purpose: Play the point game of trail
// Arguments: Int&: Casino winnings to increase or decrease (or neither) based 
//            on outcome of game
//            Int: Value of point roll 
// Return: None
void point_game(int& winnings, int point) {
    int dice_value = 0;     // Holds value of dice roll 2-12
    // roll dice
    dice_value = roll();
    // if roll 7 casino wins
    if (dice_value == 7)
         winnings += BET;
    // else if roll point casino lose
    else if (dice_value == point)
        winnings -= BET;
    // else go to point game
    else
         point_game(winnings, point);
}