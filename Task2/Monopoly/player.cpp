#include <iostream>
#include <sstream>

#include "player.h"

using namespace std;

// TODO: Implement here the methods of Player
Player :: Player(int playerId) {
    id = playerId;
    location = 0;
    money = 1500;
    if(id == 0){
        name = "Player1";
    }
    else {
        name = "Player2";
    }
}

int Player :: getId(){
    return id;
}

int Player :: getLocation(){
    return location;
}

int Player :: getMoney(){
    return money;
}

string Player :: getName(){
    return name;
}

void Player :: setLocation(int spaceNum){
    if(spaceNum > 39)
        location = spaceNum - 40;
    else
        location = spaceNum;
}

void Player :: giveMoneyToPlayer(int amount){
    money += amount;
}

void Player :: takeMoneyFromPlayer(int amount){
    money -= amount;
}
