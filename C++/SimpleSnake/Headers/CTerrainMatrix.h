#ifndef CTERRAINMATRIX_H
    #define CTERRAINMATRIX_H

    #include <cstring>
    #include "CScreenDisplay.h"

#include "SimpleSnakeDefinitions.h"
#define MAX_DIM 100

class CTerrainMatrix
{
    char matrix[MAX_DIM][MAX_DIM];
    int n_Lines, n_Columns;
public:
    CTerrainMatrix(int NLines,int NColumns){n_Lines=NLines;n_Columns=NColumns;clear();}
    void clear();

    char value_At(int i,int j){return matrix[i][j];}
    void append(int i,int j,char c){matrix[i][j]=c;}

    int getLines(){return n_Lines;}
    int getColumns(){return n_Columns;}
    void drawOnRenderer(SDL_Renderer *);
};
#endif // CTERRAINMATRIX_H
