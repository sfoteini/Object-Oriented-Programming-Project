#include "bank.h"

// TODO: Implement here the methods of Bank

Bank :: Bank(){
    money = 20580;
    freeParkMoney = 0;
}

int Bank :: getMoney(){
    return money;
}

int Bank :: getFreeParkMoney(){
    return freeParkMoney;
}

void Bank :: giveMoneyToBank(int amount){
    money += amount;
}

void Bank :: takeMoneyFromBank(int amount){
    money -= amount;
}

void Bank :: giveMoneyToFreePark(int amount){
    freeParkMoney += amount;
}

int Bank :: takeFreeParkMoney(){
    freeParkMoney = 0;
    return freeParkMoney;
}
