#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


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

}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   
    MacUILib_printf("####################\n");
    int x;
    int y;
    int i;
    char playerSymbol;
    for(y = 0; y <= gameData->getBoardSizeY() - 1; y++)
    {
        MacUILib_printf("#");
        for(x = 0; x <= gameData->getBoardSizeX() - 1; x++)
        {
            playerSymbol = snek->getSymbol(x, y);
            if(playerSymbol != '\0')
            {
                MacUILib_printf("%c", playerSymbol);
            } 
            else 
            {
                MacUILib_printf(" ");
            }
            /*
            else
            {
                for(i = 0; i < binSize && !(x == itemBin[i].x && y == itemBin[i].y); i++);

                if(i != binSize)
                {
                    MacUILib_printf("%c", itemBin[i].symbol);
                }
                else
                {
                    MacUILib_printf(" ");
                }
            }
            */
        }
        MacUILib_printf("#\n");
    }

    MacUILib_printf("####################\n"); 

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
