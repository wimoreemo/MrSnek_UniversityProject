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
    if(input == 27)
    {
        exitFlag = 1;
    }
}


