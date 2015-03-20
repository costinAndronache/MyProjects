#ifndef CBLOCKMANAGER_H
    #define CBLOCKMANAGER_H

#include <cstdlib>
#include "..//Headers//CTerrainMatrix.h"



class CBlockManager
{

    simple_point blockVector[MAX_BLOCK_ITEMS];
    char blockColors[MAX_BLOCK_ITEMS];
    unsigned int numberOfBlocks;


    CTerrainMatrix *mTerrainMatrix;
public:
    CBlockManager(CTerrainMatrix *);
    void populateTerrainMatrix();
    void printOnTerrainMatrix();
    void clear();
    void increaseBlocksBy(unsigned int );
};
#endif // CBLOCKMANAGER_H
