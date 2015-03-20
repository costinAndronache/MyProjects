#include "DrawUtils.h"

void draw_shape(SDL_Surface *screen,Shape2D *shape,int r,int g,int b)
{
    Sint16 vx[32],vy[32];


    {for(int i=0;i<shape->get_num();i++)
    {
        Vector2D vertice=shape->get_vertice(i);
        vx[i]=(Sint16)vertice.get_x();
        vy[i]=(Sint16)vertice.get_y();
    }
    polygonRGBA(screen,vx,vy,shape->get_num(),r,g,b,240);
    }

}

void draw_shape_filled(SDL_Surface *screen,Shape2D *shape,int r,int g,int b)
{
    Sint16 vx[32],vy[32];

    if(shape->get_num()>=3)
    {for(int i=0;i<shape->get_num();i++)
    {
        Vector2D vertice=shape->get_vertice(i);
        vx[i]=(Sint16)vertice.get_x();
        vy[i]=(Sint16)vertice.get_y();
    }

    filledPolygonRGBA(screen,vx,vy,shape->get_num(),r,g,b,240);
    }
        else
    {
        Vector2D v1=shape->get_vertice(0),v2=shape->get_vertice(1);

        lineRGBA(screen,(Sint16)v1.get_x(),(Sint16)v1.get_y(),(Sint16)v2.get_x(),(Sint16)v2.get_y(),
                 r,g,b,240);
    }

}
