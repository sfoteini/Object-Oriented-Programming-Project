#ifndef ACTIONS_H
#define ACTIONS_H

#include "bank.h"
#include "space.h"
#include "player.h"

/**
 * Function that makes a move for a player (sets the location). If the player
 * passes from the start, then the player gets 200.
 *
 * @param bank the bank object, used to give money to the player.
 * @param players the array of players, used to get the player according to playerTurn.
 * @param playerTurn the index of the player that has the turn, either 0 or 1.
 * @param diceRoll the amount of the dice (equal to the sum of both dice).
 * @return the index of the new space (location) of the player.
 */
int makeMove(Bank &bank, Player players[], int playerTurn, int diceRoll);

/**
 * Function that makes an action for a player according to the space. Different actions take place
 * according to the type of the space ("Property", "RailRoad", "Utility", "Tax", "FreeParking").
 *
 * @param bank the bank object, used to give money to the player.
 * @param players the array of players, used to get the player according to playerTurn.
 * @param spaces the array of board spaces, used to get the current space with the newSpace index.
 * @param playerTurn the index of the player that has the turn, either 0 or 1.
 * @param newSpace the index of the current space of the player.
 */
void makeAction(Bank &bank, Player players[], Space spaces[], int playerTurn, int newSpace);

#endif // ACTIONS_H
