#ifndef CSNAKE_H
    #define CSNAKE_H


#include "CTerrainMatrix.h"
#define HEAD_POS 0



class CSnake
{
    snake_struct m_snake;
    simple_point m_direction;

    bool alive;

    CTerrainMatrix *m_TerrainMatrix;
    void checkStatus();
    void advance();
public:
    CSnake(snake_struct *,simple_point *,CTerrainMatrix *);
    bool isAlive(){return alive;}
    void stepInStatus();
    void changeDirection(simple_point *);
    void changeSnake(snake_struct *);
    void printOnTerrain(char what_snake);

    int getLength(){return m_snake.m_length;}

};
#endif // CSNAKE_H
