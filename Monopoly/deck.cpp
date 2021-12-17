#include "deck.h"
#include "helpers.h"
#include "card.h"
#include "shuffler.h"

Deck::Deck(const char* filename)
{
    deckSize = 10;
    cards = new Card*[deckSize];

    // Read cards from file
    std::ifstream cardsfile(filename);
    CSVRow cardsrow;
    int i = -1;
    while(cardsfile >> cardsrow)
    {
        if (i >= 0)
        {
            if (cardsrow[1] == "CardMove")
                cards[i] = new CardMove(i, cardsrow[2].c_str(), atoi(cardsrow[3].c_str()));
            else if (cardsrow[1] == "CardMoney")
                cards[i] = new CardMoney(i, cardsrow[2].c_str(), atoi(cardsrow[3].c_str()));
        }
        i++;
    }
    shuffleCards();
}

void Deck::shuffleCards()
{
    shuffle(cards, deckSize);
    currentIndex = 0;
}

Card* Deck::getNextCard()
{
    // Get the card which is currently on top
    Card* card = cards[currentIndex];
    currentIndex++;
    // Shuffle the cards if they are finished
    if (currentIndex == deckSize)
        shuffleCards();
    return card;
}

