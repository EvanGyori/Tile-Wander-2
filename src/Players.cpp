#include "Players.h"
#include "Info.h"

Players::Players() {
    playerWeaponId = 0;
    playerWeaponStat = 0;
    playerShieldId = 0;
    playerMaxHp = 0;
    playerHp = 0;
    playerX = 0;
    playerY = 0;
    playerGold = 0;
}

Players::~Players() {

}

Players::Players(string name, int weaponId, int weaponStat, int shieldId, float maxHp, float hp) {
    playerName = name;
    playerWeaponId = weaponId;
    playerWeaponStat = weaponStat;
    playerShieldId = shieldId;
    playerMaxHp = maxHp;
    playerHp = hp;
    playerX = 12;
    playerY = 12;
    playerGold = 0;
    playerLvl = 1;
    playerXp = 0;
}

string Players::getName() const {
    return playerName;
}

int Players::getWpnId() const {
    return playerWeaponId;
}

int Players::getWpnStat() const {
    return playerWeaponStat;
}

int Players::getShield() const {
    return playerShieldId;
}

float Players::getMaxHp() const {
    return playerMaxHp;
}

float Players::getHp() const {
    return playerHp;
}

int Players::getX() const {
    return playerX;
}

int Players::getY() const {
    return playerY;
}

int Players::getGold() const {
    return playerGold;
}

int Players::getLvl() const {
    return playerLvl;
}

int Players::getXp() const {
    return playerXp;
}

void Players::setWpnId(int weaponId) {
    playerWeaponId = weaponId;
}

void Players::setWpnStat(int weaponStat) {
    playerWeaponStat = weaponStat;
}

void Players::setShield(int shield) {
    playerShieldId = shield;
}

void Players::setMaxHp(float maxHp) {
    playerMaxHp = maxHp;
}

void Players::setHp(float hp) {
    playerHp = hp;
}

void Players::setX(int x) {
    playerX = x;
}

void Players::setY(int y) {
    playerY = y;
}

void Players::addGold(int newGold) {
    playerGold += newGold;
}

void Players::addXp(int newXp) {
    playerXp += newXp;
}
