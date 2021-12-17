#ifdef USE_QT_LIB
#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QtGui>
#include <QDockWidget>
#include <QPushButton>
#include <QGridLayout>
#include "centralwidget.h"
#include "../bank.h"
#include "../boardgame.h"

class MainWindow;
class GUIPlayers;

class QSpinBoxWithoutTextEdit : public QSpinBox
{
    Q_OBJECT
public:
    QSpinBoxWithoutTextEdit(QWidget* parent = 0) : QSpinBox(parent)
    {
        lineEdit()->setReadOnly(true);
    }
};

class BottomBar : public QDockWidget
{
    Q_OBJECT

private:
    BoardGame* boardGame;
    int playSpeed; // in milliseconds

protected:
    QLabel* turnStatus;
    QLabel* status;
    QPushButton* rollButton;
    QPushButton* purchaseButton;
    QPushButton* endTurnButton;
    QGridLayout* layout;
    QWidget* bottomWidget;
    QGridLayout* computerSpeedLayout;
    QLabel* computerSpeedStatus;
    QSpinBox* computerSpeed;

    //storing reference pointers
    CentralWidget* monopolyBoard;
    MainWindow* myWindow;

private slots:
    //need to incorporate to make the buttons work

    void rollDice();
    void purchase();
    void endTurn();
    void rollDiceWithAnimation();
    void purchaseWithAnimation();
    void purchaseWithAnimationHelper();
    void endTurnWithAnimation();
    void exitApp();
    void changeComputerSpeed();

public:
    BottomBar(BoardGame* boardGame, CentralWidget* tempBoard, MainWindow* tempWindow);
    void setPlayers(int numberPlayers, GUIPlayers* tempPlayers[]);

    bool upgradeProperty(int propertyToUpgrade);

};

#endif
#endif
