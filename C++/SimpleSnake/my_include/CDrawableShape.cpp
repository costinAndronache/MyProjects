#include "CDrawableShape.h"

CDrawableShape::CDrawableShape(ShapeColorInfo *p_shci,int *vx,int *vy,int N)
{
    m_ShapeColorInfo=*p_shci;
    m_shape.init_vertices(vx,vy,N);
}

void CDrawableShape::changeColorInfo(ShapeColorInfo *p_shci)
{
    m_ShapeColorInfo=*p_shci;
}

void CDrawableShape::printOnRenderer(SDL_Renderer *renderer)
{
    Sint16 vx[16],vy[16];
    Vector2D auv;
    int i;

    for(i=0;i<m_shape.get_num();i++)
    {
        auv=m_shape.get_vertice(i);
        vx[i]=auv.get_x();
        vy[i]=auv.get_y();
    }

    if(m_ShapeColorInfo.fill_b)
        filledPolygonRGBA(renderer,vx,vy,i,
                    m_ShapeColorInfo.fill_color.r,
                    m_ShapeColorInfo.fill_color.g,
                    m_ShapeColorInfo.fill_color.b,
                    254);

    if(m_ShapeColorInfo.outline_b);
        polygonRGBA(renderer,vx,vy,i,
                    m_ShapeColorInfo.outline_color.r,
                    m_ShapeColorInfo.outline_color.g,
                    m_ShapeColorInfo.outline_color.b,
                    254);

}

void CDrawableShape::printOnTexture(SDL_Renderer *renderer,SDL_Texture *texture)
{
    SDL_SetRenderTarget(renderer,texture);
    printOnRenderer(renderer);
    SDL_SetRenderTarget(renderer,NULL);
}
