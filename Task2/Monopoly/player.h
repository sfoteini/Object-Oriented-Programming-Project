#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

/**
 * Class denoting a player.
 */
class Player
{

private:
    int id;
    int location;
    int money;
    string name;

public:
    /**
     * Initializes this player object, by setting its id, name, location, and money.
     *
     * @param playerId the id of the player.
     */
    Player(int playerId);

    // functions to get values
    int getId();
    int getLocation();
    int getMoney();
    string getName();

    /**
     * Sets the location of the player.
     *
     * @param spaceNum the location to be set (id of space).
     */
    void setLocation(int spaceNum);

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

};

#endif
