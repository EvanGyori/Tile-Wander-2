#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <windows.h>

using namespace std;

#ifndef WORLD_H
#define WORLD_H


class World
{
    public:
        //Default Constructor
        World();

        //Destructor
        virtual ~World();

        //Overload Constructor
        World(int);

        //Accessor Functions
        float getTile(int, int) const;
        int getArea(int, int) const;
        int getDifficulty() const;
            //Array lengths
            int getTileLength() const;
            int getAreaLength() const;

        //Mutator Functions
        void setEntireTile(int, float[8]);
        void setTile(int, int, float);
        void setArea(int, int, int, int);
        void setDifficulty(int difficulty);
        void increaseTileLength(int increment);
        void increaseAreaLength(int increment);

        //Other Functions
        void generateTiles(int x, int y);
            //generateTiles - generates tiles around one tile
        void discover(int x, int y, int dist);
            //discover - generates tiles around one tile in a distance
        void discoverAreas(int x, int y);
            //discoverAreas - generates areas around one area
        void generateArea(int x, int y);
            //generateAreas - generate an area
        int areaNumber(int x, int y);
            //areaNumber - calculates the place in the array for an area
        int areaId(int x, int y);
            //areaId - uses tiles coordinates to calculate the area and return the id
        int tileNumber(int x, int y);
            //tileNumber - calculates the place in the array for a tile
        void printMap(int x, int y, int width, int height);
            //printMap - prints the map onto the console, MUST be a odd number to center it

    protected:

    private:
        float tiles[60000][8]; // 0 - x, 1 - y, 2 - id
            //Enemy/Trap/Boss Tile 3 - typeId, 4 - loot tier, 5 - maxhp, 6 - hp, 7 - attack dmg
            //Loot Tile 3 - loot tier, 4 - loot type (0-gold, 1-weapon), 5 - value, 6 value
        int tileLength;
        int areas[1000][3]; //0 - x, 1 - y, 2 - id
        int areaLength;
        int worldDifficulty; //0 - normal, 1 - easy, 2 - hard
};

#endif // WORLD_H
