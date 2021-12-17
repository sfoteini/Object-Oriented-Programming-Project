#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "space.h"

using namespace std;

class Space;
class Property;
class RailRoad;
class Utility;

/**
 * Class denoting a player of the game.
 */
class Player
{

private:
    int id;
    int location;
    int money;

protected:
    string name;
    Space** spaces;

public:
    /**
     * Initializes this player object, by setting its id, name, location, and money.
     *
     * @param playerId the id of the player.
     */
    Player(int id);

    //functions to set values
    void setSpaces(Space** spaces);
    void setLocation(int spaceNum);

    //functions to get values
    string getName();
    int getLocation();
    int getMoney();

    /**
     * Checks if the player owns a space given its index/id.
     *
     * @param inputIndex the index/id of the space to be checked if the player owns it.
     * @return true if the player owns the space that has the given id, or false otherwise.
     */
    bool ownsProperty(int inputIndex);

    /**
     * Checks if the player owns the space given.
     *
     * @param space pointer to a space to be checked if the player owns it.
     * @return true if the player owns the space given, or false otherwise.
     */
    bool ownsProperty(Space* space);

    /**
     * Function that receives an amount of money and adds it to the player money.
     *
     * @param amount the amount to be added in the player money.
     */
    void giveMoneyToPlayer(int amount);

    /**
     * Function that removes an amount of money from the player money.
     *
     * @param amount the amount to be removed from the player money.
     */
    void takeMoneyFromPlayer(int amount);

    /**
     * Computes and returns the number of railroads owned by the player.
     *
     * @return the number of railroads owned by the player.
     */
    int getNumberOfRailRoadsOwned();

    /**
     * Computes and returns the number of utilities owned by the player.
     *
     * @return the number of utilities owned by the player.
     */
    int getNumberOfUtilitiesOwned();

    /**
     * Decides whether the player should buy the given space (the player buys it if the money of the player are more than 5 times the cost of the space).
     *
     * @param space pointer to space that is decided if the player wants to buy it.
     * @return true if the player wants to buy the space given, or false otherwise.
     */
    bool decideBuy(Space* space);

    /**
     * Decides whether the player should upgrade any of the owned properties (the player upgrades the first property for which
     * the money of the player are more than 5 times the upgrade cost of the property).
     *
     * @return the space id of the property to be upgraded, or -1 in case the player does not want to upgrade any property.
     */
    int decideUpgrade();

    /**
     * Determines whether the player can buy the given property. The property can be bought
     * only if it does not already belong to some other player and also if the player has enough money
     * to buy it (at least equal to the cost of the property).
     *
     * @param property pointer to property that is found if the player can buy it.
     * @return true if the player can buy the property given, or false otherwise.
     */
    bool canBuy(Property* property);

    /**
     * Determines whether the player can buy the given railroad. The railroad can be bought
     * only if it does not already belong to some other player and also if the player has enough money
     * to buy it (at least equal to the cost of the railroad).
     *
     * @param railroad pointer to railroad that is found if the player can buy it.
     * @return true if the player can buy the railroad given, or false otherwise.
     */
    bool canBuy(RailRoad* railroad);

    /**
     * Determines whether the player can buy the given utility. The utility can be bought
     * only if it does not already belong to some other player and also if the player has enough money
     * to buy it (at least equal to the cost of the utility).
     *
     * @param utility pointer to utility that is found if the player can buy it.
     * @return true if the player can buy the utility given, or false otherwise.
     */
    bool canBuy(Utility* utility);

    /**
     * Determines whether the player can upgrade the given property. The property can be upgraded if the property
     * belongs to the player, the player has enough money to upgrade it (at least equal to the upgrade cost of the property),
     * the player owns all the properties of the property category, and the current number of houses of the property
     * is less than 5.
     *
     * @param property pointer to property that is found if the player can upgrade it.
     * @return true if the player can upgrade the property given, or false otherwise.
     */
    bool canUpgrade(Property* property);

    /**
     * Makes the player buy the given space. Sets the owner of the space to the pointer of this player.
     *
     * @param space the space of which the owner is set to this player.
     */
    void buy(Space* space);

    /**
     * Makes the player upgrade the given space. Adds a house to the given property.
     *
     * @param space the property to which a house is added.
     */
    void upgrade(Property* property);
};

#endif
