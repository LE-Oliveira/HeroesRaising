#ifndef ITEM_H
#define ITEM_H
#include "beast.h"

class Item{
    protected:
        QString i_name;
        int i_price, i_amount;
    public:
        Item(){i_name = ""; i_price = 0; i_amount = 0;};
        Item(QString name, int price, int amount){i_name = name; i_price = price; i_amount = amount;};

        void setName(QString name){i_name = name;};
        void setPrice(int price){i_price = price;};
        void setAmount(int amount){i_amount = amount;};

        int getAmount(){return i_amount;};
        int getPrice(){return i_price;};
        QString getName(){return i_name;};

        void operator+(int amount){i_amount+=amount;};

        ~Item(){};
};
#endif //ITEM_HPP
