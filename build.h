#ifndef BUILD_H
#define BUILD_H

#include <QGraphicsView>
#include <QMediaPlayer>
#include <QLineEdit>

#include "button.h"
#include "mainmenu.h"

class Build: public QGraphicsView{
Q_OBJECT;
public:
    Build(QWidget *parent = 0);
    MainMenu* getMainMenu(){return mm;};
    void atualizaPoints();
    void lines(QGraphicsTextItem* title, QString string, QColor color);
public slots:
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
    QMediaPlayer * music;
    Button *pC, *pS, *pD, *pL, *pV;
    QGraphicsTextItem *c, *s, *d, *l, *v, *intro, *points, *name;
    Button *lC, *lS, *lD, *lL, *lV;
    Button *confirm;
    QLineEdit *nameEntry;
    MainMenu *mm;
};

#endif // BUILD_H
