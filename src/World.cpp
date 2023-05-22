#include "World.h"
#include "Info.h"

//Default Constructor
World::World() {
    worldDifficulty = 0;
    tileLength = 0;
    areaLength = 0;
}

//Destructor
World::~World() {

}

//Overload Constructor
World::World(int difficulty) {
    worldDifficulty = difficulty;
    tileLength = 0;
    areaLength = 0;
}

//Accessor Functions
float World::getTile(int i, int ii) const {
    return tiles[i][ii];
}

int World::getArea(int i, int ii) const {
    return areas[i][ii];
}

int World::getDifficulty() const {
    return worldDifficulty;
}

int World::getTileLength() const {
    return tileLength;
}

int World::getAreaLength() const {
    return areaLength;
}

//Mutator Functions
void World::setEntireTile(int i, float data[8]) {
    tiles[i][0] = data[0];
    tiles[i][1] = data[1];
    tiles[i][2] = data[2];
    tiles[i][3] = data[3];
    tiles[i][4] = data[4];
    tiles[i][5] = data[5];
    tiles[i][6] = data[6];
    tiles[i][7] = data[7];
}

void World::setTile(int i, int ii, float data) {
    tiles[i][ii] = data;
}

void World::setArea(int i, int x, int y, int id) {
    areas[i][0] = x;
    areas[i][1] = y;
    areas[i][2] = id;
}

void World::setDifficulty(int difficulty) {
    worldDifficulty = difficulty;
}

void World::increaseTileLength(int increment) {
    tileLength += increment;
}

void World::increaseAreaLength(int increment) {
    areaLength += increment;
}

//Other Functions
void World::generateTiles(int x, int y) {
    //is tile already in that direction
    bool north = false;
    bool west = false;
    bool south = false;
    bool east = false;

    for (int i=0; i<tileLength; i++) {
        if (tiles[i][0] == x && tiles[i][1] == y-1) {north = true;}
        if (tiles[i][0] == x && tiles[i][1] == y+1) {south = true;}
        if (tiles[i][0] == x-1 && tiles[i][1] == y) {west = true;}
        if (tiles[i][0] == x+1 && tiles[i][1] == y) {east = true;}
    }

    int healthPoints;
    int typeId;
    int lootTier;

    if (north == false) {
        tiles[tileLength][0] = x;
        tiles[tileLength][1] = y-1;
        if (randNumb(1, 100) <= HOSTILE_CHANCE[areaId(x, y-1)]) {
            typeId = AREA_ENEMY[areaId(x, y-1)][randNumb(0, ENEMY_COUNT[areaId(x, y-1)]-1)];
            healthPoints = randNumb(ENEMY_HP_MIN[typeId], ENEMY_HP_MAX[typeId]);
            tiles[tileLength][2] = 2;
            tiles[tileLength][3] = typeId;
            tiles[tileLength][4] = ENEMY_LOOT[typeId];
            tiles[tileLength][5] = healthPoints;
            tiles[tileLength][6] = healthPoints;
            tiles[tileLength][7] = randNumb(ENEMY_ATTACK_MIN[typeId], ENEMY_ATTACK_MAX[typeId]);

        } else if (randNumb(1, 100) <= LOOT_CHANCE[areaId(x, y-1)]) {
            lootTier = AREA_LOOT[areaId(x, y-1)];
            tiles[tileLength][2] = 3;
            tiles[tileLength][3] = lootTier;
            if (GOLD_REWARD[lootTier][0] == -1) {
                tiles[tileLength][4] = 1;
                tiles[tileLength][5] = WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)];
                tiles[tileLength][6] = randNumb(0, 8);
            } else if (WEAPON_REWARD[lootTier][0] == -1) {
                tiles[tileLength][4] = 0;
                tiles[tileLength][5] = randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]);
            } else {
                if (randNumb(0, 1) == 0) {
                    tiles[tileLength][4] = 0;
                    tiles[tileLength][5] = randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]);
                } else {
                    tiles[tileLength][4] = 1;
                    tiles[tileLength][5] = WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)];
                    tiles[tileLength][6] = randNumb(0, 8);
                }
            }

        } else if (randNumb(1, 100) <= TRAP_CHANCE[areaId(x, y-1)]) {
            typeId = AREA_TRAP[areaId(x, y-1)][randNumb(0, TRAP_COUNT[areaId(x, y-1)]-1)];
            healthPoints = randNumb(TRAP_HP_MIN[typeId], TRAP_HP_MAX[typeId]);
            tiles[tileLength][2] = 1;
            tiles[tileLength][3] = typeId;
            tiles[tileLength][4] = TRAP_LOOT[typeId];
            tiles[tileLength][5] = healthPoints;
            tiles[tileLength][6] = healthPoints;
            tiles[tileLength][7] = randNumb(TRAP_ATTACK_MIN[typeId], TRAP_ATTACK_MAX[typeId]);


        } else {
            tiles[tileLength][2] = 0;
        }
        tileLength++;
    }

    if (south == false) {
        tiles[tileLength][0] = x;
        tiles[tileLength][1] = y+1;
        if (randNumb(1, 100) <= HOSTILE_CHANCE[areaId(x, y+1)]) {
            typeId = AREA_ENEMY[areaId(x, y+1)][randNumb(0, ENEMY_COUNT[areaId(x, y+1)]-1)];
            healthPoints = randNumb(ENEMY_HP_MIN[typeId], ENEMY_HP_MAX[typeId]);
            tiles[tileLength][2] = 2;
            tiles[tileLength][3] = typeId;
            tiles[tileLength][4] = ENEMY_LOOT[typeId];
            tiles[tileLength][5] = healthPoints;
            tiles[tileLength][6] = healthPoints;
            tiles[tileLength][7] = randNumb(ENEMY_ATTACK_MIN[typeId], ENEMY_ATTACK_MAX[typeId]);

        } else if (randNumb(1, 100) <= LOOT_CHANCE[areaId(x, y+1)]) {
            lootTier = AREA_LOOT[areaId(x, y+1)];
            tiles[tileLength][2] = 3;
            tiles[tileLength][3] = lootTier;
            if (GOLD_REWARD[lootTier][0] == -1) {
                tiles[tileLength][4] = 1;
                tiles[tileLength][5] = WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)];
                tiles[tileLength][6] = randNumb(0, 8);
            } else if (WEAPON_REWARD[lootTier][0] == -1) {
                tiles[tileLength][4] = 0;
                tiles[tileLength][5] = randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]);
            } else {
                if (randNumb(0, 1) == 0) {
                    tiles[tileLength][4] = 0;
                    tiles[tileLength][5] = randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]);
                } else {
                    tiles[tileLength][4] = 1;
                    tiles[tileLength][5] = WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)];
                    tiles[tileLength][6] = randNumb(0, 8);
                }
            }

        } else if (randNumb(1, 100) <= TRAP_CHANCE[areaId(x, y+1)]) {
            typeId = AREA_TRAP[areaId(x, y+1)][randNumb(0, TRAP_COUNT[areaId(x, y+1)]-1)];
            healthPoints = randNumb(TRAP_HP_MIN[typeId], TRAP_HP_MAX[typeId]);
            tiles[tileLength][2] = 1;
            tiles[tileLength][3] = typeId;
            tiles[tileLength][4] = TRAP_LOOT[typeId];
            tiles[tileLength][5] = healthPoints;
            tiles[tileLength][6] = healthPoints;
            tiles[tileLength][7] = randNumb(TRAP_ATTACK_MIN[typeId], TRAP_ATTACK_MAX[typeId]);

        } else {
            tiles[tileLength][2] = 0;
        }
        tileLength++;
    }

    if (west == false) {
        tiles[tileLength][0] = x-1;
        tiles[tileLength][1] = y;
        if (randNumb(1, 100) <= HOSTILE_CHANCE[areaId(x-1, y)]) {
            typeId = AREA_ENEMY[areaId(x-1, y)][randNumb(0, ENEMY_COUNT[areaId(x-1, y)]-1)];
            healthPoints = randNumb(ENEMY_HP_MIN[typeId], ENEMY_HP_MAX[typeId]);
            tiles[tileLength][2] = 2;
            tiles[tileLength][3] = typeId;
            tiles[tileLength][4] = ENEMY_LOOT[typeId];
            tiles[tileLength][5] = healthPoints;
            tiles[tileLength][6] = healthPoints;
            tiles[tileLength][7] = randNumb(ENEMY_ATTACK_MIN[typeId], ENEMY_ATTACK_MAX[typeId]);

        } else if (randNumb(1, 100) <= LOOT_CHANCE[areaId(x-1, y)]) {
            lootTier = AREA_LOOT[areaId(x-1, y)];
            tiles[tileLength][2] = 3;
            tiles[tileLength][3] = lootTier;
            if (GOLD_REWARD[lootTier][0] == -1) {
                tiles[tileLength][4] = 1;
                tiles[tileLength][5] = WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)];
                tiles[tileLength][6] = randNumb(0, 8);
            } else if (WEAPON_REWARD[lootTier][0] == -1) {
                tiles[tileLength][4] = 0;
                tiles[tileLength][5] = randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]);
            } else {
                if (randNumb(0, 1) == 0) {
                    tiles[tileLength][4] = 0;
                    tiles[tileLength][5] = randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]);
                } else {
                    tiles[tileLength][4] = 1;
                    tiles[tileLength][5] = WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)];
                    tiles[tileLength][6] = randNumb(0, 8);
                }
            }

        } else if (randNumb(1, 100) <= TRAP_CHANCE[areaId(x-1, y)]) {
            typeId = AREA_TRAP[areaId(x-1, y)][randNumb(0, TRAP_COUNT[areaId(x-1, y)]-1)];
            healthPoints = randNumb(TRAP_HP_MIN[typeId], TRAP_HP_MAX[typeId]);
            tiles[tileLength][2] = 1;
            tiles[tileLength][3] = typeId;
            tiles[tileLength][4] = TRAP_LOOT[typeId];
            tiles[tileLength][5] = healthPoints;
            tiles[tileLength][6] = healthPoints;
            tiles[tileLength][7] = randNumb(TRAP_ATTACK_MIN[typeId], TRAP_ATTACK_MAX[typeId]);


        } else {
            tiles[tileLength][2] = 0;
        }
        tileLength++;
    }

    if (east == false) {
        tiles[tileLength][0] = x+1;
        tiles[tileLength][1] = y;
        if (randNumb(1, 100) <= HOSTILE_CHANCE[areaId(x+1, y)]) {
            typeId = AREA_ENEMY[areaId(x+1, y)][randNumb(0, ENEMY_COUNT[areaId(x+1, y)]-1)];
            healthPoints = randNumb(ENEMY_HP_MIN[typeId], ENEMY_HP_MAX[typeId]);
            tiles[tileLength][2] = 2;
            tiles[tileLength][3] = typeId;
            tiles[tileLength][4] = ENEMY_LOOT[typeId];
            tiles[tileLength][5] = healthPoints;
            tiles[tileLength][6] = healthPoints;
            tiles[tileLength][7] = randNumb(ENEMY_ATTACK_MIN[typeId], ENEMY_ATTACK_MAX[typeId]);

        } else if (randNumb(1, 100) <= LOOT_CHANCE[areaId(x+1, y)]) {
            lootTier = AREA_LOOT[areaId(x+1, y)];
            tiles[tileLength][2] = 3;
            tiles[tileLength][3] = lootTier;
            if (GOLD_REWARD[lootTier][0] == -1) {
                tiles[tileLength][4] = 1;
                tiles[tileLength][5] = WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)];
                tiles[tileLength][6] = randNumb(0, 8);
            } else if (WEAPON_REWARD[lootTier][0] == -1) {
                tiles[tileLength][4] = 0;
                tiles[tileLength][5] = randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]);
            } else {
                if (randNumb(0, 1) == 0) {
                    tiles[tileLength][4] = 0;
                    tiles[tileLength][5] = randNumb(GOLD_REWARD[lootTier][0], GOLD_REWARD[lootTier][1]);
                } else {
                    tiles[tileLength][4] = 1;
                    tiles[tileLength][5] = WEAPON_REWARD[lootTier][randNumb(0, WEAPON_COUNT[lootTier]-1)];
                    tiles[tileLength][6] = randNumb(0, 8);
                }
            }

        } else if (randNumb(1, 100) <= TRAP_CHANCE[areaId(x+1, y)]) {
            typeId = AREA_TRAP[areaId(x+1, y)][randNumb(0, TRAP_COUNT[areaId(x+1, y)]-1)];
            healthPoints = randNumb(TRAP_HP_MIN[typeId], TRAP_HP_MAX[typeId]);
            tiles[tileLength][2] = 1;
            tiles[tileLength][3] = typeId;
            tiles[tileLength][4] = TRAP_LOOT[typeId];
            tiles[tileLength][5] = healthPoints;
            tiles[tileLength][6] = healthPoints;
            tiles[tileLength][7] = randNumb(TRAP_ATTACK_MIN[typeId], TRAP_ATTACK_MAX[typeId]);


        } else {
            tiles[tileLength][2] = 0;
        }
        tileLength++;
    }
}

void World::discover(int x, int y, int dist) {
    generateTiles(x, y);
    if (dist >= 2) {
        generateTiles(x+1, y);
        generateTiles(x-1, y);
        generateTiles(x, y+1);
        generateTiles(x, y-1);
    }
    if (dist >= 3) {
        generateTiles(x-1, y-1);
        generateTiles(x+1, y+1);
        generateTiles(x+1, y-1);
        generateTiles(x-1, y+1);
    }
    if (dist >= 4) {
        generateTiles(x+2, y);
        generateTiles(x-2, y);
        generateTiles(x, y+2);
        generateTiles(x, y-2);
    }
}

void World::discoverAreas(int x, int y) {
    generateArea(x, y-1); //North
    generateArea(x, y+1); //South
    generateArea(x-1, y); //West
    generateArea(x+1, y); //East
    generateArea(x-1, y-1); //NorthWest
    generateArea(x+1, y-1); //NorthEast
    generateArea(x-1, y+1); //SouthWest
    generateArea(x+1, y+1); //SouthEast
}
void World::generateArea(int x, int y) {
    //Is area already in that direction
    bool discovered = false;

    for (int i=0; i<areaLength; i++) {
        if (areas[i][0] == x && areas[i][1] == y) {discovered = true;}
    }

    if (discovered == false) {
        int areaId = randNumb(0, 2);
        areas[areaLength][0] = x;
        areas[areaLength][1] = y;
        areas[areaLength][2] = areaId;
        areaLength++;
        if (AREA_BOSS[areaId] >= 0) {
            int bossId = AREA_BOSS[areaId];
            int healthPoints = randNumb(BOSS_HP_MIN[bossId], BOSS_HP_MAX[bossId]);
            tiles[tileLength][0] = areaXToTile(x)+randNumb(0, 24);
            tiles[tileLength][1] = areaYToTile(y)+randNumb(0, 24);
            tiles[tileLength][2] = 4;
            tiles[tileLength][3] = bossId;
            tiles[tileLength][4] = BOSS_LOOT[bossId];
            tiles[tileLength][5] = healthPoints;
            tiles[tileLength][6] = healthPoints;
            tiles[tileLength][7] = randNumb(BOSS_ATTACK_MIN[bossId], BOSS_ATTACK_MAX[bossId]);
            tileLength++;
        }
    }
}

int World::areaNumber(int x, int y) {
    for (int i=0; i<areaLength; i++) {
        if (areas[i][0] == areaX(x) && areas[i][1] == areaY(y)) {
            return i;
        }
    }
}

int World::areaId(int x, int y) {
    return areas[areaNumber(x, y)][2];
}

int World::tileNumber(int x, int y) {
    for (int i=0; i<tileLength; i++) {
        if (tiles[i][0] == x && tiles[i][1] == y) {
            return i;
        }
    }
}

void World::printMap(int x, int y, int width, int height) {
    //if tile has been defined yet
    bool unknownTile = true;

    //walls
    char top_left = 201;
    char top_right = 187;
    char bottom_left = 200;
    char bottom_right = 188;
    char top_bottom = 205;
    char left_right = 186;

    cout << top_left;
    for (int i=1; i<=width; i++) {
        cout << top_bottom;
    }
    cout << top_right << endl;
    for (int lengY=-(height-1)/2; lengY<=(height-1)/2; lengY++) {
        cout << left_right;
        for (int lengX=-(width-1)/2; lengX<=(width-1)/2; lengX++) {
            unknownTile = true;
            for (int i=0; i<tileLength; i++) {
                if (tiles[i][0] == x+lengX && tiles[i][1] == y+lengY) {
                    unknownTile = false;
                }
            }

            if (lengX == 0 && lengY == 0) {
                cout << PLAYER_TILE;
            } else if (unknownTile == true) {
                cout << UNKNOWN_TILE;
            } else {
                int character = tiles[tileNumber(x+lengX, y+lengY)][2];
                cout << TILE_CHAR[character];
            }

            if (lengX == (width-1)/2) {
                cout << left_right << endl;
            }
        }
    }
    cout << bottom_left;
    for (int i=1; i<=width; i++) {
        cout << top_bottom;
    }
    cout << bottom_right << endl;
}
