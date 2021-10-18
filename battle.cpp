#include <QIcon>
#include <math.h>

#include "build.h"
#include "battle.h"
#include "character.h"
#include "button.h"

extern Character *character;
extern Build *build;

Battle::Battle(){
    scene = new QGraphicsScene();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowTitle("Hero's Rise Battle");
    setWindowIcon(QIcon(":/icon/HerosRise.ico"));
    setScene(scene);
    if(character->getHp()<=0){
        scene->setSceneRect(0,0,800,600);
        setFixedSize(800,600);
        scene->setBackgroundBrush(QBrush(QPixmap(":/background/fallen.jpg").scaled(800, 600)));
        winLose = new QGraphicsTextItem();
        winLose->setPlainText("Take a rest before fighting, you're barely alive!!!");
        soundtrack = new QMediaPlayer(this);
        soundtrack->setMedia(QUrl("qrc:/sfx/deadUR.mp3"));
        soundtrack->play();
        winLose->setPos(0,0);
        winLose->setDefaultTextColor(Qt::white);
        winLose->setScale(2);
        scene->addItem(winLose);
        winLose->show();
        start = new QTimer();
        connect(start, &QTimer::timeout, this, &Battle::back);
        start->start(5000);
    }
    else{
        scene->setSceneRect(0,0,1366,768);
        setFixedSize(1366,768);
        scene->setBackgroundBrush(QBrush(QPixmap(":/background/forest.jpg").scaled(1360, 780)));
        melee = new Button("menu", "Melee Attack", QPoint(0,0), QPoint(0,0), QPoint(100, 50), Qt::gray, true);
        scene->addItem(melee);
        connect(melee, SIGNAL(clicked()), this, SLOT(meleeAttack()));
        ranged = new Button("menu", "Ranged Attack", QPoint(100,0), QPoint(0,0), QPoint(100, 50), Qt::gray, true);
        scene->addItem(ranged);
        connect(ranged, SIGNAL(clicked()), this, SLOT(rangedAttack()));
        defend = new Button("menu", "Defend", QPoint(200,0), QPoint(0,0), QPoint(100, 50), Qt::gray, true);
        scene->addItem(defend);
        connect(defend, SIGNAL(clicked()), this, SLOT(defense()));
        runAway = new Button("menu", "Run Away", QPoint(300,0), QPoint(0,0), QPoint(100, 50), Qt::gray, true);
        scene->addItem(runAway);
        connect(runAway, SIGNAL(clicked()), this, SLOT(run()));
        int being = rand() % (character->getLvl()+1) +1;
        cSprite = new QTimer();
        connect(cSprite, &QTimer::timeout, character, &Character::change);
        cSprite->start(125);
        damageCount = new QGraphicsTextItem();
        scene->addItem(damageCount);
        damageCount->hide();
        hp = new QGraphicsTextItem();
        hp->setPlainText(QString::number(character->getHp())+ "/" + QString::number(character->getVit()*2+10));
        hp->setScale(3);
        hp->setDefaultTextColor(Qt::green);
        hp->setPos(100,500);
        scene->addItem(hp);
        damageCount->setScale(3);
        QMediaPlaylist *playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl("qrc:/soundtrack/battleTheme.mp3"));
        character->setPos(100, 550);
        scene->addItem(character);
        character->show();
        if(being == 1){
            enemy = new Beast("wolf");
            enemy->setPos(1000,540);
        }
        else if(being == 2){
            enemy = new Beast("goblin");
            enemy->setPos(1000,540);
        }
        else if(being == 3){
            enemy = new Beast("flameskull");
            enemy->setPos(1000,520);
        }
        else if(being == 4){
            enemy = new Beast("hydra");
            enemy->setPos(1000,450);
        }
        else if(being == 5){
            enemy = new Beast("beholder");
            enemy->setPos(1000,300);
        }
        else if(being == 6){
            enemy = new Beast("boss");
            enemy->setPos(900,300);
            playlist->clear();
            playlist->addMedia(QUrl("qrc:/soundtrack/bossTheme.mp3"));
            scene->setBackgroundBrush(QBrush(QPixmap(":/background/boss.png").scaled(1360, 780)));
            character->setPos(200, 600);
            hp->setPos(200,550);
        }
        scene->addItem(enemy);
        enemy->show();
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        soundtrack = new QMediaPlayer(this);
        soundtrack->setPlaylist(playlist);
        soundtrack->setVolume(20);
        soundtrack->play();
        if(character->getDex()>enemy->getDex()) turn = true;
        else turn = false;
        melee->hide();
        ranged->hide();
        defend->hide();
        runAway->hide();
        start = new QTimer();
        start->setSingleShot(true);
        connect(start, &QTimer::timeout, this, &Battle::isTurn);
        start->start(1000);
    }
}

void Battle::isTurn(){
    start->disconnect(start, &QTimer::timeout, this, &Battle::isTurn);;
    if(!turn){
        if(enemy->getName() == "hydra") enemyAttack();
        return enemyAttack();
    }
    else{
        melee->show();
        ranged->show();
        defend->show();
        runAway->show();
    }
}

void Battle::enemyAttack(){
    int attack, damage, armor;
    bool type = false;
    if(rand()%2 == 1) type = true;
    attack = rand() % 20 + 1;
    if(attack<20&&attack>1){
        attack +=(enemy->getLuck()- character->getLuck())/5;
        if(d) attack -=5;
    }
    Armor tmp = character->getArmor();
    if(tmp.getName()!="null") armor = tmp.getBonus();
    else armor = 0;
    if(type&&attack>=15) damage = rand() % 3 + 1 + enemy->getAtk() - character->getDef() - armor;
    else if(!type&&attack>=10) damage = ceil(1.5*(rand() % 3 + 1 + enemy->getAtk() - character->getDef() - armor));
    else damage = -10;
    if(attack == 20) damage *=2;
    if(damage<1&&damage>-10) damage = 1;
    else if(damage<-9) damage = 0;
    if(attack == 1) enemy->addHp(-1);
    else character->addHp(-damage);
    checkHp();
    if((type&&attack<15)||(!type&&attack<10)) damageCount->setPlainText("enemy missed");
    else damageCount->setPlainText(QString::number(damage));
    hp->hide();
    hp->setPlainText(QString::number(character->getHp())+ "/" + QString::number(character->getVit()*2+10));
    hp->show();
    damageCount->setDefaultTextColor(Qt::red);
    damageCount->setScale(3);
    damageCount->show();
    if(attack == 1) damageCount->setPos(650,0);
    damageCount->setPos(150,450);
    start->setSingleShot(true);
    connect(start, &QTimer::timeout, this, &Battle::hide);
    start->start(1000);
    if(character->getHp()>0){
        turn = true;
        return isTurn();
    }
}

void Battle::meleeAttack(){
    melee->setColor(Qt::gray);
    melee->hide();
    ranged->hide();
    defend->hide();
    runAway->hide();
    int attack, damage;
    attack = rand() % 20 + 1;
    if(attack<20&&attack>1) attack +=floor((character->getLuck()- enemy->getLuck())/5);
    if(attack>=10) damage = rand() % 3 + 1 + character->getAtk() - enemy->getDef() + character->getMeleeWeapon().getBonus();
    else damage = -10;
    if(damage<1&&damage>-10) damage = 1;
    else if(damage<-9) damage = 0;
    if(attack == 20) damage *=2;
    if(attack == 1) character->addHp(-1);
    else enemy->addHp(-damage);
    if(attack<10) damageCount->setPlainText("u missed");
    else damageCount->setPlainText(QString::number(damage));
    damageCount->setDefaultTextColor(Qt::red);
    damageCount->setScale(3);
    damageCount->show();
    damageCount->setPos(950,450);
    start->setSingleShot(true);
    connect(start, &QTimer::timeout, this, &Battle::hide);
    start->start(1000);
    turn = false;
    checkHp();
    return;
}

void Battle::rangedAttack(){
    ranged->setColor(Qt::gray);
    melee->hide();
    ranged->hide();
    defend->hide();
    runAway->hide();
    int attack, damage;
    attack = rand() % 20 + 1;
    if(attack<20&&attack>1) attack +=floor((character->getLuck()- enemy->getLuck())/5);
    if(attack>=15) damage = rand() % 3 + 1 + character->getAtk() - enemy->getDef() + character->getRangedWeapon().getBonus();
    else damage = -10;
    if(damage<1&&damage>-10) damage = 1;
    else if(damage<-9) damage = 0;
    if(attack == 20) damage *=2;
    damage = ceil(1.5*damage);
    if(attack == 1) character->addHp(-1);
    else enemy->addHp(-damage);
    if(attack<15) damageCount->setPlainText("missed");
    else damageCount->setPlainText(QString::number(damage));
    damageCount->setDefaultTextColor(Qt::red);
    damageCount->setScale(3);
    damageCount->show();
    damageCount->setPos(950,450);
    start->setSingleShot(true);
    connect(start, &QTimer::timeout, this, &Battle::hide);
    start->start(1000);
    turn = false;
    checkHp();
    return;
}

void Battle::defense(){
    defend->setColor(Qt::gray);
    melee->hide();
    ranged->hide();
    defend->hide();
    runAway->hide();
    d = true;
    turn = false;
    start->setSingleShot(true);
    connect(start, &QTimer::timeout, this, &Battle::isTurn);
    start->start(1000);
}

void Battle::run(){
    cSprite->stop();
    cSprite->~QTimer();
    soundtrack->stop();
    start->~QTimer();
    this->close();
    build->getMainMenu()->show();
}

void Battle::back(){
    start->~QTimer();
    this->close();
    build->getMainMenu()->show();
}

void Battle::checkHp(){
    if(character->getHp()>0&&enemy->getHp()>0){
        start->setSingleShot(true);
        connect(start, &QTimer::timeout, this, &Battle::isTurn);
        start->start(1000);
        return;
    }
    melee->hide();
    ranged->hide();
    defend->hide();
    runAway->hide();
    if(character->getHp()<=0){
        character->setHp(0);
        character->hide();
        enemy->stop();
        winLose = new QGraphicsTextItem();
        winLose->setPlainText("Ouch, this enemy was too strong for you\nBetter luck next time");
        winLose->setScale(3);
        winLose->setDefaultTextColor(Qt::red);
    }
    else if(enemy->getHp()<=0){
        enemy->hide();
        cSprite->stop();
        character->addXp(enemy->getXp());
        winLose = new QGraphicsTextItem();
        winLose->setPlainText("Congratulations, you've slain your foe");
        winLose->setScale(3);
        winLose->setDefaultTextColor(Qt::darkGreen);
    }
    scene->addItem(winLose);
    disconnect(start);
    connect(start, &QTimer::timeout, this, &Battle::run);
    if(enemy->getName() == "goblin"){
        int chance = rand() % 20 + floor(character->getLuck()/5);
        if(chance >=10){
            int qtd = (rand() % 10 + 1) * (rand() % 5 + 1) + character->getLuck()*(rand() % 5);
            QString text = winLose->toPlainText();
            text += "\nThe goblin left some money for you";
            winLose->setPlainText(text);
            character->addMoney(qtd);
        }
    }
    else if(enemy->getName() == "wolf"){
        if((rand() % 5 + ceil(1+character->getLuck()/10) >= 5)){
            srand(time(NULL));
            int qtd = rand() % 4 + ceil(1 + character->getLuck()/10);
            QString text = winLose->toPlainText();
            text += "\nThe wolf left some stuff for you";
            winLose->setPlainText(text);
            Item claws("Wolf's Claws", 10, qtd);
            character->setLoot(claws);
        }
        if((rand() % 10 + ceil(1+character->getLuck()/10)) >= 10){
            srand(time(NULL));
            int qtd = rand() % 10 + ceil(1 + character->getLuck()/10);
            QString text = winLose->toPlainText();
            if(!text.contains("\nThe wolf left some stuff for you")) text += "\nThe wolf left some stuff for you";
            winLose->setPlainText(text);
            Item fur("Wolf's Fur", 2, qtd);
            character->setLoot(fur);
        }
    }
    if(character->getXp()>=(character->getLvl()*10+pow(5,character->getLvl()))*10){
        winLose->hide();
        QString text = winLose->toPlainText();
        text+="\nWow, you've been blessed by the skies\nYou can get a lot stronger at the Profile Menu";
        winLose->setPlainText(text);
        character->addLvl();
        character->setUpgrades(character->getUpgrades()+10);
        start->start(5000);
    }
    else start->start(2000);
    winLose->show();
}
