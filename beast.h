#ifndef BEAST_HPP
#define BEAST_HPP

#include <QString>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Beast: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    private:
        int b_hp, b_atk, b_def, b_dex, b_luck, b_xp, spr;
        QString b_name;
        QTimer *sprite;

    public:
        Beast(QString name);

        void change();
        void stop(){sprite->stop();};
        void addHp(int h){b_hp += h;};
        void setHp(int hp){b_hp = hp;};
        void setAtk(int atk){b_atk = atk;};
        void setDef(int def){b_def = def;};
        void setDex(int dex){b_dex = dex;};
        void setLuck(int luck){b_luck = luck;};
        void setXp(int xp){b_xp = xp;};

        int getHp(){return b_hp;};
        int getAtk(){return b_atk;};
        int getDef(){return b_def;};
        int getDex(){return b_dex;};
        int getLuck(){return b_luck;};
        int getXp(){return b_xp;};
        QString getName(){return b_name;};

        void operator - (int damage){b_hp-=damage;};

        ~Beast(){};

};

#endif//BEAST_HPP
