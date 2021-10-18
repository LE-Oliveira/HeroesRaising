#include <QIcon>
#include <QDebug>
#include <math.h>

#include "build.h"
#include "points.h"
#include "character.h"

extern Character *character;
extern Build *build;

Points::Points(){
    setWindowTitle("Hero's Rise Profile");
    setWindowIcon(QIcon(":/icon/HerosRise.ico"));
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/profile.png")));
    setScene(scene);
    scene->setSceneRect(0,0,800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    name = new QGraphicsTextItem();
    lines(name, QString("Name: ") + character->getName(), Qt::black);
    name->setPos(100, 40);
    scene->addItem(name);

    lvl = new QGraphicsTextItem();
    lines(lvl, QString("Level: ") + QString::number(character->getLvl()), Qt::white);
    lvl->setPos(100, 90);
    scene->addItem(lvl);

    hp = new QGraphicsTextItem();
    lines(hp, QString("Hp: ") + QString::number(character->getHp()) + QString("/") + QString::number(character->getVit()*2+10), Qt::black);
    hp->setPos(100, 140);
    scene->addItem(hp);

    con = new QGraphicsTextItem();
    lines(con, QString("Constituition: ") + QString::number(character->getDef()), Qt::white);
    con->setPos(100, 190);
    scene->addItem(con);

    str = new QGraphicsTextItem();
    lines(str, QString("Strength: ") + QString::number(character->getAtk()), Qt::black);
    str->setPos(100, 240);
    scene->addItem(str);

    dex = new QGraphicsTextItem();
    lines(dex, QString("Dexterity: ") + QString::number(character->getDex()), Qt::white);
    dex->setPos(100, 290);
    scene->addItem(dex);

    luc = new QGraphicsTextItem();
    lines(luc, QString("Luck: ") + QString::number(character->getLuck()), Qt::black);
    luc->setPos(100, 340);
    scene->addItem(luc);

    vit = new QGraphicsTextItem();
    lines(vit, QString("Vitality: ") + QString::number(character->getVit()), Qt::white);
    vit->setPos(100, 390);
    scene->addItem(vit);

    xp = new QGraphicsTextItem();
    lines(xp, QString("Xp: ") + QString::number(character->getXp()) + "/" + QString::number((character->getLvl()*10+pow(5,character->getLvl()))*10), Qt::black);
    xp->setPos(100, 440);
    scene->addItem(xp);

    money = new QGraphicsTextItem();
    lines(money, QString("Money: ") + QString::number(character->getMoney()), Qt::white);
    money->setPos(100, 490);
    scene->addItem(money);

    quit = new Button("menu", "quit", QPoint(650,500), QPoint(0,0), QPoint(50,30), Qt::gray, true);
    scene->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(back()));
    if(character->getUpgrades()>0){
        next = new Button("menu", "upgrade", QPoint(530,100), QPoint(0,0), QPoint(50,30), Qt::darkGray, true);
        scene->addItem(next);
        connect(next, SIGNAL(clicked()), this, SLOT(upgrade()));
    }
}

void Points::lines(QGraphicsTextItem* title, QString string, QColor color){
    title->setPlainText(string);
    title->setDefaultTextColor(color);
    title->setFont(QFont("Gabriola", 30));
}

void Points::back(){
    this->close();
    build->getMainMenu()->show();
}

void Points::upgrade(){
    name->hide();
    lvl->hide();
    hp->hide();
    xp->hide();
    money->hide();
    quit->hide();
    next->hide();
    upgrades = new QGraphicsTextItem();
    lines(upgrades, QString("Remaining Points: ") + QString::number(character->getUpgrades()), Qt::white);
    upgrades->setPos(67, 140);
    scene->addItem(upgrades);
    confirm = new Button("confirm", "confirm", QPoint(600,500), QPoint(0,0), QPoint(70,50), Qt::green,true);
    scene->addItem(confirm);
    connect(confirm, SIGNAL(clicked()), this, SLOT(conf()));
    pC = new Button("build", "+", QPoint(300, 220), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(pC);
    connect(pC, SIGNAL(clicked()), this, SLOT(pCons()));
    pS = new Button("build", "+", QPoint(300, 270), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(pS);
    connect(pS, SIGNAL(clicked()), this, SLOT(pStr()));
    pD = new Button("build", "+", QPoint(300, 320), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(pD);
    connect(pD, SIGNAL(clicked()), this, SLOT(pDex()));
    pL = new Button("build", "+", QPoint(300, 370), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(pL);
    connect(pL, SIGNAL(clicked()), this, SLOT(pLuck()));
    pV = new Button("build", "+", QPoint(300, 420), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(pV);
    connect(pV, SIGNAL(clicked()), this, SLOT(pVit()));
    lC = new Button("build", "-", QPoint(75, 220), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(lC);
    connect(lC, SIGNAL(clicked()), this, SLOT(lCons()));
    lS = new Button("build", "-", QPoint(75, 270), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(lS);
    connect(lS, SIGNAL(clicked()), this, SLOT(lStr()));
    lD = new Button("build", "-", QPoint(75, 320), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(lD);
    connect(lD, SIGNAL(clicked()), this, SLOT(lDex()));
    lL = new Button("build", "-", QPoint(75, 370), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(lL);
    connect(lL, SIGNAL(clicked()), this, SLOT(lLuck()));
    lV = new Button("build", "-", QPoint(75, 420), QPoint(0,0), QPoint(20,20), Qt::lightGray, true);
    scene->addItem(lV);
    connect(lV, SIGNAL(clicked()), this, SLOT(lVit()));
}

void Points::conf(){
    //character->setHp(10+2*character->getVit());
    close();
    this->close();
    build->getMainMenu()->show();
}

void Points::pCons(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addDef(1);
    character->addUpgrade(-1);
    con->hide();
    con->setPlainText("Constitution: " + QString::number(character->getDef()));
    con->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
}

void Points::pStr(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addAtk(1);
    character->addUpgrade(-1);
    str->hide();
    str->setPlainText("Strength: " + QString::number(character->getAtk()));
    str->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
}

void Points::pDex(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addDex(1);
    character->addUpgrade(-1);
    dex->hide();
    dex->setPlainText("Dexterity: " + QString::number(character->getDex()));
    dex->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
}

void Points::pLuck(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addLuck(1);
    character->addUpgrade(-1);
    luc->hide();
    luc->setPlainText("Luck: " + QString::number(character->getLuck()));
    luc->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
}

void Points::pVit(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addVit(1);
    character->addUpgrade(-1);
    vit->hide();
    vit->setPlainText("Vitality: " + QString::number(character->getVit()));
    vit->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    character->addHp(2);
}

void Points::lCons(){
    if(character->getDef()<=1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addDef(-1);
    character->addUpgrade(1);
    con->hide();
    con->setPlainText("Constitution: " + QString::number(character->getDef()));
    con->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
}

void Points::lStr(){
    if(character->getAtk() <= 1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addAtk(-1);
    character->addUpgrade(1);
    str->hide();
    str->setPlainText("Strength: " + QString::number(character->getAtk()));
    str->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
}

void Points::lDex(){
    if(character->getDex() <= 1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addDex(-1);
    character->addUpgrade(1);
    dex->hide();
    dex->setPlainText("Dexterity: " + QString::number(character->getDex()));
    dex->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
}

void Points::lLuck(){
    if(character->getLuck() <= 1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addLuck(-1);
    character->addUpgrade(1);
    luc->hide();
    luc->setPlainText("Luck: " + QString::number(character->getLuck()));
    luc->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
}

void Points::lVit(){
    if(character->getVit() <= 1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addVit(-1);
    character->addUpgrade(1);
    vit->hide();
    vit->setPlainText("Vitality: " + QString::number(character->getVit()));
    vit->show();
    upgrades->hide();
    upgrades->setPlainText("Remaining Points: " + QString::number(character->getUpgrades()));
    upgrades->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    if(character->getHp()>1) character->addHp(-2);
}

