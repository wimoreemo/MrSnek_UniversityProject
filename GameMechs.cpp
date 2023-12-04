#include "GameMechs.h"

// constructors
GameMechs::GameMechs()
{
    input = '\0';

    boardSizeX = 30;
    boardSizeY = 15;

    score = 0;

    arraySize = ARRAYSIZE;
    binSize = 0;
    itemBin = new objPos[arraySize];

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';

    if(boardX <= 1 || boardY <= 1)
    {
        boardSizeX = 30;
        boardSizeY = 15;
    }
    else
    {
        boardSizeX = boardX;
        boardSizeY = boardY;
    }

    score = 0;

    arraySize = ARRAYSIZE;
    binSize = 0;
    itemBin = new objPos[arraySize];

}

// destructors
GameMechs::~GameMechs()
{
    delete itemBin;
}

// getter functions
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

void GameMechs::getBinElement(objPos &foodObject, int bin_index)
{
    foodObject.setObjPos(itemBin[bin_index]);
}

int GameMechs::getGameStatus()
{
    return gameState;
}

const char* GameMechs::getEndMessage()
{
    switch(gameState)
    {
        case 1:
            return "Goodbye!";
        case 2:
            return "Oh no! You ran into yourself!! You died!";
        case 3:
            return "Uh oh...  You're out of points!!\nSome foods TAKE AWAY points...  be careful!";
        case 4: 
            return "You let Snek starve to death! :( \nSome foods make Snek smaller!";
        default:
            break;
    }
    return "";
}

// setter functions
void GameMechs::setInput(char this_input)
{
    input = MacUILib_getChar();
}

void GameMechs::setGameStateCollision()
{
    gameState = 2;
}

void GameMechs::setGameStateStarvation()
{
    gameState = 4;
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
        gameState = 1;
    }
}

int GameMechs::processFood(char collected_symbol)
{
    int trim;
    switch(collected_symbol)
        {
            case '*':
                trim = 0;
                score += 2;
                break;
            case '?':
                trim = 3;
                score += -10;
                break;
            case '$':
                trim = 1;
                score += 6;
                break;
            default:
                trim = 1;
        }
    return trim;
}

void GameMechs::checkScoreDeath()
{
    if(score < 0) 
    {
        gameState = 3;
    }
}

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    // Default number of foods spawning per game board = 5.
    // Algorithm below used to account for the fact that lesser number of foods need to spawn as game board spaces get used up.
    // Also accounts for spawning lesser foods when game board is constructed with small length and breadth parameters.
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

    // Random generation of foods is calculated henceforth.
    int random_num_x;
    int random_num_y;
    char random_symbol;

    srand(time(NULL));

    // String to pick random characters from.
    // Can be customized and expanded later.
    char food_symbols_string[] = "*$?";

    // Variable to store template string length.
    int str_len;
    for(str_len = 0;food_symbols_string[str_len]!= '\0';str_len++);

    // Variable to store maximum random foods out of total foods spawning.
    // This is because we don't want all foods to end up spawning as special foods.
    // This ensures some amount of normal foods always spawn.
    int max_rand_symbols = 3;

    // Random location for foods generated below.
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
                if((random_num_x == itemBin[j].x)&&(random_num_y == itemBin[j].y))
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




