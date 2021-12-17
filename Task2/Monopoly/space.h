#ifndef SPACE_H
#define SPACE_H

#include <string>

using namespace std;

/**
 * Class denoting a space of the board. Spaces can be properties,
 * railroads, utilities, taxes, jail, etc.
 */
class Space
{

private:
    int id;
    string name;
    string type;
    string actionText;
    int owner;
    int rent;
    int tax;
    int buyCost;

public:
    /**
     * Initializes this space object. Does nothing.
     */
    Space();

    // functions to set values
    void setId(int newId);
    void setName(string newName);
    void setType(string newType);
    void setActionText(string newActionText);
    void setRent(int newRent);
    void setTax(int newTax);
    void setBuyingCost(int newBuyCost);
    void setOwner(int newOwner);

    // functions to get values
    int getId();
    string getName();
    string getType();
    string getActionText();
    int getRent();
    int getTax();
    int getBuyingCost();
    int getOwner();
};

#endif

