#ifdef USE_QT_LIB
#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QtGui>

using namespace std;

struct Coordinates
{
    int x;
    int y;
};

class CentralWidget: public QWidget
{
    Q_OBJECT

private:
    QLabel* chanceCover;
    QLabel* communityCover;
    QLabel* boardLabel;
    QLabel* dice1;
    QLabel* dice2;
    QLabel** playerIcons;
    int numPlayers;
    QLabel** communityCards;
    QLabel** chanceCards;
    Coordinates boardSpace[40];

private:
    string intToString(int number);
    string concatenateStrings(string first, string second, string third);

public:
    CentralWidget(QString gamePieceNames[2]);
    void changeDiceImg(int rollNum1, int rollNum2);
    void movePieces(int playerNum, int spaceNum);
    void hidePiece(int playerNum);
    void showCommunity(int cardNum);
    void resetCommunity();
    void showChance(int cardNum);
    void resetChance();
    void initializingCards();

};

#endif
#endif
