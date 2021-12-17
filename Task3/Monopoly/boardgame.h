#ifndef BOARDGAME_H
#define BOARDGAME_H

#include "dice.h"
#include "space.h"
#include "player.h"

class BoardGame
{
private:
    Player** players;
    Bank* bank;
    Space** spaces;
    Dice* dice;
    int playerTurn;

public:
    /**
     * Initializes this game object, by setting the players and the bank.
     *
     * @param players the players of the game.
     * @param bank the bank of the game.
     */
    BoardGame(Player** players, Bank* bank);

    /**
     * Rolls the dice and returns the pointer to the dice object.
     * The result of rolling can be retrieved using the getFirstDice and getSecondDice functions.
     *
     * @return a pointer to the dice object.
     */
    Dice* rollDice();

    /**
     * Function that makes a move for a player (sets the location). If the player
     * passes from the start, then the player gets 200.
     *
     * @param diceRoll1 the value of the first of the dice.
     * @param diceRoll2 the value of the second of the dice.
     * @return the resulting space where the player is moved.
     */
    Space* movePlayer(int diceRoll1, int diceRoll2);

    /**
     * Function that makes an action for a player according to the space. Different actions take place
     * according to the type of the space. The function also returns the resulting space where the player
     * is moved (used for actions that move the player, such as go to jail)
     *
     * @param space the resulting space where the player has moved.
     * @return the resulting space where the player is moved.
     */
    Space* actOnSpace(Space* space);

    /**
     * Returns a space of the board given its id.
     *
     * @param space the id of the space to be returned.
     * @return the space of which the id is given.
     */
    Space* getSpace(int num);

    /**
     * Ends this turn and checks if the game has ended (the money of a player or the money of the bank are negative).
     *
     * @return true if the game goes on, or false if it has ended.
     */
    bool endTurn();

    /**
     * Returns the turn of the player.
     *
     * @return 0 if it is the turn of the first player, or 1 if it is the turn of the second player.
     */
    int getPlayerTurn();
};

#endif // BOARDGAME_H
