#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon: public Item{
    private:
        int w_bonus;
        bool w_equiped, w_owned, w_ranged, w_melee;
    public:
        Weapon(){};
        Weapon(QString name);

        void setBonus(int bonus){w_bonus = bonus;};
        void setEquiped(bool equiped){w_equiped = equiped;};
        void setOwned(bool owned){w_owned = owned;};

        bool getEquiped(){return w_equiped;};
        bool getOwned(){return w_owned;};
        bool getRanged(){return w_ranged;};
        bool getMelee(){return w_melee;};
        int getBonus(){return w_bonus;};

        ~Weapon(){};
};

#endif //WEAPON_HPP
