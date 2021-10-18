#ifndef POINTS_H
#define POINTS_H

#include <QGraphicsView>

#include "button.h"

class Points: public QGraphicsView{
    Q_OBJECT;
public:
    Points();
    void lines(QGraphicsTextItem* title, QString string, QColor color);
public slots:
    void upgrade();
    void back();
    void pCons();
    void pStr();
    void pDex();
    void pLuck();
    void pVit();
    void lCons();
    void lStr();
    void lDex();
    void lLuck();
    void lVit();
    void conf();
private:
    QGraphicsScene * scene;
    QGraphicsTextItem *name, *str, *dex, *con, *luc, *vit, *hp, *xp, *lvl, *money, *upgrades;
    Button *next, *quit, *confirm;
    Button *pC, *pS, *pD, *pL, *pV;
    Button *lC, *lS, *lD, *lL, *lV;
};

#endif // POINTS_H
