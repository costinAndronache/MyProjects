#include "VisualCollide.h"

bool VisualCollide::check_shape(Shape2D *pshape)
{
    return pshape->is_colliding(&BoundingBox);

}

void VisualCollide::set_drawing_basics(int posx,int posy,int s,int l, int lstart, int fdelay,ResourceBank *pRBank)
{
    x=posx;
    y=posy;
    sheet=s;
    line=l;
    column=0;
    loop_start=lstart;
    framedelay=fdelay;
    RBank=pRBank;
    last_called=0;

    set_box_after_position();
}

void VisualCollide::set_box_after_position()
{
    Vector2D vertices[4];
    SDL_Rect sprite=RBank->getSprite(sheet,line,column);
    vertices[0].set_xy(x,y);
    vertices[1].set_xy(x+sprite.w,y);
    vertices[2].set_xy(x+sprite.w,y+sprite.h);
    vertices[3].set_xy(x,y+sprite.h);

    BoundingBox.init_vertices(vertices,4);
}

void VisualCollide::set_position_after_box()
{
    Vector2D v=BoundingBox.get_vertice(0);
    x=v.get_x();
    y=v.get_y();
}

bool VisualCollide::resolve_static(Shape2D *pshape)
{
    Vector2D mtv=pshape->get_mtv(&BoundingBox);
    if(mtv.modulus())
    {

        BoundingBox.add_vector(mtv);

    set_position_after_box();
    return true;
    }
    return false;

}

Shape2D *VisualCollide::get_shape()
{
    return &BoundingBox;
}

void VisualCollide::add_x(int val)
{
    x+=val;
    set_box_after_position();
}

void VisualCollide::add_y(int val)
{
    y+=val;
    set_box_after_position();
}

VisualCollide::VisualCollide(int posx,int posy,int s,int l, int lstart, int fdelay,ResourceBank *pRBank)
{
    x=posx;
    y=posy;
    sheet=s;
    line=l;
    column=0;
    loop_start=lstart;
    framedelay=fdelay;
    RBank=pRBank;
    last_called=0;

    set_box_after_position();
}
