#ifdef USE_QT_LIB
#ifndef GUIPLAYERS_H
#define GUIPLAYERS_H

#include "../player.h"
#include <QtGui>
#include <QDockWidget>
#include <string>
#include <sstream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../space.h"
#include "../bank.h"
#include <QtCore/QSignalMapper>
#include "bottomBar.h"

class BottomBar;

class CRightClickEnabler : public QObject
{
    Q_OBJECT
public:
    CRightClickEnabler(QAbstractButton * button): QObject(button), _button(button)
    {
        button->installEventFilter(this);
    };

signals:
    void rightClick();

protected:
    inline bool eventFilter(QObject *watched, QEvent *event)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = (QMouseEvent*)event;
            if (mouseEvent->button() == Qt::RightButton)
                emit rightClick();
        }
        return false;
    }

private:
    QAbstractButton* _button;
};

class GUIPlayers : public QDockWidget
{
    Q_OBJECT

protected:
    Player* player;
    QLabel *numLabel;
    QLabel *moneyLabel;
    QGridLayout* layout;
    QWidget* sideBar;
    QLabel* gamePieceImg;
    QPushButton** ownedProperties;
    int housesOfProperty[40];
    int currentPropertyNum;
    BottomBar* bottomBar;

private slots:
    void showSpace();
    void upgradeSpace();

public:
    GUIPlayers(Player* p, QString gamePieceName);
    GUIPlayers();
    void setBottomBar(BottomBar* bottomBar);
    void setMoneyText();
    void propertyWasUpgraded(int property);
    void updateProperties();

    void enableUpgrade();
    void disableUpgrade();

};

#endif
#endif
