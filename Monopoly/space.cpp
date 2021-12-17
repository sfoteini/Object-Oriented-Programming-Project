#include <iostream>
#include "space.h"

Space::Space(int id, string name, SpaceType type, string actionText)
{
    this->id = id;
    this->name = name;
    this->type = type;
    this->actionText = actionText;
    owner = NULL;
}

void Space::setOwner(Player* owner)
{
    this->owner = owner;
}

int Space::getId()
{
    return id;
}

string Space::getName()
{
    return name;
}

string Space::getActionText()
{
    return actionText;
}

bool Space::typeIs(SpaceType type)
{
    return this->type == type;
}

bool Space::ownerIs(Player* player){
    return owner == player;
}

Property::Property(int id, string name, SpaceType type, string actionText, int buyCost, int upgradeCost, PropertyCategory category) : Space(id, name, type, actionText)
{
    this->buyCost = buyCost;
    this->upgradeCost = upgradeCost;
    this->category = category;
    numberOfHouses = 0;
}

void Property::setRent(int numberOfHouses, int inputRent)
{
    rent[numberOfHouses] = inputRent;
}

int Property::getNumberOfHouses()
{
    return numberOfHouses;
}

PropertyCategory Property::getCategory()
{
    return category;
}

int Property::getBuyingCost()
{
    return buyCost;
}

int Property::getUpgradeCost()
{
    return upgradeCost;
}

int Property::getRent()
{
    return rent[numberOfHouses];
}

void Property::addHouse()
{
    numberOfHouses++;
}

RailRoad::RailRoad(int id, string name, SpaceType type, string actionText, int buyCost) : Space(id, name, type, actionText)
{
    this->buyCost = buyCost;
}

void RailRoad::setRent(int numberOfRailRoads, int inputRent)
{
    rent[numberOfRailRoads] = inputRent;
}

int RailRoad::getBuyingCost()
{
    return buyCost;
}

int RailRoad::getRent()
{
    return rent[owner->getNumberOfRailRoadsOwned() - 1];
}

Utility::Utility(int id, string name, SpaceType type, string actionText, int buyCost, Dice* dice) : Space(id, name, type, actionText)
{
    this->buyCost = buyCost;
    this->dice = dice;
}

void Utility::setRentMultiplier(int numberOfUtilities, int inputRentMultiplier)
{
    rentMultiplier[numberOfUtilities] = inputRentMultiplier;
}

int Utility::getBuyingCost()
{
    return buyCost;
}

int Utility::getRent()
{
    return rentMultiplier[owner->getNumberOfUtilitiesOwned() - 1] * (dice->getFirstDice() + dice->getSecondDice());
}

Tax::Tax(int id, string name, SpaceType type, string actionText, int tax) : Space(id, name, type, actionText)
{
    this->tax = tax;
}

int Tax::getTax()
{
    return tax;
}
