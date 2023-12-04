#include "Player.h"


// constructors
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Initializing the playerPosList on the heap.
    playerPosList = new objPosArrayList();
    objPos tempValue(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertTail(tempValue);
}

// destructors
Player::~Player()
{
    delete playerPosList;
}

// getter functions
objPosArrayList* Player::getPlayerPosList()
{
    // Returning the reference to the playerPosList array list.
    return playerPosList;
}

char Player::getSymbol(int xPos, int yPos) 
{
    // This function finds the symbol of the player at a given coordinate.
    // This is useful for arrayList character, since there are multiple characters across the gameboard.
    // If no player instance at that coordinate, returns NULL.
    objPos tempObj;
    for(int i = 0; i < playerPosList->getSize(); i++)  
    {
        playerPosList->getElement(tempObj, i);
        if(xPos == tempObj.x && yPos == tempObj.y)
        {
            return tempObj.symbol;
        }
    }
    return 0;
    
}

char Player::getFoodCollision()
{
    objPos playerHead;
    objPos tempObj;
    playerPosList->getHeadElement(playerHead);

    for(int i = 0 ; i < (mainGameMechsRef->getBinSize()) ; i++)
    {
        mainGameMechsRef->getBinElement(tempObj, i);
        if(tempObj.x == playerHead.x && tempObj.y == playerHead.y)
        {
            mainGameMechsRef->generateFood(playerPosList);
            return tempObj.symbol;
            
        }
    }   
    return '\0';
}

// other functions
void Player::updatePlayerDir()
{  
    // Using input from mainGameMechsRef.
    // Input is always updated to the most recent value.
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

void Player::growPlayer()
{
    // PPA3 Finite State Machine logic here.
    objPos headElement;
    playerPosList->getHeadElement(headElement);
    if(myDir != STOP)
    {
        switch(myDir)
        {
            case UP:
                headElement.y--;
                if(headElement.y < 0)
                {
                    headElement.y = mainGameMechsRef->getBoardSizeY() - 1;
                }
                break;
            case DOWN:
                headElement.y++;
                if(headElement.y >= mainGameMechsRef->getBoardSizeY())
                {

                    headElement.y = 0;
                }
                break;
            case LEFT:
                headElement.x--;
                if(headElement.x < 0)
                {
                    headElement.x = mainGameMechsRef->getBoardSizeX() - 1;
                }
                break;
            case RIGHT:
                headElement.x++;
                if(headElement.x >= mainGameMechsRef->getBoardSizeX())
                {
                    headElement.x = 0;
                }
                break;
            default:
                break;
        }
    }
    playerPosList->insertHead(headElement);
}

// Function that trims snake length.
void Player::trimPlayer(int trimLength)
{
    for(int i = 0; i < trimLength; i++)
    {
        playerPosList->removeTail();
    }
}

void Player::checkSelfCollision()
{
    objPos playerHead;
    objPos playerBody;
    playerPosList->getHeadElement(playerHead);
    for(int j = 1 ; j < (playerPosList->getSize()) ; j++)
    {
        playerPosList->getElement(playerBody,j);

        if(playerHead.x == playerBody.x && playerHead.y == playerBody.y)
        {
            mainGameMechsRef->setGameStateCollision();
        }
    }
}

// Function to check whether snake has become too small (trimmed too many times due to penalty food).
void Player::checkStarvation()
{
    if(playerPosList->getSize() <= 0)
    {
        mainGameMechsRef->setGameStateStarvation();
    }
}






