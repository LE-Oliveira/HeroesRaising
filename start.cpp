#include "start.h"

#include <QIcon>
#include <QPushButton>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsView>

#include <QObject>

#include "build.h"
#include "button.h"

Build* build;

Start::Start(){
    setWindowTitle("Hero's Rise");
    setWindowIcon(QIcon(":/icon/HerosRise.ico"));
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/start.png")));
    scene->setSceneRect(0,0,415,572);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(415,573);
    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/soundtrack/start.mp3"));
    music->play();
    Button *startButton = new Button("start", "Start Game", QPoint(180, 400), QPoint(0,0), QPoint(70,50), Qt::green, true);
    setScene(scene);
    scene->addItem(startButton);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startBuild()));
}

void Start::startBuild(){
    music->stop();
    for(int i = 0; i<scene->items().size() -1; i++){
        scene->removeItem(scene->items().at(i));
    }
    close();
    build = new Build();
    build->show();
}

