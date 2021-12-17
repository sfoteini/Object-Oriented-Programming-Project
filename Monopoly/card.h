#ifndef CARD_H
#define CARD_H

#include <string>
#include "bank.h"
#include "player.h"

/**
 * Class denoting a card. This class has to be extended in order to
 * provide the type of card (CardMoney or CardMove).
 */
class Card
{

private:
    int id;

protected:
    string text;

public:
    /**
     * Initializes the card with its id.
     *
     * @param id the unique identifier of the card.
     * @param text the text of the card.
     */
    Card(int id, string text);

    /**
     * Returns the id of the card.
     *
     * @return the id of the card.
     */
    int getId();

    /**
     * Implements the action of the card (money action between bank and player).
     * This function has to be implemented in classes extending this card class.
     *
     * @param bank the bank that participates in the card action.
     * @param player the player that participates in the card action.
     */
    virtual void cardAction(Bank* bank, Player* player) = 0;

    /**
     * Returns the text of the card.
     *
     * @return the text of the card.
     */
    string getText();

};

/**
 * Class denoting a card of type move. When the player draws this card, then
 * a move is made to a new location of the board.
 */
class CardMove : public Card
{

private:
    int location;

public:
    /**
     * Initializes the move card.
     *
     * @param id the unique identifier of the card.
     * @param text the text of the card.
     * @param location the location that the card moves player to.
     */
    CardMove(int id, string text, int location);

    /**
     * Implements the move action for the player. Moves the player to the location of this card.
     *
     * @param bank the bank that may participate in the movement.
     * @param player the player that will move (change location).
     */
    void cardAction(Bank* bank, Player* player);

};

/**
 * Class denoting a card of type money. When the player draws this card, a money
 * transaction takes place.
 */
class CardMoney : public Card
{

private:
    int amount;

public:
    /**
     * Initializes the money card.
     *
     * @param id the unique identifier of the card.
     * @param text the text of the card.
     * @param amount the amount of money relevant to this card.
     */
    CardMoney(int id, string text, int amount);

    /**
     * Implements the money action between bank and player. Transfers the amount of this card from the bank to the player.
     *
     * @param bank the bank that participates in the card action.
     * @param player the player that participates in the card action.
     */
    void cardAction(Bank* bank, Player* player);

};

#endif
