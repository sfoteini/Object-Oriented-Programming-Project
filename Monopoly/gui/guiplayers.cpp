#ifdef USE_QT_LIB
#include <iostream>
#include "guiplayers.h"

GUIPlayers::GUIPlayers(Player* p, QString gamePieceName)
{

    player = p;
    ownedProperties = new QPushButton*[40];
    for(int i = 0; i < 40; i++)
    {
        housesOfProperty[i] = 0;
        ownedProperties[i] = NULL;
    }

    //player's number
    QString qNum = QString::fromStdString(p->getName());
    numLabel = new QLabel( this );
    numLabel->setText( qNum );
    numLabel->setAlignment(Qt::AlignHCenter);

    //player's money
    QString qMoney = QString::number(player->getMoney()).insert(0, '$');
    moneyLabel = new QLabel( this );
    moneyLabel->setText( qMoney );
    moneyLabel->setAlignment(Qt::AlignRight);

    //player's game piece
    gamePieceImg = new QLabel(this);
    gamePieceImg->setPixmap(gamePieceName);
    gamePieceImg->setFixedWidth(55);
    gamePieceImg->setFixedHeight(50);
    gamePieceImg->setScaledContents(true);

    //Adding all parts to layout
    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget(gamePieceImg, 0, Qt::AlignCenter | Qt::AlignLeft);
    hlayout->addWidget(numLabel, 0, Qt::AlignCenter);
    hlayout->addWidget(moneyLabel, 0, Qt::AlignCenter | Qt::AlignRight);
    layout = new QGridLayout;
    layout->addLayout(hlayout, 0, 0, 1, 4);
    layout->setAlignment(Qt::AlignTop);

    sideBar = new QWidget(this);
    sideBar->setLayout(layout);
    setWidget(sideBar);

    this->setMinimumSize(QSize(270, 650));
    this->setMaximumSize(QSize(270, 650));
}

void GUIPlayers::setBottomBar(BottomBar* bottomBar)
{
    this->bottomBar = bottomBar;
}

GUIPlayers::GUIPlayers()
{

}

void GUIPlayers::setMoneyText()
{
    QString qMoney = QString::number(player->getMoney()).insert(0, '$');
    moneyLabel->setText( qMoney );
}

void GUIPlayers::propertyWasUpgraded(int property){
    housesOfProperty[property]++;
}

void GUIPlayers::updateProperties()
{
    for(int i = 0; i < 40; i++)
    {
        // if property belongs to player
        if (player->ownsProperty(i))
        {
            QString imagePath = QString("data/smallcards/smallcard") + QString::number(i) + QString("_") + QString::number(housesOfProperty[i]) + QString(".png");
            QPixmap pixmap(imagePath);
            QIcon buttonIcon(pixmap);
            if (ownedProperties[i] == NULL)
            {
                // if widget does not exist
                ownedProperties[i] = new QPushButton(gamePieceImg);
                ownedProperties[i]->setIcon(buttonIcon);
                ownedProperties[i]->setIconSize(pixmap.rect().size());
                ownedProperties[i]->setMinimumSize(pixmap.rect().size());
                ownedProperties[i]->setMaximumSize(pixmap.rect().size());
                connect(ownedProperties[i], SIGNAL(clicked()), this, SLOT(upgradeSpace()) );
                connect(new CRightClickEnabler(ownedProperties[i]), SIGNAL(rightClick()), this, SLOT(showSpace()) );
            }
            else
            {
                // if widget exists
                ownedProperties[i]->setIcon(buttonIcon);
                ownedProperties[i]->setIconSize(pixmap.rect().size());
                layout->removeWidget(ownedProperties[i]);
            }
            ownedProperties[i]->setEnabled(true);
        }
    }
    // Add buttons to grid
    int c = 0;
    int indexes[40] = {1, 3, 6, 8, 9, 11, 13, 14, 16, 18, 19, 21, // properties
                       23, 24, 26, 27, 29, 31, 32, 34, 37, 39, // properties
                       5, 15, 25, 35, // railroads
                       12, 28, // utilities
                       0, 2, 4, 7, 10, 17, 20, 22, 30, 33, 36, 38}; // other
    for(int i = 0; i < 40; i++)
    {
        int j = indexes[i];
        if (player->ownsProperty(j))
        {
            layout->addWidget(ownedProperties[j], int(c / 4) + 2, c % 4);
            c++;
        }
    }
}

void GUIPlayers::enableUpgrade()
{
    for(int i = 0; i < 40; i++)
    {
        if (ownedProperties[i] != NULL)
        {
            ownedProperties[i]->setEnabled(true);
        }

    }
}

void GUIPlayers::disableUpgrade()
{
    for(int i = 0; i < 40; i++)
    {
        if (ownedProperties[i] != NULL)
        {
            ownedProperties[i]->setEnabled(false);
        }

    }
}

void GUIPlayers::showSpace()
{
    QPushButton* button = (QPushButton*)(sender()->parent());
    int spaceId = -1;
    for(int i = 0; i < 40; i++)
    {
        if (button == ownedProperties[i])
            spaceId = i;
    }

    QMessageBox messageBox;
    QString imagePath = QString("data/cards/card") + QString::number(spaceId) + QString(".png");
    QPixmap pixmap(imagePath);
    messageBox.setIconPixmap(pixmap);
    messageBox.setContentsMargins(13, 0, 0, 0);
    messageBox.setWindowTitle("Card Info");
    messageBox.setStandardButtons(QMessageBox::Close);
    messageBox.setMinimumSize(pixmap.rect().size());
    messageBox.setMaximumSize(pixmap.rect().size());
    messageBox.exec();
}

void GUIPlayers::upgradeSpace()
{
    QPushButton *button = (QPushButton *)sender();
    int spaceId = -1;
    for(int i = 0; i < 40; i++)
    {
        if (button == ownedProperties[i])
            spaceId = i;
    }
    if (bottomBar->upgradeProperty(spaceId)){
        housesOfProperty[spaceId]++;
        updateProperties();
        setMoneyText();
    }
}

#endif
