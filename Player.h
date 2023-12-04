#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        // getter functions
        objPosArrayList* getPlayerPosList(); // Upgrade this in iteration 3.
        char getSymbol(int xPos, int yPos);
        char getFoodCollision();
        
        // other functions
        void updatePlayerDir();
        void growPlayer();
        void trimPlayer(int trimLength);
        void checkSelfCollision();
        void checkStarvation();

    private:
        objPosArrayList* playerPosList;    
        enum Dir myDir;

        // Reference to the Main Game Mechanisms.
        GameMechs* mainGameMechsRef;
};

#endif