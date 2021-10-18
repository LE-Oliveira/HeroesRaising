#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QGraphicsPixmapItem>
#include <vector>

#include "item.h"
#include "armor.h"
#include "weapon.h"

class Character: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Character();
    void change();
    void addDef(int c){def += c;};
    void addAtk(int s){atk += s;};
    void addDex(int d){dex += d;};
    void addLuck(int l){luck += l;};
    void addVit(int v){vit += v;};
    void addLvl(){lvl++;};
    void addXp(int x){xp += x;};
    void addUpgrade(int u){upgrades+= u;};
    void setUpgrades(int u){upgrades = u;};
    void setName(QString n){name = n;};
    void setHp(int h){hp = h;};
    void addHp(int h){hp+=h;};
    void addMoney(int m){money+=m;};
    void setLoot(Item i);
    void clearL(){c_inventory.clear();};
    Weapon changeW(Weapon weapon);
    Armor changeA(Armor armor);
    void addA(Armor armor){c_armors.push_back(armor);};

    int getDef(){return def;};
    int getAtk(){return atk;};
    int getDex(){return dex;};
    int getLuck(){return luck;};
    int getVit(){return vit;};
    int getLvl(){return lvl;};
    int getXp(){return xp;};
    int getHp(){return hp;};
    int getUpgrades(){return upgrades;};
    int getMoney(){return money;};
    QString getName(){return name;};
    std::vector<Weapon> getWeapons(){return c_weapons;};
    std::vector<Armor> getArmors(){return c_armors;};
    std::vector<Item> getLoot(){return c_inventory;};
    Weapon getRangedWeapon();
    Weapon getMeleeWeapon();
    Armor getArmor();

private:
    std::vector<Weapon> c_weapons;
    std::vector<Armor> c_armors;
    std::vector<Item> c_inventory;
    int def, atk, dex,luck, vit, lvl, xp, hp, upgrades, money, sprite;
    QString name;

};

#endif // CHARACTER_H
