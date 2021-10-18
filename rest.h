#ifndef REST_H
#define REST_H

#include <QGraphicsView>
#include <QMediaPlayer>

#include "button.h"

class Rest: public QGraphicsView{
    Q_OBJECT;
public:
    Rest();
    void back();
    void hpUp();
    void notEnoughMoney();

public slots:
    void yes();
    void no();
    void healStandard();
    void healAdvanced();
    void healComplete();

private:
    Button *standard, *advanced, *complete, *n, *y;
    QGraphicsScene * scene;
    QGraphicsTextItem *hp, *money, *sentence;
    QTimer *t;
    QMediaPlayer *song;
    int still;

};

#endif // REST_H
