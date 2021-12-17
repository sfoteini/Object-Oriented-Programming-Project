#include "card.h"

// TODO: Implement here the methods of Card, CardMove, and CardMoney

Card::Card(int id, string text){
    this->id = id;
    this->text = text;
}

int Card::getId(){
    return id;
}

string Card::getText(){
    return text;
}

CardMove::CardMove(int id, string text, int location):Card(id, text){
    this->location = location;
}

void CardMove::cardAction(Bank* bank, Player* player){
    int oldLocation = player->getLocation();
    player->setLocation(location);

    // Check if we pass from start
    if(oldLocation > location)
    {
        bank->giveMoneyToBank(200);
        player->takeMoneyFromPlayer(200);
    }
}

CardMoney::CardMoney(int id, string text, int amount):Card(id, text){
    this->amount = amount;
}

void CardMoney::cardAction(Bank* bank, Player* player){
    bank->takeMoneyFromBank(amount);
    player->giveMoneyToPlayer(amount);
}
