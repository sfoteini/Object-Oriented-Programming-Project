#ifndef DICE_H
#define DICE_H

/**
 * Class denoting the dice.
 */
class Dice
{

private:
    int sides; // the number of sides of each dice
    int dice1;
    int dice2;

public:
    /**
     * Initializes the dice.
     */
    Dice();

    /**
     * Rolls two dice at random. The results of the roll are given by the
     * methods getFirstDice and getSecondDice.
     */
    void rollDice();

    /**
     * Returns the value of the first dice. This method should be called after
     * calling rollDice.
     *
     * @return the value of the first dice.
     */
    int getFirstDice();

    /**
     * Returns the value of the second dice. This method should be called after
     * calling rollDice.
     *
     * @return the value of the second dice.
     */
    int getSecondDice();
};

#endif
