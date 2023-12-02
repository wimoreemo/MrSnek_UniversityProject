#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = '\0';

    boardSizeX = 30;
    boardSizeY = 15;

    exitFlag = false;
    loseFlag = false;

    int score = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';

    boardSizeX = boardX;
    boardSizeY = boardY;

    exitFlag = false;
    loseFlag = false;

    int score = 0;
}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}


bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    return input;
}

void GameMechs::updateInput()
{
    if(MacUILib_hasChar() == 1)
    {
        input = MacUILib_getChar();
    }
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = MacUILib_getChar();
}

void GameMechs::clearInput()
{
    input = '\0';
}

void GameMechs::incrementScore()
{
    score += 1;
}

void GameMechs::checkStatus()
{
    if(input == ((char)27))
    {
        exitFlag = 1;
    }
}

void GameMechs::generateFood(objPosArrayList* blockOff)
{

    int random_num_x, random_num_y;
    char random_symbol;

    int generation_flag = 1;

    int m = blockOff->getSize();

    objPos tempObj;
    
    int i,j,k;
    for(i = 0 ; i<5 ; i++)
    {
        
        do
        {
            generation_flag = 0;

            random_num_x = rand() % (boardSizeX-2);
            random_num_y = rand() % (boardSizeY-2);
            random_symbol = '*';


            for(k = 0; k < m ; k++)
            {
                blockOff->getElement(tempObj,k);
                if(random_num_x == tempObj.x && random_num_y == tempObj.y) generation_flag = 1;
            }
            

           
            for(j=0; j < i; j++)
            {
                if((random_num_x == (*itemBin[j]).x)||(random_num_y == (*itemBin[j]).y))
                {
                    generation_flag = 1;
                }

                if(i == 4)
                {
                    random_symbol = '$';
                }
            }
            

            
        } while(generation_flag == 1);
        (*itemBin[i]).x = random_num_x;
        (*itemBin[i]).y = random_num_y;
        (*itemBin[i]).symbol = random_symbol;
    }

}

objPos** GameMechs::getFoodPos()
{
    return itemBin;
}


