#ifdef USE_QT_LIB
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "centralwidget.h"
#include "bottomBar.h"
#include "guiplayers.h"
#include <QPlainTextEdit>
#include "../player.h"
#include "../space.h"
#include "../boardgame.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    GUIPlayers* guiPlayers[2];
    CentralWidget* centralWidget;
    BottomBar* bottomBar;
    int totalPlayers;
    QString gamePieceNames[2];
    BoardGame* boardGame;
    Player** players;
    Bank* bank;
    Deck* community;
    Deck* chance;

public:
    MainWindow(BoardGame* boardGame, Player** players, Bank* bank, Deck* community, Deck* chance);
    void windowSetUp();
    void setPlayerLocation(int playerNum, int spaceNum);
    int getPlayerLocation(int playerNum);
    Player* getPlayer(int num);
    string getPlayerName(int playerNum);
    void updatePlayersMoney(int playerId = -1);
    void updatePlayersProperties(int playerId = -1);
    Player* getCurrentPlayer();

    Card* getNextCommunityCard();
    Card* getNextChanceCard();
    Bank* getBank();

    bool playerIsComputer(int playerId);
    void playerPropertyWasBought(int playerId, int propertyId);
    void playerPropertyWasUpgraded(int playerId, int propertyId);
};

#endif
#endif
