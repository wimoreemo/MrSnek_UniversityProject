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
    snek->movePlayer();


}

void DrawScreen(void)
{
    MacUILib_clearScreen();   
    
    MacUILib_printf("%d, %d, %c\n",(gameData->getFoodPos()[0]).x, (gameData->getFoodPos()[0]).y, (gameData->getFoodPos()[0]).symbol);
    MacUILib_printf("%d, %d, %c\n",(gameData->getFoodPos()[1]).x, (gameData->getFoodPos()[1]).y, (gameData->getFoodPos()[1]).symbol);
    MacUILib_printf("%d, %d, %c\n",(gameData->getFoodPos()[2]).x, (gameData->getFoodPos()[2]).y, (gameData->getFoodPos()[2]).symbol);
    MacUILib_printf("%d, %d, %c\n",(gameData->getFoodPos()[3]).x, (gameData->getFoodPos()[3]).y, (gameData->getFoodPos()[3]).symbol);
    MacUILib_printf("%d, %d, %c\n",(gameData->getFoodPos()[4]).x, (gameData->getFoodPos()[4]).y, (gameData->getFoodPos()[4]).symbol);
    MacUILib_printf("%d\n", gameData->getBinSize());
    

    //MacUILib_printf("###################\n");
    int x;
    int y;
    int i;
    char playerSymbol;
    for(y = -1; y <= gameData->getBoardSizeY(); y++)
    {
        // 16 17 18 19
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

    //MacUILib_printf("###################\n"); 

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
