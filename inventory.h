#ifndef INVENTORY_H
#define INVENTORY_H

#include <QGraphicsView>
#include <QLineEdit>

#include "character.h"
#include "button.h"

class Inventory: public QGraphicsView{
    Q_OBJECT;
public:
    Inventory();
    void info();
    void func();
public slots:
    void loot();
    void weaponry();
    void armory();
    void exit();
    void changeW();
    void changeA();
private:
    QGraphicsScene * scene;
    QLineEdit *id;
    QGraphicsTextItem *lootList, *armorList, *weaponList, *desc;
    Button *geral, *battle, *armor, *quit, *confirmChange;
    QTimer *killer;
};

#endif // INVENTORY_H
