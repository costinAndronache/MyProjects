#include "../Headers/CTerrainMatrix.h"

extern void exit_error(char message[]);

#define ALPHA_BLOCK 57
void CTerrainMatrix::clear()
{
    for(int i=0;i<n_Lines;i++)
        for(int j=0;j<n_Columns;j++)
        matrix[i][j]=EMPTY;
}
void CTerrainMatrix::drawOnRenderer(SDL_Renderer *renderer)
{

    for(int i=0;i<n_Lines;i++)
        for(int j=0;j<n_Columns;j++)
    {


        switch(matrix[i][j])
        {
     case BLOCK_RED:
        SDL_SetRenderDrawColor(renderer,119,136,153,ALPHA_BLOCK);
        break;
     case BLOCK_GREEN:
                SDL_SetRenderDrawColor(renderer,84,84,84,ALPHA_BLOCK);
                break;
     case BLOCK_BLUE:
                SDL_SetRenderDrawColor(renderer,192,192,192,ALPHA_BLOCK);
                break;
     case BLOCK_FOOD:
         SDL_SetRenderDrawColor(renderer,255,255,0,255);
         break;
     case BLOCK_SNAKE1:
        SDL_SetRenderDrawColor(renderer,125,125,0,255);
                break;
     case BLOCK_SNAKE2:
        SDL_SetRenderDrawColor(renderer,0,125,125,255);
        break;
     default:
                    SDL_SetRenderDrawColor(renderer,0,0,0,255);
                    break;
        }

    SDL_Rect my_Rect;
    my_Rect.x=i*CELL_SIZE;
    my_Rect.y=j*CELL_SIZE;
    my_Rect.w=my_Rect.h=CELL_SIZE;
    SDL_RenderFillRect(renderer,&my_Rect);
   }


}

