#include "weapon.h"

Weapon::Weapon(QString name){
    i_name = name;
    if(name == "Short Bow"){
        i_amount = 1;
        i_price = 2500;
        w_melee = false;
        w_equiped = w_owned = w_ranged = true;
        w_bonus = 1;
    }
    else if(name == "Iron Dagger"){
        i_amount = 1;
        i_price = 200;
        w_equiped = w_owned = w_melee = true;
        w_ranged = false;
        w_bonus = 0;
    }
    else if(name == "Long Bow"){
        i_amount = 1;
        i_price = 5000;
        w_equiped = w_owned = w_melee = false;
        w_ranged = true;
        w_bonus = 2;
    }
    else if(name == "Short Sword"){
        i_amount = 1;
        i_price = 1000;
        w_equiped = w_ranged = false;
        w_owned = w_melee = true;
        w_bonus = 2;
    }
    else if(name == "Spear"){
        i_amount = 1;
        i_price = 1000;
        w_ranged = w_equiped = w_owned = false;
        w_melee = true;
        w_bonus = 2;
    }
    else if(name == "Battle Hammer"){
        i_amount = 1;
        i_price = 3000;
        w_ranged = w_equiped = w_owned = false;
        w_melee = true;
        w_bonus = 3;
    }
    else if(name == "Scythe"){
        i_amount = 1;
        i_price = 5000;
        w_ranged = w_equiped = w_owned = false;
        w_melee = true;
        w_bonus = 5;
    }
    else if(name == "null"){
        i_amount = 0;
        i_price = 0;
        w_bonus = 0;
        w_equiped = w_ranged = w_melee = false;
        w_owned = false;
    }
}
