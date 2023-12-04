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

    // GameMechs parameters refer to display size (x, y)
    gameData = new GameMechs(20, 10);
    snek = new Player(gameData);

    gameData->generateFood(snek->getPlayerPosList());
}

void GetInput(void)
{
    gameData->updateInput();
}

void RunLogic(void)
{
    char collected_symbol;
    int trimLength;


    snek->updatePlayerDir();

    // Snake movement function split into growPlayer and trimPlayer in order to more efficiently control snake size
    snek->growPlayer();

    // Collision logic

    // Get symbol that the snake collided with
    collected_symbol = snek->getFoodCollision();

    // Process the symbol that the snake collided with
    // ^ Adjusts score and returns number of times to trim the player length
    trimLength = gameData->processFood(collected_symbol);

    // Trim the player length a specific number of times depending on food
    snek->trimPlayer(trimLength);

    //Check game status
    gameData->checkStatus();
    gameData->checkScoreDeath();
    snek->checkSelfCollision();
    snek->checkStarvation();



}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    MacUILib_printf("Welcome to Snek Game! ( you're Snek -> @ )\n");
    MacUILib_printf("Your score is: %d\n\n",gameData->getScore());
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
    MacUILib_printf("\nControls:\nUP    -> W\nDOWN  -> S\nLEFT  -> A\nRIGHT -> D\n\nCollect food (*) to grow! Beware special foods!\nPress Esc to quit.\n\n");
    
    // If the game is ending, print a termination message
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
