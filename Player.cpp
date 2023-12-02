#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Initialize the playerPos member (soon to be changed to an objPosArrayList) using board size
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

}


Player::~Player()
{
    // There are no heap members yet, but there will be later
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos array list

    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    // Uses input from mainGameMechsRef
    // Input should always be updated to the most recent input
    switch(mainGameMechsRef->getInput())
    {
        case 'w':    
            if(myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        case 'a':
            if(myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
        case 's':
            if(myDir != UP)
            {
                myDir = DOWN;
            }
            break;
        case 'd':
            if(myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;  
        default:
            break;
    } 
       
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    switch(myDir)
    {
        case UP:
        playerPos.y--;
            if(playerPos.y < 0)
            {
                playerPos.y = mainGameMechsRef->getBoardSizeY() - 1;
            }
            break;
        case DOWN:
            playerPos.y++;
            if(playerPos.y >= mainGameMechsRef->getBoardSizeY())
            {

                playerPos.y = 0;
            }
            break;
        case LEFT:
            playerPos.x--;
            if(playerPos.x < 0)
            {
                playerPos.x = mainGameMechsRef->getBoardSizeY();
            }
            break;
        case RIGHT:
            playerPos.x++;
            if(playerPos.x >= mainGameMechsRef->getBoardSizeX())
            {
                playerPos.x = 0;
            }
            break;
        default:
            break;
        
    }
}

char Player::getSymbol(int xPos, int yPos) 
{

    // Finds the symbol of the player at a given coordinate
    // This is useful for arrayList character, since there are multiple characters across the gameboard
    // If no player instance at that coordinate, returns NULL
    if(xPos == playerPos.x && yPos == playerPos.y)
    {
        return playerPos.symbol;
    }
    return 0;
    
}

