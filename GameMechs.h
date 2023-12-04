#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"

#define ARRAYSIZE 5
#define FOOD_TYPES 3

using namespace std;


class GameMechs
{
    private:
        char input;
        int boardSizeX;
        int boardSizeY;
        int score = 0;

        int arraySize;
        int binSize;
        objPos* itemBin;

        int gameState = 0;

    public:
        //constructors
        GameMechs();
        GameMechs(int boardX, int boardY);

        //destructor
        ~GameMechs();

        // getters
        char getInput();
        int getBoardSizeX();
        int getBoardSizeY();
        int getScore();
        int getBinSize();
        const objPos* getFoodPos();
        void getBinElement(objPos &foodObject,int bin_index);
        int getGameStatus();
        const char* getEndMessage();
        
        // setters
        void setInput(char this_input);
        void setGameStateCollision();
        void setGameStateStarvation();
        
        // other functions
        void clearInput();
        void updateInput();
        void checkStatus();
        void checkScoreDeath();
        void generateFood(objPosArrayList* blockOff);
        int processFood(char collected_symbol);
        
        
};

#endif