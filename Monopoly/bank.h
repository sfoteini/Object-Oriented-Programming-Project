#ifndef BANK_H
#define BANK_H

#include <string>

using namespace std;

/**
 * Class denoting a bank.
 */
class Bank
{

private:
    int money;
    int freeParkMoney;

public:
    /**
     * Initializes this bank object.
     */
    Bank();

    /**
     * Get the amount of money of the bank.
     *
     * @return the amount of money of the bank.
     */
    int getMoney();

    /**
     * Get the amount of free park money.
     *
     * @return the amount of free park money.
     */
    int getFreeParkMoney();

    /**
     * Function that receives an amount of money and adds it to the bank money.
     *
     * @param amount the amount to be added in the bank money.
     */
    void giveMoneyToBank(int amount);

    /**
     * Function that removes an amount of money from the bank money.
     *
     * @param amount the amount to be removed from the bank money.
     */
    void takeMoneyFromBank(int amount);

    /**
     * Function that receives an amount of money and adds it to the free park money.
     *
     * @param amount the amount to be added in the free park money.
     */
    void giveMoneyToFreePark(int amount);

    /**
     * Function that removes all free park money and returns it.
     *
     * @return the amount of the free park money that is removed.
     */
    int takeFreeParkMoney();

};
#endif
