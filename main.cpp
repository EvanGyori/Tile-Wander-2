#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <windows.h>

#include "Players.h"
#include "World.h"
#include "Info.h"

using namespace std;

ostream& bold_on(ostream& os) {
    return os << "\e[1m";
}

ostream& bold_off(ostream& os) {
    return os << "\e[0m";
}

int main()
{
    string input;

    //Player's input info
    string name;
    int weaponId;
    int weaponStat;
    int shield;
    float maxHp;
    float hp;

    //Creates the seed
    srand( time(0) );
    cout << "seed: " << time(0) << endl;
    system("pause");
    system("cls");

    cout << "What is your name: ";
    getline(cin, name);
    system("cls");

    cout << "Hello " << name << endl;
    system("pause");
    system("cls");
    //Start menu
    do {
        do {
            cout << "Tile Wander\n";
            cout << "(0) Start Game\n";
            cout << "(1) Help\n";
            cout << "(2) Settings\n";

            getline(cin, input);
            system("cls");
        } while(input != "0" && input != "1" && input != "2");

        if (input == "1") { //help
            do {
                cout << "(1) <<<\n\n(2) Tiles\n(3) Basics\n(4) Extra\n";

                getline(cin, input);
                system("cls");
            } while(input != "1");
        } else if (input == "2") { //settings
            do {
                cout << "(1) <<<\n\n(2) Change Name\n(3) Change Font\n";

                getline(cin, input);
                system("cls");
            } while(input != "1" && input != "2" && input != "3");

            if (input == "2") { //Change name
                cout << "Whats your name: ";
                getline(cin, name);
            } else if (input == "3") { //Change font
                do {
                    cout << "(1) <<<\n\nFont: " << "\n(2) Increase Font\n(3) Decrease Font";
                    getline(cin, input);

                    if (input == "2") {

                    } else if (input == "3") {

                    }
                    system("cls");
                } while(input != "1");
                system("pause");
            }
            system("cls");
        }
    } while(input != "0");

    do { //Setup
        cout << "Choose your weapon\n";
        system("pause");
        system("cls");

        cout << "(1) Basic Sword     <6 Dmg, 2x BrutalDmg, 25 Brutal Luck, 7.5 Average Dmg>\n";
        cout << "(2) Basic Dagger    <1 Dmg, 14x BrutalDmg, 50 Brutal Luck, 7.5 Average Dmg>\n";
        cout << "(3) Basic Axe       <5 Dmg, 5x BrutalDmg, 12.5 Brutal Luck, 7.5 Average Dmg>\n";
        cout << "(4) Basic LongSword <7 Dmg, 2.3x BrutalDmg, 5 Brutal Luck, 7.455 Average Dmg>\n";

        getline(cin, input);
        system("cls");
    } while(input != "1" && input != "2" && input != "3" && input != "4");

    //Player Starting Stats and info
    if (input == "1") {weaponId = 0;}
    else if (input == "2") {weaponId = 1;}
    else if (input == "3") {weaponId = 2;}
    else if (input == "4") {weaponId = 3;}
    weaponStat = 0;
    shield = 0;
    maxHp = 100;
    hp = 100;

    //Creates player object
    Players p1(name, weaponId, weaponStat, shield, maxHp, hp);

    cout << "You choose a " << STAT_NAME[p1.getWpnStat()] << " " << WEAPON_NAME[p1.getWpnId()] << endl;
    displayWpn(p1.getWpnId(), p1.getWpnStat());
    cout << endl << endl;
    system("pause");
    system("cls");

    cout << "you were given a wooden shield\n";
    cout << "<15% Block Chance, 25% Block Dmg>\n\n";
    system("pause");
    system("cls");

    //Creating world and starting area
    World w1(0);
    float data[8] = {12, 12, 0, 0, 0, 0, 0, 0};
    w1.setEntireTile(0, data);
    w1.increaseTileLength(1);

    w1.setArea(0, 0, 0, 0);
    w1.increaseAreaLength(1);

    int x;
    int y;
    int tileId;

    do {
        x = p1.getX();
        y = p1.getY();

        w1.discoverAreas(areaX(x), areaY(y));
        w1.discover(x, y, 2);

        tileId = w1.getTile(w1.tileNumber(x, y), 2);

        if (tileId == 0) { //Empty tiles then show map
            do {
                system("cls");
                cout << bold_on << AREA_NAME[w1.areaId(x, y)] << bold_off << endl;
                w1.printMap(x, y, mapSize[0], mapSize[1]);

                cout << p1.getName() << "'s hp: " << p1.getHp() << "/" << p1.getMaxHp();
                cout << "\n(" << x << ", " << y << ")\n(" << areaX(x) << ", " << areaY(y) << ")\n";
                cin >> input;
            } while(input != "w" && input != "s" && input != "a" && input != "d");

            if (input == "w") {
            p1.setY(y-1);
            } else if (input == "d") {
            p1.setX(x+1);
            } else if (input == "s") {
            p1.setY(y+1);
            } else if (input == "a") {
            p1.setX(x-1);
            }

        } else if (tileId == 1 || tileId == 2 || tileId == 4) { //Trap or Hostile or boss Tile then show fight screen
            int enemyId = w1.getTile(w1.tileNumber(x, y), 3);
            string enemyInfo;
            string enemyName;
            if (tileId == 1) {
                enemyName = TRAP_NAME[enemyId];
                enemyInfo = TRAP_INFO[enemyId];
            } else if (tileId == 2) {
                enemyName = ENEMY_NAME[enemyId];
                enemyInfo = ENEMY_INFO[enemyId];
            } else {
                enemyName = BOSS_NAME[enemyId];
                enemyInfo = BOSS_INFO[enemyId];
            }
            do {
                //character codes for wall
                char top_left = 218;
                char top_right = 191;
                char bottom_left = 192;
                char bottom_right = 217;
                char top_bottom = 196;
                char left_right = 179;

                system("cls");
                cout << enemyName;

                //Create enemy box
                cout << endl << top_left;
                for(int i=0; i<59; i++) {
                    cout << top_bottom;
                }
                cout << top_right << endl;
                for(int i=0; i<60; i++) {
                    cout << " ";
                }

                //Enemy health and attack stats
                cout << left_right << "\r" <<left_right << "+" << w1.getTile(w1.tileNumber(x, y), 6) << "/" << w1.getTile(w1.tileNumber(x, y), 5);
                cout << "  A " << w1.getTile(w1.tileNumber(x, y), 7) << endl;
                for(int i=0; i<60; i++) {
                    cout << " ";
                }
                //Enemy info
                cout << left_right << "\r" << left_right << enemyInfo;
                cout << endl << bottom_left;
                for(int i=0; i<59; i++) {
                    cout << top_bottom;
                }
                cout << bottom_right;

                //Player box
                cout << "\n\n" << p1.getName();
                cout << endl << top_left;
                for(int i=0; i<59; i++) {
                    cout << top_bottom;
                }
                cout << top_right << endl;
                for(int i=0; i<60; i++) {
                    cout << " ";
                }
                //Player hp
                cout << left_right << "\r" << left_right << "+" << p1.getHp() << "/" << p1.getMaxHp() << endl;
                for(int i=0; i<60; i++) {
                    cout << " ";
                }
                //Player weapon
                cout << left_right << "\r" << left_right << "Wpn "; displayWpn(p1.getWpnId(), p1.getWpnStat());
                cout << endl << bottom_left;
                for(int i=0; i<59; i++) {
                    cout << top_bottom;
                }
                cout << bottom_right;
                cout << "\n\n(1) Attack\n(2) Retreat\n";

                cin >> input;
            } while(input != "1" && input != "2");

            if (input == "1") {//Attacking the tile
                system("cls");
                //player attacking tile
                int enemyId = w1.getTile(w1.tileNumber(x, y), 3);
                float dmg = attack(p1.getWpnId(), p1.getWpnStat());
                w1.setTile(w1.tileNumber(x, y), 6, w1.getTile(w1.tileNumber(x, y), 6)-dmg);

                if (w1.getTile(w1.tileNumber(x,y), 6) > 0) { //If tile survives then attack player
                    p1.setHp(p1.getHp()-w1.getTile(w1.tileNumber(x,y), 7));
                    cout << "You deal " << dmg << " dmg";
                    cout << "\nThe ";
                    cout << enemyName;
                    cout << " deals " << w1.getTile(w1.tileNumber(x,y), 7) << " dmg\n";
                    system("pause");
                    if (enemyId == 1 || enemyId == 3) {
                        w1.setTile(w1.tileNumber(x, y), 7, w1.getTile(w1.tileNumber(x, y), 7)+2);
                    }
                } else { //If tile dies then reward player
                    cout << "Your attack kills the ";
                    cout << enemyName << endl;
                    system("pause");
                    int lootTier = w1.getTile(w1.tileNumber(x, y), 4);
                    w1.setTile(w1.tileNumber(x, y), 2, 3);
                    w1.setTile(w1.tileNumber(x, y), 3, lootTier);
                    if (GOLD_REWARD[lootTier][0] == -1) {
                        w1.setTile(w1.tileNumber(x, y), 4, 1);
                        w1.setTile(w1.tileNumber(x, y), 5, WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)]);
                        w1.setTile(w1.tileNumber(x, y), 6, randNumb(0, 8));
                    } else if (WEAPON_REWARD[lootTier][0] == -1) {
                        w1.setTile(w1.tileNumber(x, y), 4, 0);
                        w1.setTile(w1.tileNumber(x, y), 5, randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]));
                    } else {
                        if (randNumb(0, 1) == 0) {
                            w1.setTile(w1.tileNumber(x, y), 4, 0);
                            w1.setTile(w1.tileNumber(x, y), 5, randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]));
                        } else {
                            w1.setTile(w1.tileNumber(x, y), 4, 1);
                            w1.setTile(w1.tileNumber(x, y), 5, WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)]);
                            w1.setTile(w1.tileNumber(x, y), 6, randNumb(0, 8));
                        }
                    }
                }
            } else if (input == "2") {//Retreat
                system("cls");
                //Damage taken from tile for retreating
                int retreatMulti = 1;
                if (w1.getTile(w1.tileNumber(x, y), 3) == 4) {retreatMulti = 2;}
                p1.setHp(p1.getHp() - w1.getTile(w1.tileNumber(x, y), 7) * retreatMulti);
                cout << "You took " << w1.getTile(w1.tileNumber(x, y), 7)*retreatMulti << " damage\n";
                system("pause");

                do {//Move away from tile to continue
                    system("cls");
                    cout << bold_on << AREA_NAME[w1.areaId(x, y)] << bold_off << endl;
                    w1.printMap(x, y, mapSize[0], mapSize[1]);

                    cout << p1.getName() << "'s hp: " << p1.getHp() << "/" << p1.getMaxHp();
                    cout << "\n(" << x << ", " << y << ")\n(" << areaX(x) << ", " << areaY(y) << ")\n";
                    cin >> input;
                } while(input != "w" && input != "s" && input != "a" && input != "d");

                if (input == "w") {
                p1.setY(y-1);
                } else if (input == "d") {
                p1.setX(x+1);
                } else if (input == "s") {
                p1.setY(y+1);
                } else if (input == "a") {
                p1.setX(x-1);
                }
            }

        } else if (tileId == 3) { //Loot Tile
            do {
                system("cls");
                cout << bold_on << AREA_NAME[w1.areaId(x, y)] << bold_off << endl;

                w1.printMap(x, y, mapSize[0], mapSize[1]);
                cout << "(" << x << ", " << y << ")\n(" << areaX(x) << ", " << areaY(y) << ")\n\n";
                if (w1.getTile(w1.tileNumber(x, y), 4) == 0) { //If the loot tile is gold
                    cout << "Scavenged " << w1.getTile(w1.tileNumber(x, y), 5) << " gold\n";
                    float data[8] = {x, y, 0, 0, 0, 0, 0, 0};
                    w1.setEntireTile(w1.tileNumber(x, y), data);
                    p1.addGold(w1.getTile(w1.tileNumber(x, y), 5));

                } else if (w1.getTile(w1.tileNumber(x, y), 4) == 1) { //If the loot tile is a weapon
                    int stat = w1.getTile(w1.tileNumber(x, y), 6);
                    int weapon = w1.getTile(w1.tileNumber(x, y), 5);
                    cout << "You scavenged a " << STAT_NAME[stat] << " " << WEAPON_NAME[weapon] << endl;
                    cout << "Scavenged Weapon "; compareWpn(weapon, stat, p1.getWpnId(), p1.getWpnStat());
                    cout << "\n\nYour Weapon "; displayWpn(p1.getWpnId(), p1.getWpnStat());
                    cout << "\n\n(1) Take Weapon\n(2) Discard Weapon\n";
                }

                cin >> input;
            } while(input != "w" && input != "s" && input != "a" && input != "d" && input != "1" && input != "2");

            if (input == "w") {
            p1.setY(y-1);
            } else if (input == "d") {
            p1.setX(x+1);
            } else if (input == "s") {
            p1.setY(y+1);
            } else if (input == "a") {
            p1.setX(x-1);
            } else if (input == "1" && w1.getTile(w1.tileNumber(x, y), 4) == 1) {//Take loot
                p1.setWpnId(w1.getTile(w1.tileNumber(x, y), 5));
                p1.setWpnStat(w1.getTile(w1.tileNumber(x, y), 6));
                float data[8] = {x, y, 0, 0, 0, 0, 0, 0};
                w1.setEntireTile(w1.tileNumber(x, y), data);
            } else if (input == "2" && w1.getTile(w1.tileNumber(x, y), 4) == 1) {//Discard loot
                float data[8] = {x, y, 0, 0, 0, 0, 0, 0};
                w1.setEntireTile(w1.tileNumber(x, y), data);
            }

        }
    } while(p1.getHp() > 0);
    //Stops running if player dies
    return 0;
}
