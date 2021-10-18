#include <QIcon>
#include <QTimer>

#include "mainmenu.h"
#include "button.h"

MainMenu::MainMenu(){
    went = false;
    setWindowTitle("Hero's Rise");
    setWindowIcon(QIcon(":/icon/HerosRise.ico"));
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/spaceground.png").scaled(800,600)));
    scene->setSceneRect(0,0,800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);
    battle = new Button("menu", "Battle", QPoint(100,100), QPoint(0,0), QPoint(100,30), Qt::red, true);
    connect(battle, SIGNAL(clicked()), this, SLOT(b()));
    scene->addItem(battle);
    points = new Button("menu", "See Points", QPoint(100,130), QPoint(0,0), QPoint(100,30), Qt::cyan, true);
    connect(points, SIGNAL(clicked()), this, SLOT(p()));
    scene->addItem(points);
    rest = new Button("menu", "Rest and Heal", QPoint(100,160), QPoint(0,0), QPoint(100,30), Qt::green, true);
    connect(rest, SIGNAL(clicked()), this, SLOT(r()));
    scene->addItem(rest);
    inventory = new Button("menu", "Inventory", QPoint(100,190), QPoint(0,0), QPoint(100,30), Qt::white, true);
    connect(inventory, SIGNAL(clicked()), this, SLOT(i()));
    scene->addItem(inventory);
    store = new Button("menu", "Store", QPoint(100,220), QPoint(0,0), QPoint(100,30), Qt::yellow, true);
    connect(store, SIGNAL(clicked()), this, SLOT(s()));
    scene->addItem(store);
    quit = new Button("menu", "Quit Game", QPoint(100,250), QPoint(0,0), QPoint(100,30), Qt::gray, true);
    connect(quit, SIGNAL(clicked()), this, SLOT(q()));
    scene->addItem(quit);
    setScene(scene);
}

void MainMenu::b(){
    this->hide();
    fight = new Battle();
    fight->show();
    went = false;
}

void MainMenu::p(){
    this->hide();
    profile = new Points();
    profile->show();
    //QTimer *t = new QTimer();
    //t->setSingleShot(true);
    //connect(t, &QTimer::timeout, this, &MainMenu::pback);
    //t->start(10000);
}

void MainMenu::r(){
    this->hide();
    inn = new Rest();
    inn->show();
}

void MainMenu::i(){
    this->hide();
    equipment = new Inventory();
    equipment->show();
}

void MainMenu::s(){
    this->hide();
    shop = new Store();
    shop->show();
}

void MainMenu::q(){
    this->close();
}

void MainMenu::bback(){
    fight->close();
    this->show();
}

void MainMenu::pback(){
    profile->close();
    this->show();
}

void MainMenu::rback(){
    inn->close();
    this->show();
}

void MainMenu::iback(){
    equipment->close();
    this->show();
}

void MainMenu::sback(){
    shop->close();
    this->show();
}
