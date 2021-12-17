#include <sstream>
#include <iostream>
#include "player.h"

using namespace std;

Player::Player(int id)
{
    this->id = id;
    money = 1500;
    location = 0;

    if (id == 0)
        name = "Player 1";
    else if (id == 1)
        name = "Player 2";
}

void Player::setSpaces(Space** spaces)
{
    this->spaces = spaces;
}

void Player::setLocation(int spaceNum)
{
    location = spaceNum;
}

void Player::setOpponent(Player* opponent)
{
    this->opponent = opponent;
}

string Player::getName()
{
    return name;
}

void Player::giveMoneyToPlayer(int amount)
{
    money = money + amount;
}

int Player::getMoney()
{
    return money;
}

void Player::takeMoneyFromPlayer(int amount)
{
    money = money - amount;
}

int Player::getLocation()
{
    return location;
}

bool Player::ownsProperty(int inputIndex)
{
    return spaces[inputIndex]->ownerIs(this);
}

bool Player::ownsProperty(Space* space)
{
    return space->ownerIs(this);
}

bool Player::canUpgrade(Property* property)
{
    if (ownsProperty(property) && this->getMoney() >= property->getUpgradeCost())
    {
        for(int i = 0; i < 40; i++)
        {
            if (spaces[i]->typeIs(PropertyType))
            {
                Property* otherProperty = ((Property*)spaces[i]);
                if (otherProperty->getCategory() == property->getCategory())
                {
                    // here we can check all properties of the same category
                    if (!ownsProperty(otherProperty)) // if any of these properties does not belong
                        return false;                        // to the player, then no upgrade is possible
                }
            }
        }
        if (property->getNumberOfHouses() < 5)
            return true;
    }
    return false;
}

bool Player::canBuy(Property* property)
{
    // if the space does not belong to anybody
    if(property->ownerIs(NULL))
    {
        // if player has enough money to buy it
        if(this->getMoney() >= property->getBuyingCost())
        {
            return true;
        }
    }
    return false;
}

bool Player::canBuy(RailRoad* railroad)
{
    // if the space does not belong to anybody
    if(railroad->ownerIs(NULL))
    {
        // if player has enough money to buy it
        if(this->getMoney() >= railroad->getBuyingCost())
        {
            return true;
        }
    }
    return false;
}

bool Player::canBuy(Utility* utility)
{
    // if the space does not belong to anybody
    if(utility->ownerIs(NULL))
    {
        // if player has enough money to buy it
        if(this->getMoney() >= utility->getBuyingCost())
        {
            return true;
        }
    }
    return false;
}

void Player::upgrade(Property* space)
{
    space->addHouse();
}

void Player::buy(Space* space)
{
    space->setOwner(this);
}

int Player::getNumberOfRailRoadsOwned()
{
    int numberOfRailRoads = 0;
    for(int i = 0; i < 40; i++){
        if (spaces[i]->typeIs(RailRoadType) && ownsProperty(spaces[i]))
            numberOfRailRoads++;
    }
    return numberOfRailRoads;
}

int Player::getNumberOfUtilitiesOwned(){
    int numberOfUtilities = 0;
    for(int i = 0; i < 40; i++) {
        if (spaces[i]->typeIs(UtilityType) && ownsProperty(spaces[i]))
            numberOfUtilities++;
    }
    return numberOfUtilities;
}

HumanPlayer::HumanPlayer(int id) : Player(id)
{
}

bool HumanPlayer::decideBuy(Space* space)
{
    char input;
    do
    {
        cout << name << ", do you want to buy " << space->getName() << "? [y/n] ";
        cin >> input;
    }
    while( !cin.fail() && input!='y' && input!='n');
    return input=='y';
}

int HumanPlayer::decideUpgrade()
{
    // Find out how many properties can be upgraded
    int numPropertiesThatCanBeUpgraded = 0;
    for(int i = 0; i < 40; i++)
    {
        if (spaces[i]->typeIs(PropertyType) && canUpgrade((Property*)spaces[i]))
            numPropertiesThatCanBeUpgraded++;
    }

    int *allowedNumbers = new int[numPropertiesThatCanBeUpgraded + 1];
    int index = 0;
    int input;
    bool stop;
    do
    {
        cout << "Which property would you like to upgrade? [-1 for none]" << endl;
        for(int i = 0; i < 40; i++)
        {
            if (spaces[i]->typeIs(PropertyType))
            {
                Property* property = ((Property*)spaces[i]);
                if (canUpgrade(property))
                {
                    allowedNumbers[index++] = i;
                    cout << property->getId() << ": " << property->getName() << " (" << property->getNumberOfHouses() << " houses)" << endl;
                }
            }
        }
        allowedNumbers[index] = -1;
        cin >> input;
        stop = false;
        for(int k = 0; k < numPropertiesThatCanBeUpgraded + 1; k++)
        {
            if (allowedNumbers[k] == input)
                stop = true;
        }
    }
    while( !cin.fail() && !stop);
    delete [] allowedNumbers;
    return input;
}

ComputerPlayer::ComputerPlayer(int id) : Player(id)
{
}

bool ComputerPlayer::decideBuy(Space* space)
{
    if (space->typeIs(PropertyType) && getMoney() > 5 * ((Property*)space)->getBuyingCost())
        return true;
    else if (space->typeIs(RailRoadType) && getMoney() > 5 * ((RailRoad*)space)->getBuyingCost())
        return true;
    else if (space->typeIs(UtilityType) && getMoney() > 5 * ((Utility*)space)->getBuyingCost())
        return true;
    else
        return false;
}

int ComputerPlayer::decideUpgrade()
{
    for(int i = 0; i < 40; i++)
    {
        if (spaces[i]->typeIs(PropertyType) && canUpgrade((Property*)spaces[i]) &&
            getMoney() > 5 * ((Property*)spaces[i])->getUpgradeCost())
        {
            return i;
        }
    }
    return -1;
}

