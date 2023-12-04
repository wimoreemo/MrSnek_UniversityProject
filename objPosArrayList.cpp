#include "objPosArrayList.h"


// constructors
objPosArrayList::objPosArrayList()
{
    sizeArray = ARRAY_MAX_CAP;
    aList = new objPos[sizeArray];
    sizeList = 0;
}

// destructor
objPosArrayList::~objPosArrayList()
{
    delete aList;
}

// getter functions
int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);   
}

// other functions
void objPosArrayList::insertHead(objPos thisPos)
{
    for(int i = sizeList; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }
    aList[0] = thisPos;
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[sizeList] = thisPos;
    sizeList++;
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i < sizeList; i++)
    {
        aList[i] = aList[i + 1];
    }
    sizeList--;
}

void objPosArrayList::removeTail()
{
    sizeList--;
}


