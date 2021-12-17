#ifdef USE_QT_LIB
#include "centralwidget.h"
#include<iostream>
#include<sstream>

using namespace std;

CentralWidget::CentralWidget(QString gamePieceNames[2]): QWidget()
{

    //setting up the chance and community chest images
    boardLabel = new QLabel( this ); //adding current widget to another widget
    boardLabel->setPixmap( QPixmap("data/board.png") );
    this->setGeometry(0, 0, 650, 650);

    //setting up the dice images
    dice1 = new QLabel(this);
    dice1->setPixmap(QPixmap("data/dice/dice1.png"));
    dice1->setGeometry(430, 370, 35, 35);
    dice1->setFixedWidth(35);
    dice1->setFixedHeight(35);
    dice1->setScaledContents(true);
    dice1->show();

    dice2 = new QLabel(this);
    dice2->setPixmap(QPixmap("data/dice/dice1.png"));
    dice2->setGeometry(470, 370, 35, 35);
    dice2->setFixedWidth(35);
    dice2->setFixedHeight(35);
    dice2->setScaledContents(true);
    dice2->show();


    //Create the covers for the card deck
    chanceCover = new QLabel(this);
    chanceCover->setPixmap(QPixmap("data/chance/chanceTemplate.jpg"));
    chanceCover->setGeometry(102, 102, 180, 100);
    chanceCover->setFixedWidth(180);
    chanceCover->setFixedHeight(100);
    chanceCover->setScaledContents(true);
    chanceCover->show();

    communityCover = new QLabel(this);
    communityCover->setPixmap(QPixmap("data/communitychest/communityTemplate.jpg"));
    communityCover->setGeometry(366, 442, 180, 100);
    communityCover->setFixedWidth(180);
    communityCover->setFixedHeight(100);
    communityCover->setScaledContents(true);
    communityCover->show();

    //setting up space locations on the board
    int x[40] = {594, 513, 462, 408, 356, 304, 252, 199, 145, 94, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
                 95, 146, 198, 250, 303, 356, 408, 460, 514, 594, 594, 594, 594, 594, 594, 594, 594, 594, 594
                };
    int y[40] = {590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 590, 511, 460, 408, 356, 303, 251, 198, 146,
                 93, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 93, 145, 197, 249, 302, 354, 407, 459, 511
                };
    for (int i = 0; i < 40; i++)
    {
        boardSpace[i].x = x[i];
        boardSpace[i].y = y[i];
    }

    //setting up Player Icons
    playerIcons = new QLabel*[2];

    for(int i = 0; i < 2; i++)
    {
        playerIcons[i] = new QLabel(this);
        playerIcons[i]->setPixmap(QPixmap(gamePieceNames[i]));

        Coordinates tempLocation;
        tempLocation.x = 594;
        tempLocation.y = 590;

        playerIcons[i]->setGeometry(tempLocation.x + (i*22), tempLocation.y, 25, 25);

        playerIcons[i]->setFixedWidth(25);
        playerIcons[i]->setFixedHeight(25);
        playerIcons[i]->setScaledContents(true);
        playerIcons[i]->show();
    }


}

string CentralWidget::intToString(int number)
{
    stringstream strs;
    strs << number;
    string output = strs.str();
    strs.clear();
    return output;
}

string CentralWidget::concatenateStrings(string first, string second, string third)
{
    return first + second + third;
}

void CentralWidget::movePieces(int playerNum, int spaceNum)
{
    Coordinates tempLocation = boardSpace[spaceNum];
    if(playerNum == 0)
    {
        playerIcons[playerNum]->setGeometry(tempLocation.x, tempLocation.y, 25, 25);
    }
    else if (playerNum == 1)
    {
        playerIcons[playerNum]->setGeometry(tempLocation.x + (22), tempLocation.y, 25, 25);
    }
}

void CentralWidget::changeDiceImg(int rollNum1, int rollNum2)
{
    dice1->setPixmap(QPixmap(concatenateStrings("data/dice/dice", intToString(rollNum1), ".png").c_str()));
    dice2->setPixmap(QPixmap(concatenateStrings("data/dice/dice", intToString(rollNum2), ".png").c_str()));
}

void CentralWidget::hidePiece(int playerNum)
{
    playerIcons[playerNum]->hide();
}

void CentralWidget::showCommunity(int cardNum)
{
    communityCover->hide();
    communityCards[cardNum]->show();
}

void CentralWidget::resetCommunity()
{
    for( int i = 0; i < 10; i++)
    {
        communityCards[i]->hide();
    }
    communityCover->show();
}

void CentralWidget::showChance(int cardNum)
{
    chanceCover->hide();
    chanceCards[cardNum]->show();
}

void CentralWidget::resetChance()
{
    for( int i = 0; i < 10; i++)
    {
        chanceCards[i]->hide();
    }
    chanceCover->show();

}

void CentralWidget::initializingCards()
{

    communityCards = new QLabel*[10];
    chanceCards = new QLabel*[10];


    for( int i = 0; i < 10; i++)
    {
        chanceCards[i] = new QLabel(this);
        chanceCards[i]->setPixmap(QPixmap(concatenateStrings("data/chance/chance", intToString(i), ".png").c_str()));
        chanceCards[i]->setGeometry(102, 102, 180, 100);
        chanceCards[i]->setFixedWidth(180);
        chanceCards[i]->setFixedHeight(100);
        chanceCards[i]->setScaledContents(true);
        chanceCards[i]->hide();
    }

    for( int i = 0; i < 10; i++)
    {
        communityCards[i] = new QLabel(this);
        communityCards[i]->setPixmap(QPixmap(concatenateStrings("data/communitychest/community", intToString(i), ".png").c_str()));
        communityCards[i]->setGeometry(366, 442, 180, 100);
        communityCards[i]->setFixedWidth(180);
        communityCards[i]->setFixedHeight(100);
        communityCards[i]->setScaledContents(true);
        communityCards[i]->hide();
    }

}

#endif
