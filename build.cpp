#include <QMediaPlayer>
#include <QIcon>
#include <QString>

#include "build.h"
#include "button.h"
#include "character.h"
#include "points.h"

extern Character *character;

Build::Build(QWidget *parent){
    setWindowTitle("Hero's Rise");
    setWindowIcon(QIcon(":/icon/HerosRise.ico"));
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/profile.png")));
    scene->setSceneRect(0,0,800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);
    music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/soundtrack/build.mp3"));
    music->setVolume(25);
    music->play();
    character = new Character();
    intro = new QGraphicsTextItem();
    lines(intro, "Please build up your character", Qt::black);
    intro->setPos(20,20);
    scene->addItem(intro);
    points = new QGraphicsTextItem();
    lines(points, "You still have " + QString::number(character->getUpgrades()) + " points left", Qt::white);
    points->setPos(30, 70);
    scene->addItem(points);
    name = new QGraphicsTextItem();
    lines(name, "Name:", Qt::black);
    name->setPos(30,120);
    scene->addItem(name);
    nameEntry = new QLineEdit();
    nameEntry->setMaxLength(10);
    scene->addWidget(nameEntry);
    nameEntry->move(115,155);
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
    c = new QGraphicsTextItem();
    lines(c, QString("Constituition: ") + QString::number(character->getDef()), Qt::white);
    c->setPos(100, 190);
    scene->addItem(c);
    s = new QGraphicsTextItem();
    lines(s, QString("Strength: ") + QString::number(character->getAtk()), Qt::black);
    s->setPos(100, 240);
    scene->addItem(s);
    d = new QGraphicsTextItem();
    lines(d, QString("Dexterity: ") + QString::number(character->getDex()), Qt::white);
    d->setPos(100, 290);
    scene->addItem(d);
    l = new QGraphicsTextItem();
    lines(l, QString("Luck: ") + QString::number(character->getLuck()), Qt::black);
    l->setPos(100, 340);
    scene->addItem(l);
    v = new QGraphicsTextItem();
    lines(v, QString("Vitality: ") + QString::number(character->getVit()), Qt::white);
    v->setPos(100, 390);
    scene->addItem(v);
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
    setScene(scene);
    confirm = new Button("menu", "Confirm", QPoint(630, 520), QPoint(0,0), QPoint(80,30), Qt::gray, true);
    scene->addItem(confirm);
    connect(confirm, SIGNAL(clicked()), this, SLOT(conf()));
}

void Build::lines(QGraphicsTextItem* title, QString string, QColor color){
    title->setPlainText(string);
    title->setDefaultTextColor(color);
    title->setFont(QFont("Gabriola", 30));
}

void Build::atualizaPoints(){
    scene->removeItem(points);
    points = new QGraphicsTextItem();
    lines(points, "You still have " + QString::number(character->getUpgrades()) + " points left", Qt::white);
    points->setPos(30,70);
    scene->addItem(points);
}

void Build::pCons(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addDef(1);
    character->addUpgrade(-1);
    int cons = character->getDef();
    c->hide();
    c->setPlainText("Constitution: " + QString::number(cons));
    c->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::pStr(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addAtk(1);
    character->addUpgrade(-1);
    int str = character->getAtk();
    s->hide();
    s->setPlainText("Strength: " + QString::number(str));
    s->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::pDex(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addDex(1);
    character->addUpgrade(-1);
    int dex = character->getDex();
    d->hide();
    d->setPlainText("Dexterity: " + QString::number(dex));
    d->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::pLuck(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addLuck(1);
    character->addUpgrade(-1);
    int luck = character->getLuck();
    l->hide();
    l->setPlainText("Luck: " + QString::number(luck));
    l->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::pVit(){
    if(character->getUpgrades()<=0){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addVit(1);
    character->addUpgrade(-1);
    int vit = character->getVit();
    v->hide();
    v->setPlainText("Vitality: " + QString::number(vit));
    v->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::lCons(){
    if(character->getUpgrades()>=10||character->getDef()<=1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addDef(-1);
    character->addUpgrade(1);
    int cons = character->getDef();
    c->hide();
    c->setPlainText("Constitution: " + QString::number(cons));
    c->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::lStr(){
    if(character->getUpgrades()>=10||character->getAtk() <= 1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addAtk(-1);
    character->addUpgrade(1);
    int str = character->getAtk();
    s->hide();
    s->setPlainText("Strength: " + QString::number(str));
    s->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::lDex(){
    if(character->getUpgrades()>=10||character->getDex() <= 1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addDex(-1);
    character->addUpgrade(1);
    int dex = character->getDex();
    d->hide();
    d->setPlainText("Dexterity: " + QString::number(dex));
    d->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::lLuck(){
    if(character->getUpgrades()>=10||character->getLuck() <= 1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addLuck(-1);
    character->addUpgrade(1);
    int luck = character->getLuck();
    l->hide();
    l->setPlainText("Luck: " + QString::number(luck));
    l->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::lVit(){
    if(character->getUpgrades()>=10||character->getVit() <= 1){
        QMediaPlayer *sfx = new QMediaPlayer();
        sfx->setMedia(QUrl("qrc:/sfx/nop.mp3"));
        sfx->play();
        return;
    }
    character->addVit(-1);
    character->addUpgrade(1);
    int vit = character->getVit();
    v->hide();
    v->setPlainText("Vitality: " + QString::number(vit));
    v->show();
    QMediaPlayer *sfx = new QMediaPlayer();
    sfx->setMedia(QUrl("qrc:/sfx/stat.mp3"));
    sfx->play();
    atualizaPoints();
}

void Build::conf(){
    if(nameEntry->text() == "") return;
    character->setHp(10+2*character->getVit());
    music->stop();
    QString aux = nameEntry->text();
    QString aux2;
    int a = aux.size();
    if(a>10) a = 10;
    for(int i =0; i<a; i++) aux2.push_back(aux.at(i));
    character->setName(aux2);
    close();
    mm = new MainMenu();
    mm->show();
}
