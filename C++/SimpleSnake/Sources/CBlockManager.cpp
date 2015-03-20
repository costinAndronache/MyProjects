#include "../Headers/CBlockManager.h"

extern void exit_error(char message[]);

CBlockManager::CBlockManager(CTerrainMatrix *TerrainMatrix)
{
    if(!TerrainMatrix)
        exit_error("Null TerrainMatrix on initalizing block manager!");
    mTerrainMatrix=TerrainMatrix;

    for(int i=0;i<MAX_BLOCK_ITEMS;i++)
    blockVector[i]={0,0};

    numberOfBlocks=0;
}

void CBlockManager::clear()
{
    for(int i=0;i<numberOfBlocks;i++)
        {
            mTerrainMatrix->append(blockVector[i].x,blockVector[i].y,EMPTY);
            blockVector[i]={0,0};
        }
}
void CBlockManager::populateTerrainMatrix()
{
    clear();
    srand(SDL_GetTicks());

    for(int i=0;i<numberOfBlocks;i++)
    {
        do
        {
            blockVector[i].x=rand()%mTerrainMatrix->getLines();
            blockVector[i].y=rand()%mTerrainMatrix->getColumns();

        }while(mTerrainMatrix->value_At(blockVector[i].x,
                                        blockVector[i].y) != EMPTY);

        blockColors[i]=rand()%3 + 1;
    }
}

void CBlockManager::increaseBlocksBy(unsigned int byHowMuch)
{
    if(numberOfBlocks+byHowMuch>MAX_BLOCK_ITEMS)
        numberOfBlocks=MAX_BLOCK_ITEMS;
    else
        numberOfBlocks+=byHowMuch;
}

void CBlockManager::printOnTerrainMatrix()
{
    for(int i=0;i<numberOfBlocks;i++)
        mTerrainMatrix->append(blockVector[i].x,blockVector[i].y,blockColors[i]);
}
