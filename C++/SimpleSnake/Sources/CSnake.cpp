#include "..//Headers//CSnake.h"

extern void exit_error(char message[]);


void CSnake::changeDirection(simple_point *ppoint)
{
    //m_direction=*ppoint;

    int x1=m_direction.x, y1=m_direction.y;
    int x2=ppoint->x, y2=ppoint->y;

    if((x2 && (x2>1 || x2<-1)) || (y2 && (y2>1 || y2<-1)))
       exit_error("Improper coordinates given.\n");

    if(((x1 && !x2) || (!x1 && x2)) || ((y1 && !y2)||(!y1 && y2)))
        m_direction=*ppoint;

}

void CSnake::changeSnake(snake_struct *snk)
{
    if(snk->m_length>MAX_SNAKE_SIZE || snk->m_length<0)
        exit_error("Improper snake length, on changing the snake!");

    for(int i=0;i<snk->m_length;i++)
    {
        int x=snk->snake_vector[i].x;
        int y=snk->snake_vector[i].y;

        if(x<0 || y<0)
            exit_error("Negative coordinates, on changing the snake!");

      if((x>=m_TerrainMatrix->getLines()) ||
           y>=m_TerrainMatrix->getColumns())
            exit_error("Out of bound coordinates, on chaning the snake!");


    }

    m_snake=*snk;
    alive=true;
}
CSnake::CSnake(snake_struct *snk,simple_point *ppoint,CTerrainMatrix *TerrainMatrix)
{
    if(!TerrainMatrix)
    exit_error("Null terrain matrix on snake initialization!");
    m_TerrainMatrix=TerrainMatrix;
    alive=true;


    changeDirection(ppoint);
    changeSnake(snk);


}


void CSnake::checkStatus()
{

    int x=m_snake.snake_vector[HEAD_POS].x, y=m_snake.snake_vector[HEAD_POS].y;

    if(x>=m_TerrainMatrix->getLines() || y>=m_TerrainMatrix->getColumns())
        {
            alive=false;
            return;
        }

    if(x<0 || y<0)
        {
            alive=false;
            return;
        }

    char block=m_TerrainMatrix->value_At(x,y);
    if(block==BLOCK_FOOD)
    {
        ++m_snake.m_length;
        m_snake.snake_vector[m_snake.m_length-1]=m_snake.snake_vector[m_snake.m_length-2];
        m_TerrainMatrix->append(x,y,EMPTY);
        return;
    }

    if(block!=EMPTY || block==BLOCK_SNAKE1 || block==BLOCK_SNAKE2)
        if(m_direction.x || m_direction.y)
        alive=false;

}

void CSnake::advance()
{

    for(int i=m_snake.m_length-1;i>0;i--)
        m_snake.snake_vector[i]=m_snake.snake_vector[i-1];

    m_snake.snake_vector[HEAD_POS].x+=m_direction.x;
    m_snake.snake_vector[HEAD_POS].y+=m_direction.y;
}

void CSnake::stepInStatus()
{
    advance();
    checkStatus();
}

void CSnake::printOnTerrain(char whatsnake)
{
    if(whatsnake!=BLOCK_SNAKE1 && whatsnake!=BLOCK_SNAKE2)
        exit_error("Undefined \"whatsnake\" in printOnTerrain()");

    for(int i=0;i<m_snake.m_length;i++)
    m_TerrainMatrix->append(m_snake.snake_vector[i].x,
                            m_snake.snake_vector[i].y,
                            whatsnake);
}
