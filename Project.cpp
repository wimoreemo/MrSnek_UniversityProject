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

    while(gameData->getGameStatus() == 0)  
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

    gameData = new GameMechs(1,2);
    snek = new Player(gameData);

    gameData->generateFood(snek->getPlayerPosList());

}

void GetInput(void)
{
    gameData->updateInput();
}

void RunLogic(void)
{
    //Check game status
    gameData->checkStatus();
    gameData->checkScoreDeath();
    snek->checkSelfCollision();
    snek->checkStarvation();


    snek->updatePlayerDir();
    snek->growPlayer();

    // Collision logic

    char collected_symbol;
    int trimLength;

    collected_symbol = snek->getFoodCollision();

    trimLength = gameData->processFood(collected_symbol);

    snek->trimPlayer(trimLength);





}

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

    if(gameData->getGameStatus() != 0)
    {
        MacUILib_printf("%s", gameData->getEndMessage());
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
