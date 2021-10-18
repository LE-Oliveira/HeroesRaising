#include <QDebug>

#include "character.h"

Character::Character(){
    sprite = 0;
    def = 1;
    atk = 1;
    dex = 1;
    luck = 1;
    vit = 1;
    lvl = 1;
    xp = 0;
    upgrades = 10;
    hp = 10 + 2*vit;
    name = "";
    money = 100;
    setPixmap(QPixmap(":/mc/sprites/mc0.png").scaled(128, 108));
    Weapon melee("Iron Dagger");
    c_weapons.push_back(melee);
    Weapon range("Short Bow");
    c_weapons.push_back(range);
}

void Character::change(){
    sprite++;
    if(sprite>=4) sprite = 0;
    QString a = ":/mc/sprites/mc" + QString::number(sprite) + ".png";
    setPixmap(QPixmap(a).scaled(128, 108));
}

void Character::setLoot(Item i){
    unsigned long long j=0;
    QString aux = i.getName();
    for(j=0; j<c_inventory.size(); j++){
        if(aux==c_inventory.at(j).getName()){
            c_inventory.at(j)+(i.getAmount());
            break;
        }
    }
    if(j==0||j==c_inventory.size()-1) c_inventory.push_back(i);
}

Weapon Character::getRangedWeapon(){
    for(unsigned long long i=0; i<c_weapons.size(); i++){
        if(c_weapons.at(i).getEquiped()&&c_weapons.at(i).getRanged()) return c_weapons.at(i);
    }
    Weapon w("null");
    return w;
}

Weapon Character::getMeleeWeapon(){
    for(unsigned long long i=0; i<c_weapons.size(); i++){
        if(c_weapons.at(i).getEquiped()&&c_weapons.at(i).getMelee()) return c_weapons.at(i);
    }
    Weapon w("null");
    return w;
}

Armor Character::getArmor(){
    for(unsigned long long i=0; i<c_armors.size(); i++){
        if(c_armors.at(i).getEquiped()) return c_armors.at(i);
    }
    Armor obj("null");
    return obj;
}

Armor Character::changeA(Armor armor){
    Armor tmp = c_armors.at(0);
    c_armors.clear();
    c_armors.push_back(armor);
    return tmp;
}

Weapon Character::changeW(Weapon weapon){
    Weapon tmp;
    if(c_weapons.at(0).getMelee()&&weapon.getMelee()){
        tmp = c_weapons.at(0);
        c_weapons.at(0) = weapon;
    }
    else if(c_weapons.at(0).getRanged()&&weapon.getRanged()){
        tmp = c_weapons.at(0);
        c_weapons.at(0) = weapon;
    }
    else if(c_weapons.at(1).getMelee()&&weapon.getMelee()){
        tmp = c_weapons.at(1);
        c_weapons.at(1) = weapon;
    }
    else if(c_weapons.at(1).getRanged()&&weapon.getRanged()){
        tmp = c_weapons.at(1);
        c_weapons.at(1) = weapon;
    }
    return tmp;
}
