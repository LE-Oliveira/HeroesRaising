#ifndef START_H
#define START_H

#include <QGraphicsView>
#include <QMediaPlayer>

#include "build.h"

class Start: public QGraphicsView {
Q_OBJECT
public:
    Start();
    void qualquer();
    //void mousePressEvent(QMouseEvent * event);
public slots:
    void startBuild();
private:
    QGraphicsScene * scene;
    QMediaPlayer * music;
    //Build *build;
};

#endif // START_H
