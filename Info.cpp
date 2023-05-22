#include "Info.h"

int randNumb(int min = 0, int max = 1) {
  int r = (rand() % (max+1-min))+min;
  return r;
}

int areaX(int x) {
    float area = x/25;
    if (x < 0) {--area;}

    return floor(area);
}

int areaY(int y) {
    float area = y/25;
    if (y < 0) {--area;}

    return floor(area);
}

int areaXToTile(int x) {
    int tile = x*25;
    if (x < 0) {tile+1;}

    return tile;
}

int areaYToTile(int y) {
    int tile = y*25;
    if (y < 0) {tile+1;}

    return tile;
}

float avgDmg(int wpnId, int wpnStat) {
    float dmg = WEAPON_DMG[wpnId] * STAT_DMG[wpnStat];
    float multi = WEAPON_MULTI[wpnId] * STAT_MULTI[wpnStat];
    float chance = WEAPON_CHANCE[wpnId] * STAT_CHANCE[wpnStat];

    return (dmg * multi - dmg) * (chance / 100) + dmg;
}

float dmg(int wpnId, int wpnStat) {
    return WEAPON_DMG[wpnId] * STAT_DMG[wpnStat];
}

float multi(int wpnId, int wpnStat) {
    return WEAPON_MULTI[wpnId] * STAT_MULTI[wpnStat];
}

float chance(int wpnId, int wpnStat) {
    return WEAPON_CHANCE[wpnId] * STAT_CHANCE[wpnStat];
}

float attack(int wpnId, int wpnStat) {
    if (randNumb(1, 100) <= chance(wpnId, wpnStat)) {
        return dmg(wpnId, wpnStat) * multi(wpnId, wpnStat);
    } else {
        return dmg(wpnId, wpnStat);
    }
}

void displayWpn(int wpnId, int wpnStat) {
    float dmg = WEAPON_DMG[wpnId] * STAT_DMG[wpnStat];
    float multi = WEAPON_MULTI[wpnId] * STAT_MULTI[wpnStat];
    float chance = WEAPON_CHANCE[wpnId] * STAT_CHANCE[wpnStat];

    cout << "<" << dmg << " Dmg, " << multi << "x BrutalDmg, " << chance << " BrutalLuck, " << avgDmg(wpnId, wpnStat) << " AvgDmg>";
}

void compareWpn(int id1, int stat1, int id2, int stat2) {
    float dmg1 = WEAPON_DMG[id1] * STAT_DMG[stat1];
    float multi1 = WEAPON_MULTI[id1] * STAT_MULTI[stat1];
    float chance1 = WEAPON_CHANCE[id1] * STAT_CHANCE[stat1];

    float dmg2 = WEAPON_DMG[id2] * STAT_DMG[stat2];
    float multi2 = WEAPON_MULTI[id2] * STAT_MULTI[stat2];
    float chance2 = WEAPON_CHANCE[id2] * STAT_CHANCE[stat2];

    colorOutput(7);
    cout << "<";
    if (dmg1 > dmg2) { colorOutput(10); }
    if (dmg1 < dmg2) { colorOutput(12); }
    cout << dmg1;
    colorOutput(7);
    cout << " Dmg, ";
    if (multi1 > multi2) { colorOutput(10); }
    if (multi1 < multi2) { colorOutput(12); }
    cout << multi1 << "x";
    colorOutput(7);
    cout << " BrutalDmg, ";
    if (chance1 > chance2) { colorOutput(10); }
    if (chance1 < chance2) { colorOutput(12); }
    cout << chance1;
    colorOutput(7);
    cout << " Brutal Luck, ";
    if (avgDmg(id1, stat1) > avgDmg(id2, stat2)) { colorOutput(10); }
    if (avgDmg(id1, stat1) < avgDmg(id2, stat2)) { colorOutput(12); }
    cout << avgDmg(id1, stat1);
    colorOutput(7);
    cout << " Average Dmg>";
}

void colorOutput(int k) { //7 is the normal output color
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

