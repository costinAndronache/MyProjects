#include "../Headers/CFoodManager.h"


extern void exit_error(char message[]);

void CFoodManager::printOnTerrain(void)
{
    for(int i=0;i<numberOfItems;i++)
        m_TerrainMatrix->append(foodVector[i].x,foodVector[i].y,BLOCK_FOOD);
}
void CFoodManager::populateWithFood(void)
{

    srand(SDL_GetTicks());
    int x,y;

    for(int i=0;i<numberOfItems;i++)
        if(m_TerrainMatrix->value_At(foodVector[i].x,foodVector[i].y) != BLOCK_FOOD)
        {do
        {
            foodVector[i].x=rand()%m_TerrainMatrix->getLines();
            foodVector[i].y=rand()%m_TerrainMatrix->getColumns();

        }while(m_TerrainMatrix->value_At(foodVector[i].x,foodVector[i].y)!=EMPTY);

        printOnTerrain();
        }

}


CFoodManager::CFoodManager(int NumberOfItems,CTerrainMatrix *TerrainMatrix)
{
    if(!TerrainMatrix)
        exit_error("Null terrain matrix on food manager initialization.");
    m_TerrainMatrix=TerrainMatrix;

    if(NumberOfItems<0 || NumberOfItems>MAX_FOOD_ITEMS)
        exit_error("Number of food items out of bound in food manager initialization.");
    numberOfItems=NumberOfItems;

    foodVector[0]=foodVector[1]={0,0};
    populateWithFood();
}
