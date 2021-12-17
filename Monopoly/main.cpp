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

#ifdef USE_QT_LIB
#include <QApplication>
#include "gui/mainwindow.h"
#endif // USE_QT_LIB

using namespace std;

void printState(BoardGame* boardGame, Player** players)
{
    cout << endl;
    for(int p = 0; p < 2; p++)
    {
        cout << "PLAYER " << p + 1 << "  POS: ";
        if (players[p]->getLocation() >= 10)
            cout << players[p]->getLocation();
        else
            cout << " " << players[p]->getLocation();
        cout << "  $" << players[p]->getMoney() << "  PRP:";
        for(int i = 0; i < 40; i++)
        {
            if (players[p]->ownsProperty(i))
            {
                if (boardGame->getSpace(i)->typeIs(PropertyType))
                    cout << " " << i << "[" << ((Property*)boardGame->getSpace(i))->getNumberOfHouses() << "]";
                else if (boardGame->getSpace(i)->typeIs(RailRoadType))
                    cout << " " << i << "[R]";
                else if (boardGame->getSpace(i)->typeIs(UtilityType))
                    cout << " " << i << "[U]";
            }
        }
        cout << endl;
    }
}

int main(int argv, char* argc[])
{
    srand(time(0));

    Player** players = new Player*[2];
    players[0] = new ComputerPlayer(0);
    players[1] = new ComputerPlayer(1);
    players[0]->setOpponent(players[1]);
    players[1]->setOpponent(players[0]);
    Bank* bank = new Bank();
    Deck* community = new Deck("data/community.csv");
    Deck* chance = new Deck("data/chance.csv");
    BoardGame* boardGame = new BoardGame(players, bank, community, chance);


#ifdef USE_QT_LIB
    bool gui = true;
    if (gui)
    {
        QApplication app(argv, argc);
        MainWindow mainWindow(boardGame, players, bank, community, chance);
        mainWindow.windowSetUp();
        mainWindow.show();

        return app.exec();
    }
    else
#endif // USE_QT_LIB
    {
        printState(boardGame, players);
        Player* currentPlayer = players[boardGame->getPlayerTurn()];
        cout << "Turn of " << currentPlayer->getName() << endl;
        while (true)
        {
            // Check if current player can upgrade any space
            bool currentPlayerCanUpgradeAnySpace = false;
            for(int i = 0; i < 40; i++)
                if (boardGame->getSpace(i)->typeIs(PropertyType) && currentPlayer->canUpgrade((Property*)boardGame->getSpace(i)))
                    currentPlayerCanUpgradeAnySpace = true;

            if (currentPlayerCanUpgradeAnySpace){
                int propertyToUpgrade = currentPlayer->decideUpgrade();
                if (propertyToUpgrade >= 0){
                    Property* property = (Property*) boardGame->getSpace(propertyToUpgrade);
                    currentPlayer->takeMoneyFromPlayer(property->getUpgradeCost());
                    bank->giveMoneyToBank(property->getUpgradeCost());
                    currentPlayer->upgrade(property);
                }
            }

            Dice* dice = boardGame->rollDice();
            Space* space = boardGame->movePlayer(dice->getFirstDice(), dice->getSecondDice());

            int spaceId = space->getId();
            cout << currentPlayer->getName() << " moved to " << space->getName() << endl;
            if(space->typeIs(CommunityChestType))
            {
                Card* card = community->getNextCard();
                space = boardGame->actOnCard(card);
                cout << card->getText() << endl;
            }
            else if(space->typeIs(ChanceType))
            {
                Card* card = chance->getNextCard();
                space = boardGame->actOnCard(card);
                cout << card->getText() << endl;
            }
            space = boardGame->actOnSpace(space);
            if (spaceId != space->getId())
                cout << currentPlayer->getName() << " moved to " << space->getName() << endl;

            bool canBuy = false;
            if(space->typeIs(PropertyType)){
                Property* property = (Property*) space;
                canBuy = currentPlayer->canBuy(property);
            }
            else if(space->typeIs(RailRoadType)){
                RailRoad* railroad = (RailRoad*) space;
                canBuy = currentPlayer->canBuy(railroad);
            }
            else if(space->typeIs(UtilityType)){
                Utility* utility = (Utility*) space;
                canBuy = currentPlayer->canBuy(utility);
            }
            if (canBuy)
            {
                if (currentPlayer->decideBuy(space)){
                    if(space->typeIs(PropertyType)){
                        Property* property = (Property*) space;
                        currentPlayer->takeMoneyFromPlayer(property->getBuyingCost());
                        bank->giveMoneyToBank(property->getBuyingCost());
                        currentPlayer->buy(property);
                    }
                    else if(space->typeIs(RailRoadType)){
                        RailRoad* railroad = (RailRoad*) space;
                        currentPlayer->takeMoneyFromPlayer(railroad->getBuyingCost());
                        bank->giveMoneyToBank(railroad->getBuyingCost());
                        currentPlayer->buy(railroad);
                    }
                    else if(space->typeIs(UtilityType)){
                        Utility* utility = (Utility*) space;
                        currentPlayer->takeMoneyFromPlayer(utility->getBuyingCost());
                        bank->giveMoneyToBank(utility->getBuyingCost());
                        currentPlayer->buy(utility);
                    }
                    cout << currentPlayer->getName() << " purchased " << space->getName() << endl;
                }
            }

            if (boardGame->endTurn())
            {
                printState(boardGame, players);
                currentPlayer = players[boardGame->getPlayerTurn()];
                cout << "Turn of " << currentPlayer->getName() << endl;
                // Uncomment the following line to add a delay
                // for(int i = 0; i < 40000000; i++);
            }
            else
                break;
        }
        printState(boardGame, players);
        cout << "Game Over!" << endl;
        if (players[0]->getMoney() > players[1]->getMoney())
            cout << "Player 1 is the winner!" << endl;
        else if (players[0]->getMoney() < players[1]->getMoney())
            cout << "Player 2 is the winner!" << endl;
        else
            cout << "It's a tie!" << endl;
    }
}
