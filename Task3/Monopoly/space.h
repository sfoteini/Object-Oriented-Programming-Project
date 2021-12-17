#ifndef SPACE_H
#define SPACE_H

#include <string>
#include "dice.h"
#include "player.h"

class Player;

using namespace std;

/**
 * Enumeration used to represent the different types of spaces.
 */
enum SpaceType {PropertyType, RailRoadType, UtilityType, TaxType, FreeParkingType,
                GoJailType, CommunityChestType, ChanceType, JailType, STARTType};

/**
 * Class denoting a space of the board. Spaces can be properties,
 * railroads, utilities, taxes, jail, etc.
 */
class Space
{

private:
    int id;
    string name;
    SpaceType type;
    string actionText;

protected:
    Player* owner;

public:
    /**
     * Initializes the space given as input its id, i.e. its position in the board, its name,
     * its type (SpaceType), and its action text. The owner is also initialized to nothing.
     *
     * @param id the unique identifier of the space, which is also its board number.
     * @param name the name to be set in this space.
     * @param type the type to be set in this space.
     * @param actionText the action text to be set in this space.
     */
    Space(int id, string name, SpaceType type, string actionText);

    /**
     * Sets the owner of this space. The owner is a pointer to a Player object.
     *
     * @param owner the owner to be set for this space.
     */
    void setOwner(Player* owner);

    // functions to get values
    int getId();
    string getName();
    string getActionText();

    /**
     * Checks is the type of this space is the same as the type given.
     *
     * @param type the type to check if it is the same as the type of this space.
     * @return true if the type given is the same as the type of this space, or false otherwise.
     */
    bool typeIs(SpaceType type);

    /**
     * Checks is the owner of this space is the same as the owner given.
     *
     * @param owner the owner to check if it is the same as the owner of this space.
     * @return true if the owner given is the same as the owner of this space, or false otherwise.
     */
    bool ownerIs(Player* player);
};

/**
 * Enumeration used to represent the different categories of properties.
 */
enum PropertyCategory {DarkPurple, LightBlue, Pink, Orange, Red, Yellow, Green, DarkBlue};

/**
 * Class denoting a property of the board.
 */
class Property : public Space
{
private:
    int buyCost;
    int upgradeCost;
    int rent[6];
    PropertyCategory category;
    int numberOfHouses;

public:
    /**
     * Initializes the property given as input its id, i.e. its position in the board, its name, its type (SpaceType),
     * its action text, its buying cost, its upgrade cost (i.e. cost of each house), and its category.
     * This method at first calls the constructor of Space, while it also initializes the number of houses to 0.
     *
     * @param id the unique identifier of the property, which is also its board number.
     * @param name the name to be set in this property.
     * @param type the space type to be set in this property (which is actually equal to PropertyType).
     * @param actionText the action text to be set in this property.
     * @param buyCost the cost of buying this property.
     * @param upgradeCost the cost of upgrading this property (i.e. cost of each house).
     * @param category the category of this property.
     */
    Property(int id, string name, SpaceType type, string actionText, int buyCost, int upgradeCost, PropertyCategory category);

    /**
     * Sets the rent of this property for a specific number of houses.
     *
     * @param numberOfHouses the number of houses for which the rent is set.
     * @param inputRent the rent to be set in this property for the specified number of houses.
     */
    void setRent(int numberOfHouses, int inputRent);

    // functions to get values
    int getBuyingCost();
    int getUpgradeCost();
    int getNumberOfHouses();
    PropertyCategory getCategory();

    /**
     * Returns the rent of this property. Note that the rent depends on the number of houses that
     * currently exist in this property (values 0, 1, ..., 5).
     *
     * @return the rent value of this property.
     */
    int getRent();

    /**
     * Adds a house to this property by increasing the number of houses variable.
     */
    void addHouse();
};

/**
 * Class denoting a railroad of the board.
 */
class RailRoad : public Space
{
private:
    int buyCost;
    int rent[4];

public:
    /**
     * Initializes the railroad given as input its id, i.e. its position in the board, its name, its type (SpaceType),
     * its action text, and its buying cost. This method at first calls the constructor of Space.
     *
     * @param id the unique identifier of the railroad, which is also its board number.
     * @param name the name to be set in this railroad.
     * @param type the space type to be set in this railroad (which is actually equal to RailRoadType).
     * @param actionText the action text to be set in this railroad.
     * @param buyCost the cost of buying this railroad.
     */
    RailRoad(int id, string name, SpaceType type, string actionText, int buyCost);

    /**
     * Sets the rent of this railroad for a specific number of railroads belonging to a single player.
     * Note that the array is zero-based so if the owner of this railroad has 2 railroads in total, then
     * this function should set the rent value in index position 1.
     *
     * @param numberOfRailRoads the number of railroads for which the rent is set.
     * @param inputRent the rent to be set in this railroad for the specified number of owned railroads.
     */
    void setRent(int numberOfRailRoads, int inputRent);

    // functions to get values
    int getBuyingCost();

    /**
     * Returns the rent of this railroad. Note that the rent depends on the number of railroads that
     * belong to the owner of this railroad. Hint: this method uses Player::getNumberOfRailRoadsOwned().
     * Note that the array is zero-based so if the owner of this railroad has 2 railroads in total, then
     * this function should return the rent value in index position 1.
     *
     * @return the rent value of this railroad.
     */
    int getRent();
};

/**
 * Class denoting a utility of the board.
 */
class Utility : public Space
{
private:
    int buyCost;
    Dice* dice;
    int rentMultiplier[2];

public:
    /**
     * Initializes the utility given as input its id, i.e. its position in the board, its name, its type (SpaceType),
     * its action text, its buying cost, and a pointer to the dice of the game. This method at first calls the constructor of Space.
     *
     * @param id the unique identifier of the utility, which is also its board number.
     * @param name the name to be set in this utility.
     * @param type the space type to be set in this utility (which is actually equal to UtilityType).
     * @param actionText the action text to be set in this utility.
     * @param buyCost the cost of buying this utility.
     * @param dice a pointer to the dice of the game.
     */
    Utility(int id, string name, SpaceType type, string actionText, int buyCost, Dice* dice);

    /**
     * Sets the rent multiplier of this utility for a specific number of utilities belonging to a single player.
     * Note that the array is zero-based so if the owner of this utility has 2 utilities in total, then
     * this function should set the rent value in index position 1.
     *
     * @param numberOfUtilities the number of utilities for which the rent is set.
     * @param inputRentMultiplier the rent multiplier to be set in this utility for the specified number of owned utilities.
     */
    void setRentMultiplier(int numberOfUtilities, int inputRentMultiplier);

    // functions to get values
    int getBuyingCost();

    /**
     * Returns the rent of this utility. Note that the rent depends on the number of utilities that
     * belong to the owner of this utility. Hint: this method uses Player::getNumberOfUtilitiesOwned().
     * Note that the array is zero-based so if the owner of this utility has 2 utilities in total, then
     * this function should use the rent multiplier value in index position 1.
     * The final value of the rent is computed by multiplying the rent multiplier with the last value of the dice.
     *
     * @return the rent value of this utility.
     */
    int getRent();
};

/**
 * Class denoting a tax of the board.
 */
class Tax : public Space
{
private:
    int tax;

public:
    /**
     * Initializes the tax given as input its id, i.e. its position in the board, its name, its type (SpaceType),
     * its action text, and the value of the tax. This method at first calls the constructor of Space.
     *
     * @param id the unique identifier of the utility, which is also its board number.
     * @param name the name to be set in this utility.
     * @param type the space type to be set in this utility (which is actually equal to TaxType).
     * @param actionText the action text to be set in this utility.
     * @param tax the value of the tax.
     */
    Tax(int id, string name, SpaceType type, string actionText, int tax);

    // functions to get values
    int getTax();
};

#endif

