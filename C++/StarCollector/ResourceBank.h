#ifndef _RESOURCE_BANK_H
    #define _RESOURCE_BANK_H

#include "SDL.h"
#include "SDL_image.h"
#define max_sheet 30
#define max_rows 10
#define max_columns 10

class ResourceBank
{
    private:
    int num_of_sheets;
    SDL_Surface *sheets[max_sheet];
    SDL_Rect sprites[max_sheet][max_rows][max_columns];

    int frames[max_sheet][max_rows];

    void initialize();
    static ResourceBank *instance;
    ResourceBank(){initialize();}

    public:
    static ResourceBank *get_instance();
    SDL_Surface *getSurface(int surface);
    SDL_Rect getSprite(int sheet,int x,int y);
    int get_frames(int sheet,int row);
};

#endif
