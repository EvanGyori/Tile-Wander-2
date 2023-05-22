#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

#ifndef PLAYERS_H
#define PLAYERS_H


class Players {
    public:
        //Default constructor
        Players();

        //Destructor
        virtual ~Players();

        //Overload constructor
        Players(string, int, int, int, float, float);

        //Accessor Functions
        string getName() const;
        int getWpnId() const;
        int getWpnStat() const;
        int getShield() const;
        float getMaxHp() const;
        float getHp() const;
        int getX() const;
        int getY() const;
        int getGold() const;
        int getLvl() const;
        int getXp() const;

        //Mutator Functions
        void setWpnId(int);
        void setWpnStat(int);
        void setShield(int);
        void setMaxHp(float);
        void setHp(float);
        void setX(int);
        void setY(int);
        void addGold(int);
        void addXp(int);

    protected:

    private:
        string playerName;
        int playerWeaponId;
        int playerWeaponStat;
        int playerShieldId;
        float playerMaxHp;
        float playerHp;
        int playerX;
        int playerY;
        int playerGold;
        int playerLvl;
        int playerXp;
};

#endif // PLAYERS_H
