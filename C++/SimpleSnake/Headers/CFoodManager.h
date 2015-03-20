#ifndef CFOODMANAGER_H
    #define CFOODMANAGER_H


#include <cstdlib>
#include "..//Headers//CTerrainMatrix.h"


class CFoodManager
{

    simple_point foodVector[MAX_FOOD_ITEMS];
    int numberOfItems;

    CTerrainMatrix *m_TerrainMatrix;


public:
    CFoodManager(int NumberOfItems,CTerrainMatrix *TerrainMatrix);
    void printOnTerrain();
    void populateWithFood();


};


#endif // CFOODMANAGER_H
