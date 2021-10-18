#include <QIcon>
#include <QMediaPlaylist>

#include "store.h"
#include "build.h"
#include "character.h"

extern Build * build;
extern Character * character;

Store::Store(){
    setWindowTitle("Hero's Rise Store");
    setWindowIcon(QIcon(":/icon/HerosRise.ico"));
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/shop.jpg").scaled(800, 600)));
    setScene(scene);
    buy = new Button("shop", "Buy Items", QPoint(200,260), QPoint(0,0), QPoint(55,18), Qt::cyan, true);
    connect(buy, SIGNAL(clicked()), this, SLOT(buyItem()));
    scene->addItem(buy);
    sell = new Button("shop", "Sell Items", QPoint(190,400), QPoint(0,0), QPoint(50,18), Qt::yellow, true);
    connect(sell, SIGNAL(clicked()), this, SLOT(sellItem()));
    scene->addItem(sell);
    quit = new Button("menu", "Quit", QPoint(400,50), QPoint(0,0), QPoint(30,18), Qt::gray, true);
    connect(quit, SIGNAL(clicked()), this, SLOT(leave()));
    scene->addItem(quit);
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/soundtrack/shop1.mp3"));
    playlist->addMedia(QUrl("qrc:/soundtrack/shop2.mp3"));
    playlist->addMedia(QUrl("qrc:/soundtrack/shop3.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->setPlaybackMode(QMediaPlaylist::Random);
    soundtrack = new QMediaPlayer();
    soundtrack->setPlaylist(playlist);
    soundtrack->setVolume(50);
    soundtrack->play();
}

void Store::buyItem(){
    sell->hide();
    buy->hide();
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/items.jpg").scaled(800,600)));
    itemList = new QGraphicsTextItem();
    weapons.push_back(Weapon("Short Bow"));
    weapons.push_back(Weapon("Iron Dagger"));
    weapons.push_back(Weapon("Long Bow"));
    weapons.push_back(Weapon("Short Sword"));
    weapons.push_back(Weapon("Spear"));
    weapons.push_back(Weapon("Battle Hammer"));
    weapons.push_back(Weapon("Scythe"));
    armors.push_back(Armor("Padded Leather"));
    armors.push_back(Armor("Ring Mail"));
    armors.push_back(Armor("Half Plate"));
    armors.push_back(Armor("Chain Mail"));
    armors.push_back(Armor("Spiked Armor"));
    QString tmp = "Id\tName\t\t\tPrice\t\tBonus\n"
                "1\tShort Bow\t\t2500\t\t1\n"
                "2\tIron Dagger\t\t200\t\t0\n"
                "3\tLong Bow\t\t5000\t\t2\n"
                "4\tShort Sword\t\t1000\t\t2\n"
                "5\tSpear\t\t\t1000\t\t2\n"
                "6\tBattle Hammer\t3000\t\t3\n"
                "7\tScythe\t\t\t2500\t\t5\n"
                "8\tPadded Leather\t100\t\t1\n"
                "9\tRing Mail\t\t600\t\t2\n"
                "10\tHalf Plate\t\t2500\t\t3\n"
                "11\tChain Mail\t\t2500\t\t4\n"
                "12\tSpiked Armor\t2500\t\t2\n";
    itemList->setPlainText(tmp);
    desc = new QGraphicsTextItem();
    desc->setPlainText("Which one you wanna buy?");
    desc->setPos(140,550);
    scene->addItem(desc);
    id = new QLineEdit();
    id->move(320,550);
    scene->addWidget(id);
    confirmChange = new Button("confirm", "Buy now", QPoint(550,550), QPoint(0,0), QPoint(50,18), Qt::green, true);
    scene->addItem(confirmChange);
    connect(confirmChange, SIGNAL(clicked()), this, SLOT(buyY()));
    itemList->setDefaultTextColor(Qt::black);
    itemList->setFont(QFont("Times", 20));
    itemList->setPos(60,80);
    scene->addItem(itemList);
    itemList->show();
    quit->setPos(650,550);
}

void Store::sellItem(){
    sell->hide();
    buy->hide();
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/items.jpg").scaled(800,600)));
    std::vector<Item> loots = character->getLoot();
    itemList = new QGraphicsTextItem();
    if(loots.size() == 0) itemList->setPlainText("You have no items, battle to acquire some more");
    else{
        QString list = itemList->toPlainText();
        list = "Id\t\tName\t\tQtd\tPrice\n";
        for(unsigned long long i = 0; i<loots.size(); i++){
            list+=(QString::number(i) + "\t\t" + loots.at(i).getName() + "\t\t" + QString::number(loots.at(i).getAmount()) + "\t\t" + QString::number(loots.at(i).getPrice()) + "\n");
        }
        itemList->setPlainText(list);
        desc = new QGraphicsTextItem();
        desc->setPlainText("Sell all items?");
        desc->setPos(140,550);
        scene->addItem(desc);
        confirmChange = new Button("confirm", "Sell All", QPoint(350,550), QPoint(0,0), QPoint(70,18), Qt::green, true);
        scene->addItem(confirmChange);
        connect(confirmChange, SIGNAL(clicked()), this, SLOT(sellY()));
    }
    itemList->setDefaultTextColor(Qt::black);
    itemList->setFont(QFont("Gabriola", 20));
    itemList->setPos(60,80);
    scene->addItem(itemList);
    itemList->show();
    quit->setPos(650,550);
}

void Store::sellY(){
    for(int i=0; i<character->getLoot().size(); i++){
        Item tmp = character->getLoot().at(i);
        character->addMoney(tmp.getAmount()*tmp.getPrice());
    }
    character->clearL();
    leave();
}

void Store::buyY(){
    int a = id->text().toInt();
    if(a>0&&a<8){
        Weapon next = weapons.at(a-1);
        Weapon last;
        last = character->changeW(next);
        character->addMoney(last.getPrice());
    }
    else if(a>7&&a<13){
        Armor next = armors.at(a-8);
        if(character->getMoney()>=next.getPrice()){
            Armor last;
            if(character->getArmors().size() == 0) character->addA(next);
            else{
                last = character->changeA(next);
                character->addMoney(last.getPrice());
            }
            character->addMoney(-next.getPrice());
        }
    }
    leave();
}

void Store::leave(){
    this->close();
    soundtrack->stop();
    build->getMainMenu()->show();
}
