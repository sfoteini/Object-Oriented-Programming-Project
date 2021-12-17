#include <iostream>
#include "space.h"

// TODO: Implement here the methods of Space, Property, RailRoad, Utility, and Tax
using namespace std;


//Space

Space :: Space(int id, string name, SpaceType type, string actionText){
    this -> id = id;
    this -> name = name;
    this -> type = type;
    this -> actionText = actionText;
    this -> owner = 0;
}

void Space :: setOwner(Player* owner){
    this -> owner = owner;
}

int Space :: getId(){
    return id;
}

string Space :: getName(){
    return name;
}

string Space :: getActionText(){
    return actionText;
}

bool Space :: typeIs(SpaceType type){
    if(this -> type == type)
        return true;
    else
        return false;
}

bool Space :: ownerIs(Player* player){
    if(owner == player)
        return true;
    else
        return false;
}

//Property

Property :: Property(int id, string name, SpaceType type, string actionText, int buyCost,
                     int upgradeCost, PropertyCategory category) : Space(id, name, type, actionText){

    this -> buyCost = buyCost;
    this -> upgradeCost = upgradeCost;
    this -> category = category;
    numberOfHouses = 0;
}

void Property :: setRent(int numberOfHouses, int inputRent){
    rent[numberOfHouses] = inputRent;
}

int Property :: getBuyingCost(){
    return buyCost;
}

int Property :: getUpgradeCost(){
    return upgradeCost;
}

int Property :: getNumberOfHouses(){
    return numberOfHouses;
}

PropertyCategory Property :: getCategory(){
    return category;
}


int Property :: getRent(){
    return rent[numberOfHouses];
}

void Property :: addHouse(){
    numberOfHouses++;
}


//RailRoad

RailRoad :: RailRoad(int id, string name, SpaceType type, string actionText, int buyCost)
                : Space(id, name, type, actionText){

    this -> buyCost = buyCost;
}

void RailRoad :: setRent(int numberOfRailRoads, int inputRent){
    rent[numberOfRailRoads] = inputRent;
}

int RailRoad :: getBuyingCost(){
    return buyCost;
}

int RailRoad :: getRent(){
    int number = owner -> getNumberOfRailRoadsOwned();
    return rent[number -1];
}


//Utility

Utility :: Utility(int id, string name, SpaceType type, string actionText, int buyCost, Dice* dice)
                : Space(id, name, type, actionText){

    this -> buyCost = buyCost;
    this -> dice = dice;
}

void Utility :: setRentMultiplier(int numberOfUtilities, int inputRentMultiplier){
    rentMultiplier[numberOfUtilities] = inputRentMultiplier;
}

int Utility :: getBuyingCost(){
    return buyCost;
}

int Utility :: getRent(){
    int number = owner -> getNumberOfUtilitiesOwned();
    int dice1 = dice -> getFirstDice();
    int dice2 = dice -> getSecondDice();
    int temp = rentMultiplier[number -1] * (dice1 + dice2);
    return temp;
}


//Tax

Tax :: Tax(int id, string name, SpaceType type, string actionText, int tax)
            : Space(id, name, type, actionText){

    this -> tax = tax;
}

int Tax :: getTax(){
    return tax;
}
