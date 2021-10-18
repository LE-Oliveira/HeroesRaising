#include <QIcon>
#include <QGraphicsTextItem>
#include <QTimer>
#include <math.h>
#include <QMediaPlaylist>

#include "rest.h"
#include "character.h"
#include "start.h"

extern Character *character;
extern Build * build;

Rest::Rest(){
    setWindowTitle("Hero's Rise Inn");
    setWindowIcon(QIcon(":/icon/HerosRise.ico"));
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/inn2d.jpg").scaled(800, 600)));
    setScene(scene);
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/soundtrack/healing.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    song = new QMediaPlayer();
    song->setMedia(playlist);//song->setMedia(QUrl("qrc:/soundtrack/healing.mp3"));
    song->play();
    hp = new QGraphicsTextItem();
    hp->setDefaultTextColor(Qt::green);
    hp->setFont(QFont("times", 16));
    hp->setPos(30,0);
    if(character->getHp() == (character->getVit()*2+10)){
        hp->setPlainText((QString("Oh, your health is perfect!! Came back when you have injuries")));
        t = new QTimer();
        t->setSingleShot(true);
        connect(t, &QTimer::timeout, this, &Rest::back);
        t->start(4000);
    }
    else{
        hp->setPlainText(QString(character->getName() + "'s Hp: ") + QString::number(character->getHp()) + QString("/") + QString::number(character->getVit()*2+10));
        sentence = new QGraphicsTextItem();
        sentence->setDefaultTextColor(Qt::white);
        sentence->setFont(QFont("times", 16));
        sentence->setPlainText("Ouch, it seems that you are hurt\nWe have the best and confiest bedrooms over the region\nDo you wish to rest for a while in the Sweet Dreams Inn?");
        sentence->setPos(30, 30);
        scene->addItem(sentence);
        y = new Button("choice", "Yes", QPoint(100, 150), QPoint(0,0), QPoint(270,30), QColor(Qt::yellow), true);
        connect(y, SIGNAL(clicked()), this, SLOT(yes()));
        scene->addItem(y);
        n = new Button("choice", "No", QPoint(370, 150), QPoint(0,0), QPoint(270,30), QColor(Qt::yellow), true);
        connect(n, SIGNAL(clicked()), this, SLOT(no()));
        scene->addItem(n);
    }
    scene->addItem(hp);
}

void Rest::back(){
    this->close();
    t->~QTimer();
    song->stop();
    build->getMainMenu()->show();
    build->getMainMenu()->setWent(true);
}

void Rest::no(){
    for(int i = 0; i < scene->items().size(); i ++) if(typeid(*(scene->items().at(i))) == typeid(Button)) scene->items().at(i)->hide();
    sentence->hide();
    sentence->setPlainText("Okay, good luck out there");
    sentence->show();
    t = new QTimer();
    t->setSingleShot(true);
    connect(t, &QTimer::timeout, this, &Rest::back);
    t->start(3000);
}

void Rest::yes(){
    scene->removeItem(n);
    y->hide();
    n->hide();
    sentence->hide();
    money = new QGraphicsTextItem();
    money->setDefaultTextColor(Qt::yellow);
    money->setFont(QFont("times", 16));
    money->setPlainText(QString(character->getName() + "'s money:") + QString::number(character->getMoney()));
    money->setPos(550, 0);
    scene->addItem(money);
    sentence->setPlainText("We have 3 options of services");
    standard = new Button("menu", "Standard\nCosts 5 coins and heals 25% of life", QPoint(300, 300), QPoint(0,0), QPoint(200,50), Qt::gray, true);
    scene->addItem(standard);
    connect(standard, SIGNAL(clicked()), this, SLOT(healStandard()));
    advanced = new Button("menu", "Advanced\nCosts 9 coins and heals 50% of life", QPoint(300, 350), QPoint(0,0), QPoint(200,50), Qt::gray, true);
    scene->addItem(advanced);
    connect(advanced, SIGNAL(clicked()), this, SLOT(healAdvanced()));
    complete= new Button("menu", "Complete\nCosts 17 coins and heals 100% of life", QPoint(300, 400), QPoint(0,0), QPoint(200,50), Qt::gray, true);
    scene->addItem(complete);
    connect(complete, SIGNAL(clicked()), this, SLOT(healComplete()));
    n = new Button("menu", "Never mind. I've changed my mind", QPoint(300, 450), QPoint(0,0), QPoint(200,50), QColor(Qt::gray), true);
    connect(n, SIGNAL(clicked()), this, SLOT(no()));
    n->show();
    sentence->show();
    scene->addItem(n);
}

void Rest::notEnoughMoney(){
    for(int i = 0; i < scene->items().size(); i ++) if(typeid(*(scene->items().at(i))) == typeid(Button)) scene->items().at(i)->hide();
    sentence->hide();
    sentence->setPlainText("You have not enough money... You'd better sell some items to the store.\nCome back when you have aquired some money");
    sentence->show();
    t = new QTimer();
    t->setSingleShot(true);
    connect(t, &QTimer::timeout, this, &Rest::back);
    t->start(3000);
}

void Rest::hpUp(){
    QGraphicsTextItem* action = new QGraphicsTextItem();
    if(still <= 0){
        t->stop();
        scene->removeItem(action);
        action->~QGraphicsTextItem();
        sentence->hide();
        sentence->setPlainText("After a rest you feel a bit better");
        sentence->show();
        t->setSingleShot(true);
        connect(t, &QTimer::timeout, this, &Rest::back);
        t->start(3000);
        return;
    }
    character->setHp(character->getHp() + 1);
    scene->removeItem(hp);
    hp->setPlainText(QString(character->getName() + "'s Hp: ") + QString::number(character->getHp()) + QString("/") + QString::number(character->getVit()*2+10));
    scene->addItem(hp);
    action->setPlainText("Resting");
    scene->addItem(action);
    action->show();
    still--;
}

void Rest::healStandard(){
    int chance;
    advanced->hide();
    standard->hide();
    n->hide();
    complete->hide();
    if(build->getMainMenu()->getWent()) chance = 0;
    else chance = rand() % (20) + character->getLuck();
    int Hp = character->getHp(), vit = character->getVit();
    if (Hp + ceil(0.25 * (10 + 2 * vit)) > 10 + 2 * vit) still = 10 + 2 * vit - Hp;
    else still = ceil(0.25 * (10 + 2 * vit));
    if(chance>19){
        sentence->hide();
        sentence->setPlainText("You know what? Take a free trial. No fees for ya\nResting");
        sentence->show();
        t = new QTimer();
        connect(t, &QTimer::timeout, this, &Rest::hpUp);
        t->start(300);
    }
    else if(character->getMoney() >= 5){
        sentence->hide();
        sentence->setPlainText("Resting");
        sentence->show();
        character->addMoney(-5);
        money->hide();
        money->setPlainText(QString(character->getName() + "'s money:") + QString::number(character->getMoney()));
        money->show();
        t = new QTimer();
        connect(t, &QTimer::timeout, this, &Rest::hpUp);
        t->start(300);
    }
    else return notEnoughMoney();
}

void Rest::healAdvanced(){
    int chance;
    advanced->hide();
    standard->hide();
    n->hide();
    complete->hide();
    if(build->getMainMenu()->getWent()) chance = 0;
    else chance = rand() % (20) + character->getLuck();
    int Hp = character->getHp(), vit = character->getVit();
    if (Hp + ceil(0.5 * (10 + 2 * vit)) > 10 + 2 * vit) still = 10 + 2 * vit - Hp;
    else still = ceil(0.5 * (10 + 2 * vit));
    if(chance>19){
        sentence->hide();
        sentence->setPlainText("You know what? Take a free trial. No fees for ya");
        sentence->show();
        t = new QTimer();
        connect(t, &QTimer::timeout, this, &Rest::hpUp);
        t->start(300);
    }
    else if(character->getMoney() >= 9){
        sentence->hide();
        sentence->setPlainText("Resting");
        sentence->show();
        character->addMoney(-9);
        money->hide();
        money->setPlainText(QString(character->getName() + "'s money:") + QString::number(character->getMoney()));
        money->show();
        t = new QTimer();
        connect(t, &QTimer::timeout, this, &Rest::hpUp);
        t->start(300);
    }
    else return notEnoughMoney();
}

void Rest::healComplete(){
    int chance;
    advanced->hide();
    standard->hide();
    n->hide();
    complete->hide();
    if(build->getMainMenu()->getWent()) chance = 0;
    else chance = rand() % (20) + character->getLuck();
    int Hp = character->getHp(), vit = character->getVit();
    still = vit*2 + 10 - Hp;
    if(chance>19){
        sentence->hide();
        sentence->setPlainText("You know what? Take a free trial. No fees for ya");
        sentence->show();
        t = new QTimer();
        connect(t, &QTimer::timeout, this, &Rest::hpUp);
        t->start(300);
    }
    else if(character->getMoney() >= 17){
        sentence->hide();
        sentence->setPlainText("Resting");
        sentence->show();
        character->addMoney(-17);
        money->hide();
        money->setPlainText(QString(character->getName() + "'s money:") + QString::number(character->getMoney()));
        money->show();
        t = new QTimer();
        connect(t, &QTimer::timeout, this, &Rest::hpUp);
        t->start(300);
    }
    else return notEnoughMoney();
}
