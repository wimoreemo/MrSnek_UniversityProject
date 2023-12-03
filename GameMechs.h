#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

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
        int score;

        int arraySize;
        int binSize;
        objPos* itemBin;

        enum life_state { alive,self_collision,score_death};

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

        // getters
        bool getExitFlagStatus();
        char getInput();
        int getBoardSizeX();
        int getBoardSizeY();
        int getScore();
        int getBinSize();
        bool getLoseFlagStatus();
        //void get_Score(char food_collected);
        const objPos* getFoodPos();
        void getBinElement(objPos &foodObject,int bin_index);
  
        // other functions
        void clearInput();
        void updateInput();
        void checkStatus();
        void generateFood(objPosArrayList* blockOff);
        
        
};

#endif