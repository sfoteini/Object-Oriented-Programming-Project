#ifdef USE_QT_LIB
#include <iostream>
#include "bottomBar.h"
#include "mainwindow.h"
#include "../dice.h"

BottomBar::BottomBar(BoardGame* boardGame, CentralWidget* tempBoard, MainWindow* tempWindow)
{
    playSpeed = 500;
    this->boardGame = boardGame;

    //setting up all the buttons
    turnStatus = new QLabel();
    status = new QLabel();
    rollButton = new QPushButton("Roll Dice");
    purchaseButton = new QPushButton("Purchase");
    endTurnButton = new QPushButton("End Turn");

    computerSpeedLayout = new QGridLayout;
    computerSpeedStatus = new QLabel();
    computerSpeedStatus->setText(QString("Computer Delay (ms):"));
    computerSpeed = new QSpinBoxWithoutTextEdit;
    computerSpeed->setMinimum(0);
    computerSpeed->setMaximum(2000);
    computerSpeed->setSingleStep(100);
    computerSpeed->setValue(500);
    connect(computerSpeed, SIGNAL(valueChanged(int)), this, SLOT(changeComputerSpeed()) );
    computerSpeedLayout->addWidget(computerSpeedStatus, 0, 0, 0, 1, 0);
    computerSpeedLayout->addWidget(computerSpeed, 0, 1, 0, 1, 0);

    layout = new QGridLayout;
    layout->addWidget(turnStatus, 0, 0, 0, 1, 0);
    layout->addWidget(status, 0, 1, 0, 4, 0);
    layout->addLayout(computerSpeedLayout, 0, 5, 0, 1, 0);
    layout->addWidget(endTurnButton, 0, 6, 0, 2, 0);
    layout->addWidget(purchaseButton, 0, 8, 0, 2, 0);
    layout->addWidget(rollButton, 0, 10, 0, 2, 0);

    this->setMaximumSize(QSize(1200, 40));

    bottomWidget = new QWidget(this);
    bottomWidget->setLayout(layout);
    setWidget(bottomWidget);

    int left, top, right, bottom;
    layout->getContentsMargins(&left, &top, &right, &bottom);
    layout->setContentsMargins(left, top - 1, right, bottom - 1);

    //connecting buttons
    connect(rollButton, SIGNAL(clicked()), this, SLOT(rollDice()) );
    connect(endTurnButton, SIGNAL(clicked()), this, SLOT(endTurn()) );
    connect(purchaseButton, SIGNAL(clicked()), this, SLOT(purchase()) );

    //disabling the endTurnButton
    endTurnButton->setEnabled(false);
    purchaseButton->setEnabled(false);

    turnStatus->setText(QString("Turn of Player ") + QString::number(boardGame->getPlayerTurn() + 1));
    status->setText(QString("Roll the dice"));

    monopolyBoard = tempBoard;
    monopolyBoard->initializingCards();
    myWindow = tempWindow;

    // This code is only relevant if the player is a computer
    if (myWindow->playerIsComputer(boardGame->getPlayerTurn())){
        QTimer::singleShot(playSpeed, this, SLOT(rollDiceWithAnimation()));
    }
}

void BottomBar::rollDice()
{
    int currentPlayerNum = boardGame->getPlayerTurn();

    // roll the dice
    Dice* dice = boardGame->rollDice();
    monopolyBoard->changeDiceImg(dice->getFirstDice(), dice->getSecondDice());

    // move the player
    Space* space = boardGame->movePlayer(dice->getFirstDice(), dice->getSecondDice());
    myWindow->setPlayerLocation(currentPlayerNum, space->getId());

    space = boardGame->actOnSpace(space);
    myWindow->updatePlayersMoney();

    bool canBuy = false;
    if(space->typeIs(PropertyType)){
        Property* property = (Property*) space;
        canBuy = myWindow->getCurrentPlayer()->canBuy(property);
    }
    else if(space->typeIs(RailRoadType)){
        RailRoad* railroad = (RailRoad*) space;
        canBuy = myWindow->getCurrentPlayer()->canBuy(railroad);
    }
    else if(space->typeIs(UtilityType)){
        Utility* utility = (Utility*) space;
        canBuy = myWindow->getCurrentPlayer()->canBuy(utility);
    }
    purchaseButton->setEnabled(canBuy);
    endTurnButton->setEnabled(true);
    rollButton->setEnabled(false);

    status->setText(QString("Player ") + QString::number(boardGame->getPlayerTurn() + 1) +
                    QString(" moved to ") + QString(space->getName().c_str()));

    // This code is only relevant if the player is a computer
    if (myWindow->playerIsComputer(boardGame->getPlayerTurn())){
        if (canBuy){
            Player* currentPlayer = myWindow->getCurrentPlayer();
            Bank* bank = myWindow->getBank();
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
                QTimer::singleShot(playSpeed, this, SLOT(purchaseWithAnimation()));
                QTimer::singleShot(2 * playSpeed, this, SLOT(endTurnWithAnimation()));
            }
            else{
                QTimer::singleShot(playSpeed, this, SLOT(endTurnWithAnimation()));
            }
        }
        else{
            QTimer::singleShot(playSpeed, this, SLOT(endTurnWithAnimation()));
        }
    }
}

void BottomBar::changeComputerSpeed(){
    playSpeed = ((QSpinBox*) sender())->value();
}

void BottomBar::endTurnWithAnimation(){
    endTurnButton->animateClick();
}

void BottomBar::rollDiceWithAnimation(){
    rollButton->animateClick();
}

void BottomBar::purchaseWithAnimation(){
    purchaseButton->setDown(true);
    QTimer::singleShot(100, this, SLOT(purchaseWithAnimationHelper()));
}
void BottomBar::purchaseWithAnimationHelper(){
    purchaseButton->setDown(false);
    myWindow->playerPropertyWasBought(boardGame->getPlayerTurn(), myWindow->getPlayerLocation(boardGame->getPlayerTurn()));
    purchaseButton->setEnabled(false);
}

bool BottomBar::upgradeProperty(int propertyToUpgrade)
{
    Space* space = boardGame->getSpace(propertyToUpgrade);
    if (space->typeIs(PropertyType) && myWindow->getCurrentPlayer()->canUpgrade((Property*)space))
    {
        myWindow->getCurrentPlayer()->upgrade((Property*)space);
        status->setText(QString("Player ") + QString::number(boardGame->getPlayerTurn() + 1) + QString(" upgraded ") +
                        QString(space->getName().c_str()) + QString(" - Roll the dice"));
        return true;
    }
    return false;
}

void BottomBar::purchase()
{
    Space* space = boardGame->getSpace(myWindow->getPlayerLocation(boardGame->getPlayerTurn()));
    if(space->typeIs(PropertyType)){
        Property* property = (Property*) space;
        myWindow->getCurrentPlayer()->takeMoneyFromPlayer(property->getBuyingCost());
        myWindow->getBank()->giveMoneyToBank(property->getBuyingCost());
        myWindow->getCurrentPlayer()->buy(property);
    }
    else if(space->typeIs(RailRoadType)){
        RailRoad* railroad = (RailRoad*) space;
        myWindow->getCurrentPlayer()->takeMoneyFromPlayer(railroad->getBuyingCost());
        myWindow->getBank()->giveMoneyToBank(railroad->getBuyingCost());
        myWindow->getCurrentPlayer()->buy(railroad);
    }
    else if(space->typeIs(UtilityType)){
        Utility* utility = (Utility*) space;
        myWindow->getCurrentPlayer()->takeMoneyFromPlayer(utility->getBuyingCost());
        myWindow->getBank()->giveMoneyToBank(utility->getBuyingCost());
        myWindow->getCurrentPlayer()->buy(utility);
    }
    myWindow->updatePlayersProperties(boardGame->getPlayerTurn());
    purchaseButton->setEnabled(false);
    myWindow->updatePlayersMoney();

    status->setText(QString("Player ") + QString::number(boardGame->getPlayerTurn() + 1) +
                    QString(" purchased ") + QString(space->getName().c_str()));
}

void BottomBar::endTurn()
{
    if (boardGame->endTurn())
    {
        // Check if current player can upgrade any space
        bool currentPlayerCanUpgradeAnySpace = false;
        for(int i = 0; i < 40; i++)
            if (boardGame->getSpace(i)->typeIs(PropertyType) && myWindow->getCurrentPlayer()->canUpgrade((Property*)boardGame->getSpace(i)))
                currentPlayerCanUpgradeAnySpace = true;

        // Continue playing
        myWindow->updatePlayersProperties(1 - boardGame->getPlayerTurn());
        turnStatus->setText(QString("Turn of Player ") + QString::number(boardGame->getPlayerTurn() + 1));
        status->setText(QString("Roll the dice" + (currentPlayerCanUpgradeAnySpace ? QString(" or Upgrade") : QString(""))));

        monopolyBoard->resetCommunity();
        monopolyBoard->resetChance();

        rollButton->setEnabled(true);
        purchaseButton->setEnabled(false);
        endTurnButton->setEnabled(false);

        // This code is only relevant if the player is a computer
        if (myWindow->playerIsComputer(boardGame->getPlayerTurn())){
            if (currentPlayerCanUpgradeAnySpace){
                int propertyToUpgrade = myWindow->getCurrentPlayer()->decideUpgrade();
                if (propertyToUpgrade >= 0){
                    myWindow->getCurrentPlayer()->upgrade((Property*)boardGame->getSpace(propertyToUpgrade));
                    myWindow->playerPropertyWasUpgraded(boardGame->getPlayerTurn(), propertyToUpgrade);
                }
            }
            QTimer::singleShot(playSpeed, this, SLOT(rollDiceWithAnimation()));
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Game Over!");
        if (myWindow->getPlayer(0)->getMoney() > myWindow->getPlayer(1)->getMoney())
            messageBox.setText(QString("Player 1 is the winner!"));
        else if (myWindow->getPlayer(0)->getMoney() < myWindow->getPlayer(1)->getMoney())
            messageBox.setText(QString("Player 2 is the winner!"));
        else
            messageBox.setText(QString("It's a tie!"));
        messageBox.setStandardButtons(QMessageBox::NoButton);
        QPushButton* exitButton = new QPushButton("Exit");
        messageBox.addButton(exitButton, QMessageBox::AcceptRole);
        connect(exitButton, SIGNAL(clicked()), this, SLOT(exitApp()));
        messageBox.exec();
    }
}

void BottomBar::exitApp()
{
    myWindow->close();
}

#endif
