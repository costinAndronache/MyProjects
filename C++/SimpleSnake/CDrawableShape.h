#ifndef CDRAWABLESHAPE_H
    #define CDRAWABLESHAPE_H

#include "SDL2_gfxPrimitives.h"
#include "Geometry/shape2D.h"

struct ShapeColorInfo
{
    struct
    {
        int r,g,b;
    }outline_color,fill_color;

    bool outline_b,fill_b;
};


class CDrawableShape
{
    ShapeColorInfo m_ShapeColorInfo;
    public:
    Shape2D m_shape;

    CDrawableShape(ShapeColorInfo*,int*,int*,int);
    void changeColorInfo(ShapeColorInfo*);
    void printOnTexture(SDL_Renderer *,SDL_Texture* );
    void printOnRenderer(SDL_Renderer* );
};

#endif // CDRAWABLESHAPE_H
