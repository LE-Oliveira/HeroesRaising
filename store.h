#ifndef STORE_H
#define STORE_H

#include <QGraphicsView>
#include <QMediaPlayer>
#include <QLineEdit>

#include "button.h"
#include "weapon.h"
#include "armor.h"

class Store: public QGraphicsView{
    Q_OBJECT;
public:
    Store();
public slots:
    void leave();
    void buyItem();
    void sellItem();
    void buyY();
    void sellY();
private:
    QGraphicsScene * scene;
    Button *buy, *sell, *quit, *confirmChange;
    QLineEdit *id;
    QMediaPlayer *soundtrack;
    QGraphicsTextItem *itemList, *desc;
    std::vector<Armor> armors;
    std::vector<Weapon> weapons;
};

#endif // STORE_H
