#ifndef DECK_H
#define DECK_H

#include "card.h"

/**
 * Class that implements a deck of cards. It shuffles the card and
 * provides the next card when required.
 */
class Deck
{
private:
    Card** cards;
    int deckSize; // the number of cards in the deck
    int currentIndex; // holds the current distance from the top of the card deck

public:
    /**
     * Initializes this class giving as input the filename to read the cards from.
     * The header of the csv filename is class;type;path;money and each line must
     * have the following format
     * chance OR community;CardMove OR CardMoney;Text of the card;Integer for the location/amount of the card
     *
     * @param filename the filename from which the cards are read.
     */
    Deck(const char* filename);

    /**
     * Returns the next card from the top of the deck. If the returned card is the
     * last card of the deck, then (upon returning) the cards are shuffled.
     *
     * @return Card* the card from the top of the deck.
     */
    Card* getNextCard();

    /**
     * Shuffles the cards of the deck.
     */
    void shuffleCards();
};

#endif // DECK_H
