#include "bank.h"

Bank::Bank()
{
    money = 20580;
    freeParkMoney = 0;
}

void Bank::giveMoneyToBank(int amount)
{
    money = money + amount;
}

void Bank::giveMoneyToFreePark(int amount)
{
    money = money + amount;
}

int Bank::getMoney()
{
    return money;
}

int Bank::getFreeParkMoney()
{
    return freeParkMoney;
}

void Bank::takeMoneyFromBank(int amount)
{
    money = money - amount;
}

int Bank::takeFreeParkMoney()
{
    // Get the amount of free park money and make them zero
    int tempFreeParkMoney = freeParkMoney;
    freeParkMoney = 0;
    return tempFreeParkMoney;
}

