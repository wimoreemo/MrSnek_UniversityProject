#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

#define BINSIZE 5


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
        int score;

        int binSize;
        objPos* itemBin;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();
        
        bool getExitFlagStatus();
        void setExitTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();
        void setLoseFlag();

        int getBoardSizeX();
        int getBoardSizeY();
        int getScore();
        int getBinSize();

        bool getLoseFlagStatus();
        void incrementScore();
        void updateInput();
        void checkStatus();

        void generateFood(objPosArrayList* blockOff);
        const objPos* getFoodPos();
  

};

#endif