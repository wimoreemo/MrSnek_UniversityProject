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
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        
        int boardSizeX;
        int boardSizeY;

        bool loseFlag;
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
        
        // setters
        void setExitTrue();
        void setInput(char this_input);
        void setLoseFlag();
        void setGameStateCollision();
        void setGameStateStarvation();

        // getters
        bool getExitFlagStatus();
        char getInput();
        int getBoardSizeX();
        int getBoardSizeY();
        int getScore();
        int getBinSize();
        bool getLoseFlagStatus();
        const objPos* getFoodPos();
        void getBinElement(objPos &foodObject,int bin_index);
        int getGameStatus();
        const char* getEndMessage();
        
        // other functions
        void clearInput();
        void updateInput();
        void checkStatus();
        void checkScoreDeath();
        void generateFood(objPosArrayList* blockOff);
        int processFood(char collected_symbol);
        
        
};

#endif