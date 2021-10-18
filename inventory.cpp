#include <QIcon>

#include "inventory.h"
#include "build.h"
#include "item.h"
#include "weapon.h"

extern Build *build;
extern Character *character;

Inventory::Inventory(){
    setWindowTitle("Hero's Rise Inventory");
    setWindowIcon(QIcon(":/icon/HerosRise.ico"));
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,437);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,437);
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/inventory.jpg").scaled(800, 437)));
    setScene(scene);
    geral = new Button("inventory", "Loot", QPoint(0,0), QPoint(0,0), QPoint(70,30), Qt::lightGray, true);
    connect(geral, SIGNAL(clicked()), this, SLOT(loot()));
    scene->addItem(geral);
    battle = new Button("inventory", "Weapons", QPoint(100,0), QPoint(0,0), QPoint(70,30), Qt::lightGray, true);
    connect(battle, SIGNAL(clicked()), this, SLOT(weaponry()));
    scene->addItem(battle);
    armor = new Button("inventory", "Armors", QPoint(200,0), QPoint(0,0), QPoint(70,30), Qt::lightGray, true);
    connect(armor, SIGNAL(clicked()), this, SLOT(armory()));
    scene->addItem(armor);
    quit = new Button("inventory", "Quit", QPoint(750,400), QPoint(0,0), QPoint(30,30), Qt::lightGray, true);
    connect(quit, SIGNAL(clicked()), this, SLOT(exit()));
    scene->addItem(quit);
}

void Inventory::loot(){
    geral->hide();
    battle->hide();
    armor->hide();
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/items.jpg").scaled(800,437)));
    std::vector<Item> loots = character->getLoot();
    lootList = new QGraphicsTextItem();
    if(loots.size() == 0) lootList->setPlainText("You have no items, battle to acquire some more");
    else{
        QString list = lootList->toPlainText();
        for(unsigned long long i = 0; i<loots.size(); i++){
            list+=("You have " + QString::number(loots.at(i).getAmount()) + " units of " + loots.at(i).getName() + "\n");
        }
        lootList->setPlainText(list);
    }
    lootList->setDefaultTextColor(Qt::black);
    lootList->setFont(QFont("Gabriola", 20));
    lootList->setPos(50,50);
    scene->addItem(lootList);
    lootList->show();
}

void Inventory::weaponry(){
    geral->hide();
    battle->hide();
    armor->hide();
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/items.jpg").scaled(800,437)));
    std::vector<Weapon> weapons = character->getWeapons();
    weaponList = new QGraphicsTextItem();
    if(weapons.size() == 0) weaponList->setPlainText("You have no weapon, buy some at the Store");
    else{
        QString list = weaponList->toPlainText();
        list+= "You have the following weapons:\n";
        for(unsigned long long i = 0; i<weapons.size(); i++){
            list+=QString::number(i+1) + " - " + weapons.at(i).getName() + " which gives you + " + QString::number(weapons.at(i).getBonus()) + "\n";
        }
        weaponList->setPlainText(list);
    }
    weaponList->setDefaultTextColor(Qt::black);
    weaponList->setFont(QFont("Gabriola", 20));
    weaponList->setPos(50,50);
    scene->addItem(weaponList);
    weaponList->show();
    info();
    connect(confirmChange, SIGNAL(clicked()), this, SLOT(changeW()));
}

void Inventory::armory(){
    geral->hide();
    battle->hide();
    armor->hide();
    scene->setBackgroundBrush(QBrush(QPixmap(":/background/items.jpg").scaled(800,437)));
    std::vector<Armor> armors = character->getArmors();
    armorList = new QGraphicsTextItem();
    if(armors.size() == 0) armorList->setPlainText("You have no armor, buy some at the Store");
    else{
        QString list = armorList->toPlainText();
        list+= "You have the following weapons:\n";
        for(unsigned long long i = 0; i<armors.size(); i++){
            list+=QString::number(i+1) + " - " + armors.at(i).getName() + " which giver you +" + QString::number(armors.at(i).getBonus()) + "\n";
        }
        armorList->setPlainText(list);
    }
    armorList->setDefaultTextColor(Qt::black);
    armorList->setFont(QFont("Gabriola", 20));
    armorList->setPos(50,50);
    scene->addItem(armorList);
    armorList->show();
    info();
    connect(confirmChange, SIGNAL(clicked()), this, SLOT(changeA()));
}

void Inventory::info(){
    desc = new QGraphicsTextItem();
    desc->setPlainText("Insert an ID to change equipment:");
    scene->addItem(desc);
    desc->setPos(140,390);
    id = new QLineEdit();
    id->move(320,390);
    scene->addWidget(id);
    confirmChange = new Button("confirm", "Confirm Change", QPoint(525,390), QPoint(0,0), QPoint(100,18), Qt::green, true);
    scene->addItem(confirmChange);
}

void Inventory::changeW(){
    int aux = id->text().toInt() - 1;
    if(aux>=character->getWeapons().size()) return;
    QString type;
    if(character->getWeapons().at(aux).getMelee()) type = "melee";
    for(int i = 0; i<aux;i++){
        Weapon tmp = character->getWeapons().at(i);
        if(tmp.getEquiped()&&tmp.getMelee()){
            character->getWeapons().at(i).setEquiped(false);
            break;
        }
    }
    character->getWeapons().at(aux).setEquiped(true);
    desc->setPlainText("Equipment sucessfully changed");
    desc->setPos(350,218);
    killer = new QTimer();
    connect(killer, &QTimer::timeout, this, &Inventory::func);
    killer->start(1500);
}

void Inventory::changeA(){
    int aux = id->text().toInt() - 1;
    if(aux>=character->getArmors().size()) return;
    for(int i = 0; i<aux;i++){
        Armor tmp = character->getArmors().at(i);
        if(tmp.getEquiped()){
            character->getArmors().at(i).setEquiped(false);
            break;
        }
    }
    character->getArmors().at(aux).setEquiped(true);
    desc->setPlainText("Equipment sucessfully changed");
    desc->setPos(350,218);
    killer = new QTimer();
    connect(killer, &QTimer::timeout, this, &Inventory::func);
    killer->start(1500);
}

void Inventory::func(){desc->hide(); killer->~QTimer();}

void Inventory::exit(){
    this->close();
    build->getMainMenu()->show();
}
