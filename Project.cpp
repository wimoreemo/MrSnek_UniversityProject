#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"



using namespace std;

#define DELAY_CONST 100000

GameMechs* gameData;
Player* snek;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(gameData->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gameData = new GameMechs(18, 8);
    snek = new Player(gameData);

    gameData->generateFood(snek->getPlayerPosList());

}

void GetInput(void)
{
    gameData->updateInput();
}

void RunLogic(void)
{
    gameData->checkStatus();
    snek->updatePlayerDir();
    snek->growPlayer();

    // Collision logic



}



/*
TODO
-Change your preprocessor constant to be named ARRAYSIZE
-Set a new integer member arraySize equal to ARRAYSIZE
-In your bin allocation line, tell it to create an array of size arraySize
-Set binSize equal to arraySize
-leave all other instances of binSize the way they are, this is our pseudo-array-length




if(arraySize <= (boardSizeX * boardSizeY) - blockOff.getSize() - 3 && arraySize != binSize)
{
    binSize = arraySize;
}
else if(arraySize > (boardSizeX * boardSizeY) - blockOff.getSize() - 3)
{
    binSize = (boardSizeX * boardSizeY) - blockOff.getSize() - 3;
} 
else if((boardSizeX * boardSizeY) - blockOff.getSize() <= 3)
{
    binSize = 1;
}




*/

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    int x;
    int y;
    int i;
    char playerSymbol;
    for(y = -1; y <= gameData->getBoardSizeY(); y++)
    {

        MacUILib_printf("#");
        for(x = 0; x <= gameData->getBoardSizeX() - 1; x++)
        {
            playerSymbol = snek->getSymbol(x, y);
            if(y < 0 || y == gameData->getBoardSizeY())
            {
                MacUILib_printf("#");
            }
            else if(playerSymbol != '\0')
            {
                MacUILib_printf("%c", playerSymbol);
            } 
            
            else
            {
                
                for(i = 0; i < gameData->getBinSize() && !(x == (gameData->getFoodPos()[i]).x && y == (gameData->getFoodPos()[i]).y); i++);

                if(i != gameData->getBinSize())
                {
                    MacUILib_printf("%c", (gameData->getFoodPos()[i]).symbol);
                }
                else
                {
                    MacUILib_printf(" ");
                }                
            }

        }
        MacUILib_printf("#\n");
    }

    

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{   
    
    MacUILib_uninit();

    delete gameData;
    delete snek;
}
