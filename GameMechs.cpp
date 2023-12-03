#include "GameMechs.h"
#include "MacUILib.h"

// constructors
GameMechs::GameMechs()
{
    input = '\0';

    boardSizeX = 30;
    boardSizeY = 15;

    exitFlag = false;
    loseFlag = false;

    score = 0;

    arraySize = ARRAYSIZE;
    binSize = 0;
    itemBin = new objPos[arraySize];

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';

    boardSizeX = boardX;
    boardSizeY = boardY;

    exitFlag = false;
    loseFlag = false;

    score = 0;

    arraySize = ARRAYSIZE;
    binSize = 0;
    itemBin = new objPos[arraySize];

}

// do you need a destructor?
GameMechs::~GameMechs()
{
    delete itemBin;
}

// getter functions
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

const objPos* GameMechs::getFoodPos()
{
    return itemBin;
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

int GameMechs::getBinSize()
{
    return binSize;
}

/*int GameMechs::get_Score(char food_collected)
{
    int points;
    switch(food_collected)
        {
            case '*':
                points = 10; 
                break;
            case '?':
                points = -30;
                break;
            case '$':
                points = 50;
                break;
        }
    return points;
}*/

void GameMechs::getBinElement(objPos &foodObject, int bin_index)
{
    foodObject.setObjPos(itemBin[bin_index]);
}

// setter functions
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = MacUILib_getChar();
}

void GameMechs::setScore(int input_score)
{
    score = input_score;
}

// other functions
void GameMechs::updateInput()
{
    if(MacUILib_hasChar() == 1)
    {
        input = MacUILib_getChar();
    }
}

void GameMechs::clearInput()
{
    input = '\0';
}

void GameMechs::checkStatus()
{
    if(input == ((char)27))
    {
        exitFlag = 1;
    }
}

int GameMechs::processFood(char collected_symbol)
{
    int trim;
    switch(collected_symbol)
        {
            case '*':
                trim = 0;
                break;
            case '?':
                trim = 3;
                break;
            case '$':
                trim = 1;
                break;
            default:
                trim = 1;
        }
    return trim;
}

void GameMechs::generateFood(objPosArrayList* blockOff)
{

    if(arraySize <= (boardSizeX * boardSizeY) - blockOff->getSize() - 3 && arraySize != binSize)
    {
        binSize = arraySize;
    }
    else if(arraySize > (boardSizeX * boardSizeY) - blockOff->getSize() - 3)
    {
        binSize = (boardSizeX * boardSizeY) - blockOff->getSize() - 3;
    } 
    else if((boardSizeX * boardSizeY) - blockOff->getSize() <= 3)
    {
        binSize = 1;
    }

    int random_num_x;
    int random_num_y;
    char random_symbol;

    srand(time(NULL));

    char food_symbols_string[] = "*$?";
    int str_len;
    int max_rand_symbols = 3;
    for(str_len = 0;food_symbols_string[str_len]!= '\0';str_len++);

    int generation_flag = 1;

    int m = blockOff->getSize();

    objPos tempObj;
    
    int i,j,k;
    for(i = 0 ; i < binSize ; i++)
    {
        
        do
        {
            generation_flag = 0;

            random_num_x = rand() % (boardSizeX-1);
            random_num_y = rand() % (boardSizeY-1);
            random_symbol = food_symbols_string[(rand() % (str_len))];


            for(k = 0; k < m ; k++)
            {
                blockOff->getElement(tempObj,k);
                if(random_num_x == tempObj.x && random_num_y == tempObj.y) generation_flag = 1;
            }
            

           
            for(j=0; j < i; j++)
            {
                if((random_num_x == itemBin[j].x)||(random_num_y == itemBin[j].y))
                {
                    generation_flag = 1;
                }

                if(j >= max_rand_symbols)
                {
                    random_symbol = '*';
                }
            }
            

            
        } while(generation_flag == 1);
        itemBin[i].x = random_num_x;
        itemBin[i].y = random_num_y;
        itemBin[i].symbol = random_symbol;
    }

}




