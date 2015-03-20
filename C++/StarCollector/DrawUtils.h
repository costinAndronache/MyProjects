#ifndef DRAWUTILS_H
    #define DRAWUTILS_H

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "shape2D.h"

void draw_shape(SDL_Surface *screen,Shape2D *shape,int r,int g,int b);
void draw_shape_filled(SDL_Surface *screen,Shape2D *shape,int r,int g,int b);

#endif // DRAWUTILS
