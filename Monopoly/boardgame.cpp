#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "space.h"
#include "player.h"
#include "dice.h"
#include "bank.h"
#include "boardgame.h"
#include "helpers.h"

using namespace std;

BoardGame::BoardGame(Player** players, Bank* bank, Deck* community, Deck* chance)
{
    dice = new Dice;

    // Initialize spaces in board
    spaces = new Space*[40];
    std::ifstream file("data/spaces.csv");
    CSVRow row;
    int rowindex = -1;
    while(file >> row)
    {
        if (rowindex >= 0)
        {
            int id = atoi(row[0].c_str());
            string name = row[1].c_str();
            string type = row[2].c_str();
            string actionText = row[3].c_str();
            if (type == "Property")
            {
                int buyingCost = atoi(row[4].c_str());
                int upgradeCost = atoi(row[5].c_str());
                string category = row[13].c_str();
                Property* property;
                if (category == "Dark Purple")
                    property = new Property(id, name, PropertyType, actionText, buyingCost, upgradeCost, DarkPurple);
                else if (category == "Light Blue")
                    property = new Property(id, name, PropertyType, actionText, buyingCost, upgradeCost, LightBlue);
                if (category == "Pink")
                    property = new Property(id, name, PropertyType, actionText, buyingCost, upgradeCost, Pink);
                if (category == "Orange")
                    property = new Property(id, name, PropertyType, actionText, buyingCost, upgradeCost, Orange);
                if (category == "Red")
                    property = new Property(id, name, PropertyType, actionText, buyingCost, upgradeCost, Red);
                if (category == "Yellow")
                    property = new Property(id, name, PropertyType, actionText, buyingCost, upgradeCost, Yellow);
                if (category == "Green")
                    property = new Property(id, name, PropertyType, actionText, buyingCost, upgradeCost, Green);
                if (category == "Dark Blue")
                    property = new Property(id, name, PropertyType, actionText, buyingCost, upgradeCost, DarkBlue);
                property->setRent(0, atoi(row[6].c_str()));
                property->setRent(1, atoi(row[7].c_str()));
                property->setRent(2, atoi(row[8].c_str()));
                property->setRent(3, atoi(row[9].c_str()));
                property->setRent(4, atoi(row[10].c_str()));
                property->setRent(5, atoi(row[11].c_str()));
                spaces[rowindex] = property;
            }
            else if (type == "RailRoad")
            {
                RailRoad* railroad = new RailRoad(id, name, RailRoadType, actionText,
                                                  atoi(row[4].c_str())); // buyingCost
                railroad->setRent(0, atoi(row[6].c_str()));
                railroad->setRent(1, atoi(row[7].c_str()));
                railroad->setRent(2, atoi(row[8].c_str()));
                railroad->setRent(3, atoi(row[9].c_str()));
                spaces[rowindex] = railroad;
            }
            else if (type == "Utility")
            {
                Utility* utility = new Utility(id, name, UtilityType, actionText,
                                               atoi(row[4].c_str()), // buyingCost
                                               dice);
                utility->setRentMultiplier(0, atoi(row[6].c_str()));
                utility->setRentMultiplier(1, atoi(row[7].c_str()));
                spaces[rowindex] = utility;
            }
            else if (type == "Tax")
            {
                spaces[rowindex] = new Tax(id, name, TaxType, actionText,
                                           atoi(row[12].c_str())); // tax
            }
            else
            {
                SpaceType spaceType;
                if (type == "FreeParking") spaceType = FreeParkingType;
                else if (type == "GoJail") spaceType = GoJailType;
                else if (type == "CommunityChest") spaceType = CommunityChestType;
                else if (type == "Chance") spaceType = ChanceType;
                else if (type == "Jail") spaceType = JailType;
                else if (type == "START") spaceType = STARTType;
                spaces[rowindex] = new Space(id, name, spaceType, actionText);
            }
        }
        rowindex++;
    }

    this->bank = bank;
    this->community = community;
    this->chance = chance;
    this->players = players;
    players[0]->setSpaces(spaces);
    players[1]->setSpaces(spaces);

    playerTurn = 0;
}

Space* BoardGame::getSpace(int num)
{
    return spaces[num];
}

Dice* BoardGame::rollDice()
{
    dice->rollDice();
    return dice;
}

Space* BoardGame::movePlayer(int diceRoll1, int diceRoll2)
{
    Player* currentPlayer = players[playerTurn];

    // Move player
    int oldSpace = currentPlayer->getLocation();
    int newSpace = (oldSpace + diceRoll1 + diceRoll2) % 40;
    currentPlayer->setLocation(newSpace);

    // Check if we pass from start
    if(oldSpace > newSpace)
    {
        bank->takeMoneyFromBank(200);
        currentPlayer->giveMoneyToPlayer(200);
    }
    return spaces[newSpace];
}

Space* BoardGame::actOnSpace(Space* space)
{
    Player* currentPlayer = players[playerTurn];
    Player* otherPlayer = players[1 - playerTurn];

    if(space->typeIs(PropertyType) || space->typeIs(RailRoadType) || space->typeIs(UtilityType))
    {
        // if the property is owned by the other player
        if(space->ownerIs(otherPlayer))
        {
            if(space->typeIs(PropertyType)){
                Property* property = (Property*) space;
                otherPlayer->giveMoneyToPlayer(property->getRent());
                currentPlayer->takeMoneyFromPlayer(property->getRent());
            }
            else if(space->typeIs(RailRoadType)){
                RailRoad* railroad = (RailRoad*) space;
                otherPlayer->giveMoneyToPlayer(railroad->getRent());
                currentPlayer->takeMoneyFromPlayer(railroad->getRent());
            }
            else if(space->typeIs(UtilityType)){
                Utility* utility = (Utility*) space;
                otherPlayer->giveMoneyToPlayer(utility->getRent());
                currentPlayer->takeMoneyFromPlayer(utility->getRent());
            }
        }
    }
    else if(space->typeIs(TaxType))
    {
        currentPlayer->takeMoneyFromPlayer(((Tax*)space)->getTax());
        bank->giveMoneyToFreePark(((Tax*)space)->getTax());
    }
    else if(space->typeIs(FreeParkingType))
    {
        currentPlayer->giveMoneyToPlayer(bank->getFreeParkMoney());
        bank->takeFreeParkMoney();
    }
    else if(space->typeIs(GoJailType))
    {
        currentPlayer->setLocation(10);
        currentPlayer->takeMoneyFromPlayer(200);
        bank->giveMoneyToFreePark(200);
        space = spaces[10];
    }
    else if(space->typeIs(CommunityChestType) || space->typeIs(ChanceType))
    {
        // Do nothing, as the card is drawn from outside the boardGame
        // using the Chance and CommunityChest objects, and then the
        // card actions are executed using the actOnCard method
    }
    return space;
}

Space* BoardGame::actOnCard(Card* card)
{
    Player* currentPlayer = players[playerTurn];
    int currentLocation = currentPlayer->getLocation(); // save current location
    card->cardAction(bank, currentPlayer); // make the move
    int nextLocation = currentPlayer->getLocation(); // get final location
    if(currentLocation > nextLocation) // if the player has passed the start
    {
        // then the player gets 200 from the bank
        bank->takeMoneyFromBank(200);
        currentPlayer->giveMoneyToPlayer(200);
    }
    return spaces[nextLocation];
}

bool BoardGame::endTurn()
{
    playerTurn = 1 - playerTurn;
    return players[1 - playerTurn]->getMoney() >= 0 && bank->getMoney() >= 0;
}

int BoardGame::getPlayerTurn()
{
    return playerTurn;
}
