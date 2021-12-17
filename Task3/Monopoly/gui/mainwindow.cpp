#ifdef USE_QT_LIB

#include<iostream>
#include "mainwindow.h"

using namespace std;

/**************     Primary constructor     ***************/
MainWindow::MainWindow(BoardGame* boardGame, Player** players, Bank* bank)
{
    this->boardGame = boardGame;
    this->players = players;
    this->bank = bank;

    setFixedSize(1200, 691);

    gamePieceNames[0] = QString("data/hat.png");
    gamePieceNames[1] = QString("data/dog.png");
}

/***********     Setting up the entire window     ************/
void MainWindow::windowSetUp()
{
    //Displaying GUIPlayers
    for(int i = 0; i < 2; i++)
    {
        guiPlayers[i] = new GUIPlayers(players[i], gamePieceNames[i]);
        guiPlayers[i]->setFeatures(QDockWidget::NoDockWidgetFeatures);
        guiPlayers[i]->setTitleBarWidget(new QWidget());
    }

    addDockWidget( Qt::LeftDockWidgetArea, guiPlayers[0]);
    addDockWidget( Qt::RightDockWidgetArea, guiPlayers[1]);

    //Displaying the board in the central widget
    centralWidget = new CentralWidget(gamePieceNames);
    setCentralWidget( centralWidget );

    //Displaying the Bottom Button bar
    bottomBar = new BottomBar(boardGame, centralWidget, this);

    bottomBar->setFeatures(QDockWidget::NoDockWidgetFeatures);
    bottomBar->setTitleBarWidget(new QWidget());
    addDockWidget( Qt::BottomDockWidgetArea, bottomBar );

    for(int i = 0; i < 2; i++)
    {
        guiPlayers[i]->setBottomBar(bottomBar);
    }

    //Create numPlayers of QLabels in central widget,
    //save images, and display the players on the board
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            qApp->desktop()->availableGeometry()
        )
    );


}


/************     Rest of Regular Functions     ************/

void MainWindow::setPlayerLocation(int playerNum, int spaceNum)
{
    centralWidget->movePieces(playerNum, spaceNum);
}

int MainWindow::getPlayerLocation(int playerNum)
{
    return players[playerNum]->getLocation();
}

Player* MainWindow::getPlayer(int num)
{
    return players[num];
}

string MainWindow::getPlayerName(int playerNum)
{
    return players[playerNum]->getName();
}

Player* MainWindow::getCurrentPlayer()
{
    return players[boardGame->getPlayerTurn()];
}

void MainWindow::updatePlayersMoney(int playerId /* = -1 */)
{
    if (playerId >= 0)
        guiPlayers[playerId]->setMoneyText();
    else{
        guiPlayers[0]->setMoneyText();
        guiPlayers[1]->setMoneyText();
    }
}

void MainWindow::updatePlayersProperties(int playerId /* = -1 */)
{
    if (playerId >= 0)
        guiPlayers[playerId]->updateProperties();
    else{
        guiPlayers[0]->updateProperties();
        guiPlayers[1]->updateProperties();
    }
}

bool MainWindow::playerIsComputer(int playerId){
    return true;
}

void MainWindow::playerPropertyWasBought(int playerId, int propertyId)
{
    guiPlayers[playerId]->updateProperties();
    guiPlayers[playerId]->setMoneyText();
}

void MainWindow::playerPropertyWasUpgraded(int playerId, int propertyId)
{
    guiPlayers[playerId]->propertyWasUpgraded(propertyId);
    guiPlayers[playerId]->updateProperties();
    guiPlayers[playerId]->setMoneyText();
}

Bank* MainWindow::getBank(){
    return bank;
}

#endif
