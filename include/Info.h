#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <windows.h>

using namespace std;

const int mapSize[2] = {19, 13}; //can only be odd #s

//array order is the id
//Weapons
const string WEAPON_NAME[14] = {"Basic Sword", "Basic Dagger", "Basic Axe", "Basic LongSword",
"Advanced Sword", "Advanced Dagger", "Advanced Axe", "Advanced LongSword", "Basic BattleAxe",
"Advanced BattleAxe", "Combat Sword", "Combat Dagger", "Combat Axe", "Combat LongSword"};
const float WEAPON_DMG[14] =    {6,  1,  5,    7,   8,  1,  7,  10,  12, 15, 13,  1,  12, 17};
const float WEAPON_MULTI[14] =  {2,  14, 5,    2.3, 2,  20, 5,  2.5, 3,  4,  2.5, 25, 5,  2.5};
const float WEAPON_CHANCE[14] = {25, 50, 12.5, 5,   30, 50, 14, 5,   5,  10, 30,  75, 15, 10};

//Weapon Stat Multipliers
const string STAT_NAME[9] = {"Plain", "Rusty", "Polished", "Unfortunate", "Fortunate",
"Cracked", "Broad", "Dull", "Sharp"};
const float STAT_DMG[9] =    {1, 0.8, 1.2, 1,   1,   1,   1.2, 0.8, 1.2};
const float STAT_MULTI[9] =  {1, 1,   1,   1,   1,   0.9, 1.1, 1,   1};
const float STAT_CHANCE[9] = {1, 1.1, 0.9, 0.8, 1.2, 1,   0.8, 1,   1};

//Shields
const string SHIELD_NAME[5] = {"Wooden Shield", "Tough Wooden Shield", "Metal Shield", "Tough Metal Shield", "Steel Shield"};
const float SHIELD_CHANCE[5] =  {15, 15, 35, 35, 35};
const float SHIELD_PERCENT[5] = {25, 45, 25, 45, 100};


//Tile Characters
const string TILE_NAME[5] = {"Empty", "Trap", "Hostile", "Loot", "Boss"};
const char TILE_CHAR[5] = {176, 35, 219, 35, 234};
const char UNKNOWN_TILE = 32;
const char PLAYER_TILE = 197;

//Areas
const string AREA_NAME[3] = {"Ghost Towns", "Forbidden Caverns", "Frozen Mountain Tops"};
const int TRAP_CHANCE[3] = {0, 0, 1};
const int HOSTILE_CHANCE[3] = {5, 12, 10};
const int LOOT_CHANCE[3] = {2, 4, 3};
const int AREA_LOOT[3] = {0, 0, 1};
const int ENEMY_COUNT[3] = {2, 6, 2};
const int AREA_ENEMY[3][6] = {{0, 1}, {1, 2, 3, 4, 5, 6}, {7, 8}};
const int TRAP_COUNT[3] = {0, 0, 1};
const int AREA_TRAP[3][2] = {-1, -1, 0};
const int AREA_BOSS[3] = {-1, -1, 1};

//Enemies
const string ENEMY_NAME[9] = {"Hungry Hound", "Mutated Rat", "Wolf Spider", "Huntsman Spider",
"Black Bear", "Cave Wolf", "Bat", "Yeti", "Snow Troll"};
const int ENEMY_ATTACK_MIN[9] = {3, 0, 2, 4, 7, 5, 3};
const int ENEMY_ATTACK_MAX[9] = {6, 0, 4, 6, 12, 8, 5};
const int ENEMY_HP_MIN[9] = {15, 15, 50, 25, 50, 25, 8};
const int ENEMY_HP_MAX[9] = {35, 25, 75, 40, 70, 40, 15};
const int ENEMY_LOOT[9] = {1, 1, 2, 2, 4, 2, 1};
const int ENEMY_XP[9] = {5, 3};
const string ENEMY_INFO[9] = {
"",
"+2 attack each turn", //Mutated rat
"",
"+2 attack each turn", //Huntsman spider
"Retreating causes double the dmg", //black bear
"",
"Kill 10 to summon a giant bat", //Bat
"Attacks twice", //yeti
""
};

//Enemy Traps
const string TRAP_NAME[2] = {"Arctic Wolf", "Living Wood"};
const int TRAP_ATTACK_MIN[2] = {5, 0};
const int TRAP_ATTACK_MAX[2] = {10, 0};
const int TRAP_HP_MIN[2] = {25, 10};
const int TRAP_HP_MAX[2] = {35, 10};
const int TRAP_LOOT[2] = {2, 0};
const int TRAP_XP[2] = {10};
const string TRAP_INFO[2] = {
"", ""
};

//Bosses
const string BOSS_NAME[2] = {"Giant Bat", "Ice Giant"};
const int BOSS_ATTACK_MIN[2] = {3, 10};
const int BOSS_ATTACK_MAX[2] = {5, 12};
const int BOSS_HP_MIN[2] = {100, 70};
const int BOSS_HP_MAX[2] = {130, 85};
const int BOSS_LOOT[2] = {1, 1};
const int BOSS_XP[2] = {1, 1};
const string BOSS_INFO[2] = {
"Gets a buff when low",
"Your shield is useless against the ice giant"
};

//Loot Tiers
const bool CHOOSE_REWARD[5] = {false, false, false, false, false};
const int GOLD_REWARD[5][2] = {{-1}, {1, 3}, {4, 8}, {15, 25}, {15, 20}};
const int WEAPON_COUNT[5] = {4, 4, 4, 1, -1};
const int WEAPON_REWARD[5][4] = {{0, 1, 2, 3}, {0, 1, 2, 3}, {4, 5, 6, 7}, {8}, {0}};

//Inventory Items


//Functions

//Create a random number
int randNumb(int min, int max);

//Calculate the area coordinates using the tile coordinates
int areaX(int x);
int areaY(int y);

//Calculate the top left tile coordinates of a area
int areaXToTile(int x);
int areaYToTile(int y);

//Calculate a Weapons average damage
float avgDmg(int wpnId, int wpnStat);

//Calculate a weapons damage
float dmg(int wpnId, int wpnStat);

//Calculate a weapons brutal damage multiplier
float multi(int wpnId, int wpnStat);

//Calculate a weapons brutal chance
float chance(int wpnId, int wpnStat);

//Determine the attack damage
float attack(int wpnId, int wpnStat);

//Display the stats of a weapon
void displayWpn(int wpnId, int wpnStat);

//Compares the stats of two weapons then displays the first weapon
void compareWpn(int id1, int stat1, int id2, int stat2);

//Changes the output color of text
void colorOutput(int k);
