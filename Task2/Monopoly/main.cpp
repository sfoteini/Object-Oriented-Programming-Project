#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "player.h"
#include "space.h"
#include "dice.h"
#include "bank.h"
#include "helpers.h"
#include "actions.h"

using namespace std;

int main()
{
    srand(time(0));

    // Declare game objects
    Dice dice;
    Bank bank;
    Space spaces[40];
    Player players[2] = {Player(0), Player(1)};

    initializeSpaces(spaces);

    // Play game
    int playerTurn = 0;
    printState(spaces, players);
    do
    {
        dice.rollDice();
        int diceRoll1 = dice.getFirstDice();
        int diceRoll2 = dice.getSecondDice();

        // Move player
        int newSpace = makeMove(bank, players, playerTurn, diceRoll1 + diceRoll2);
        cout << players[playerTurn].getName() << " moved to " << spaces[newSpace].getName() << endl;

        // Act on new location of player
        makeAction(bank, players, spaces, playerTurn, newSpace);

        // Next turn
        playerTurn = 1 - playerTurn;
        printState(spaces, players);
        // Uncomment the following line to add a delay
        //for(int i = 0; i < 40000000; i++);
    } while (players[0].getMoney() >= 0 && players[1].getMoney() >= 0 && bank.getMoney() >= 0);

    // The winner is the player with the most money
    printState(spaces, players);
    cout << "Game Over!" << endl;
    if (players[0].getMoney() > players[1].getMoney())
        cout << "Player 1 is the winner!" << endl;
    else if (players[0].getMoney() < players[1].getMoney())
        cout << "Player 2 is the winner!" << endl;
    else
        cout << "It's a tie!" << endl;

    return 0;
}
