#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsView>

#include "button.h"
#include "battle.h"
#include "points.h"
#include "rest.h"
#include "inventory.h"
#include "store.h"

class MainMenu: public QGraphicsView{
    Q_OBJECT
public:
    MainMenu();
    void bback();
    void pback();
    void rback();
    void iback();
    void sback();

    void setWent(bool b){went = b;};

    bool getWent(){return went;};

public slots:
    void b();
    void p();
    void r();
    void i();
    void s();
    void q();

private:
    bool went;
    QGraphicsScene *scene;
    Button *battle, *points, *rest, *inventory, *store, *quit;
    Battle *fight;
    Points *profile;
    Rest *inn;
    Inventory *equipment;
    Store *shop;
};

#endif // MAINMENU_H
