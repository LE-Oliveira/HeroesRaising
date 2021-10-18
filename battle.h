#ifndef BATTLE_H
#define BATTLE_H

#include <QGraphicsView>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "beast.h"
#include "button.h"

class Battle: public QGraphicsView{
    Q_OBJECT;
public:
    Battle();
    void isTurn();
    void enemyAttack();
    void hide(){damageCount->hide();};
    void checkHp();

public slots:
    void meleeAttack();
    void rangedAttack();
    void defense();
    void run();
    void back();

private:
    QGraphicsTextItem *damageCount, *winLose, *hp;
    bool turn, d;
    Button *melee, *ranged, *defend, *runAway;
    Beast *enemy;
    QGraphicsScene *scene;
    QMediaPlayer *soundtrack;
    QTimer *cSprite, *start;
};

#endif // BATTLE_H
