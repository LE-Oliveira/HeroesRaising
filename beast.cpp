#include "beast.h"
#include <math.h>

#include <QGraphicsTextItem>
#include <QObject>

Beast::Beast(QString name){
    b_name = name;
    if(name == "wolf"){
        b_hp = rand() % 8 + 2 +rand() % 8;
        b_atk = rand () % 4 + 2;
        b_def = rand () % 3 + 2;
        b_dex = rand () % 7 + 2;
        b_luck = rand () % 10 + 1;
        b_xp = b_hp + b_dex*5 + b_atk*4 + b_def*3 + ceil(b_luck/2);
        sprite = new QTimer();
        sprite->setInterval(80);
        spr = 0;
        connect(sprite, &QTimer::timeout, this, &Beast::change);
        sprite->start();
        setPixmap(QPixmap(":/wolf/sprites/wolf0.png").scaled(110,76));
    }
    else if(name == "goblin"){
        b_hp = rand() % 6 + 1 + rand() % 6;
        b_atk = rand () % 3 + 1;
        b_def = rand () % 2 + 1;
        b_dex = rand () % 4 + 1;
        b_luck = rand () % 10 + 1;
        b_xp = b_hp + b_dex*5 + b_atk*4 + b_def*3 + ceil(b_luck/2);
        sprite = new QTimer();
        sprite->setInterval(120);
        spr = 0;
        connect(sprite, &QTimer::timeout, this, &Beast::change);
        sprite->start();
        setPixmap(QPixmap(":/goblin/sprites/goblin0.png").scaled(96,96));
    }
    else if(name == "flameskull"){
        b_hp = rand() % 6 + 4 + rand() % 6 + rand() % 6 + rand() % 6;
        b_atk = rand () % 4 + 2;
        b_def = rand () % 3 + 2;
        b_dex = rand () % 7 + 2;
        b_luck = rand() % 5 + 1;
        b_xp = b_hp + b_dex*5 + b_atk*4 + b_def*3 + ceil(b_luck/2);
        sprite = new QTimer();
        sprite->setInterval(60);
        spr = 0;
        connect(sprite, &QTimer::timeout, this, &Beast::change);
        sprite->start();
        setPixmap(QPixmap(":/flameskull/sprites/flameskull0.png").scaled(86,80));
    }
    else if(name == "hydra"){
        b_hp = rand() % 10 + 30 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10;
        b_atk = rand() % 5 + rand() % 5 + 10;
        b_def = rand() % 5 + rand() % 5 + 6;
        b_dex = rand() % 6 + 1;
        b_luck = rand() % 5 + 2;
        b_xp = b_hp + b_dex*5 + b_atk*4 + b_def*3 + ceil(b_luck/2);
        sprite = new QTimer();
        sprite->setInterval(60);
        spr = 0;
        connect(sprite, &QTimer::timeout, this, &Beast::change);
        sprite->start();
        setPixmap(QPixmap(":/hydra/sprites/hydra0.png").scaled(140,140));
    }
    else if(name == "beholder"){
        b_hp = rand() % 10 + 50 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10;
        b_atk = rand() % 5 + rand() % 5 + rand() % 5 + 10;
        b_def = rand() % 5 + rand() % 5 + 6;
        b_dex = rand() % 6 + 1;
        b_luck = rand() % 5 + 10;
        b_xp = b_hp + b_dex*5 + b_atk*4 + b_def*3 + ceil(b_luck/2);
        sprite = new QTimer();
        sprite->setInterval(110);
        spr = 0;
        connect(sprite, &QTimer::timeout, this, &Beast::change);
        sprite->start();
        setPixmap(QPixmap(":/beholder/sprites/beholder0.png").scaled(180,180));
    }
    else if(name == "boss"){
        b_hp = rand() % 10 + 100 + rand() % 10 + rand() % 10 + rand() % 10 + rand() % 10;
        b_atk = rand() % 5 + rand() % 5 + rand() % 5 + rand() % 5 + 20;
        b_def = rand() % 5 + rand() % 5 + 10;
        b_dex = rand() % 6 + 3;
        b_luck = rand() % 5 + 5;
        b_xp = b_hp + b_dex*5 + b_atk*4 + b_def*3 + ceil(b_luck/2);
        sprite = new QTimer();
        sprite->setInterval(100);
        spr = 0;
        connect(sprite, &QTimer::timeout, this, &Beast::change);
        sprite->start();
        setPixmap(QPixmap(":/boss/sprites/boss0.png").scaled(225,260));
    }
}

void Beast::change(){
    spr++;
    if(b_name=="wolf"){
        if(spr>5) spr = 0;
        QString a = ":/wolf/sprites/wolf" + QString::number(spr) + ".png";
        setPixmap(QPixmap(a).scaled(165,114));
    }
    else if(b_name=="goblin"){
        if(spr>2) spr = 0;
        QString a = ":/goblin/sprites/goblin" + QString::number(spr) + ".png";
        setPixmap(QPixmap(a).scaled(96,96));
    }
    else if(b_name == "flameskull"){
        if(spr>7) spr = 0;
        QString a = ":/flameskull/sprites/flameskull" + QString::number(spr) + ".png";
        setPixmap(QPixmap(a).scaled(86,80));
    }
    else if(b_name=="hydra"){
        if(spr>7) spr = 0;
        QString a = ":/hydra/sprites/hydra" + QString::number(spr) + ".png";
        setPixmap(QPixmap(a).scaled(200,200));
    }
    else if(b_name == "beholder"){
        if(spr>5) spr = 0;
        QString a = ":/beholder/sprites/beholder" + QString::number(spr) + ".png";
        setPixmap(QPixmap(a).scaled(250,250));
    }
    else if(b_name == "boss"){
        if(spr>7) spr = 0;
        QString a = ":/boss/sprites/boss" + QString::number(spr) + ".png";
        setPixmap(QPixmap(a).scaled(338,390));
    }
}

