#include <cstdlib>
#include <ctime>
#include "dice.h"

Dice::Dice()
{
    sides = 6;
    dice1 = 1;
    dice2 = 1;
}

void Dice::rollDice()
{
    dice1 = rand() % sides + 1;
    dice2 = rand() % sides + 1;
}

int Dice::getFirstDice()
{
    return dice1;
}

int Dice::getSecondDice()
{
    return dice2;
}
