#include <iostream>

#include "actions.h"

using namespace std;

int makeMove(Bank &bank, Player players[], int playerTurn, int diceRoll)
{
    // TODO: Implement this function
    int prevLocation = players[playerTurn].getLocation();
    players[playerTurn].setLocation(prevLocation + diceRoll);
    int newLocation = players[playerTurn].getLocation();
    if(newLocation == 0 || ((prevLocation + diceRoll) > 40)){
        players[playerTurn].giveMoneyToPlayer(200);
        bank.takeMoneyFromBank(200);
    }
    return newLocation;
}

void makeAction(Bank &bank, Player players[], Space spaces[], int playerTurn, int newSpace)
{
    // TODO: Implement this function
    string type = spaces[newSpace].getType();
    if(type == "Property" || type == "RailRoad" || type == "Utility"){
        if(spaces[newSpace].getOwner() == (1 - playerTurn)){
            int rent = spaces[newSpace].getRent();
            players[playerTurn].takeMoneyFromPlayer(rent);
            players[1 - playerTurn].giveMoneyToPlayer(rent);
        }
        else if(spaces[newSpace].getOwner() == -1){
            int buyCost = spaces[newSpace].getBuyingCost();
            if(players[playerTurn].getMoney() >= (5 * buyCost)){
                spaces[newSpace].setOwner(playerTurn);
                players[playerTurn].takeMoneyFromPlayer(buyCost);
                bank.giveMoneyToBank(buyCost);
            }
        }
    }
    else if(type == "Tax"){
        int tax = spaces[newSpace].getTax();
        players[playerTurn].takeMoneyFromPlayer(tax);
        bank.giveMoneyToFreePark(tax);
    }
    else if(type == "FreeParking"){
        int money = bank.takeFreeParkMoney();
        players[playerTurn].giveMoneyToPlayer(money);
    }
    else if(type == "GoJail"){
        players[playerTurn].setLocation(10);
        players[playerTurn].takeMoneyFromPlayer(200);
        bank.giveMoneyToFreePark(200);
    }
}
