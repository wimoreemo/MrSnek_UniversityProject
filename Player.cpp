#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Initialize the playerPosList member (soon to be changed to an objPosArrayList) using board size
    //playerPosList.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList = new objPosArrayList();
    objPos tempValue(4, 4, '@');
    playerPosList->insertTail(tempValue);
    

}

Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPosList()
{
    // return the reference to the playerPosList array list

    return playerPosList;
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

void Player::growPlayer()
{
    // PPA3 Finite State Machine logic
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

void Player::trimPlayer(int trimLength)
{
    for(int i = 0; i < trimLength; i++)
    {
        playerPosList->removeTail();
    }
}

bool Player::checkSelfCollision()
{
    objPos playerHead;
    objPos playerBody;
    playerPosList->getHeadElement(playerHead);
    for(int j = 1 ; j < (playerPosList->getSize()) ; j++)
    {
        playerPosList->getElement(playerBody,j);

        if(playerHead.x == playerBody.x && playerHead.y == playerBody.y)
        {
            mainGameMechsRef->setExitTrue();
        }
    }
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


char Player::getSymbol(int xPos, int yPos) 
{

    // Finds the symbol of the player at a given coordinate
    // This is useful for arrayList character, since there are multiple characters across the gameboard
    // If no player instance at that coordinate, returns NULL
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

