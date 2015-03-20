#include "VisualEntity.h"

VisualEntity::VisualEntity()
{
    RBank=NULL;
    x=y=loop_start=sheet=line=column=0;
    framedelay=0;
    last_called=0;
}

VisualEntity::VisualEntity(int posx,int posy,int s,int l, int lstart, int fdelay,ResourceBank *pRBank)
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
}

void VisualEntity::set_x(int px)
{
    x=px;
}

void VisualEntity::set_y(int py)
{
    y=py;
}

void VisualEntity::switch_line(int l,int ls)
{
    if(line!=l)
    {column=0;
    line=l;
    loop_start=ls;
    last_called=0;
    }
}

void VisualEntity::step_animation()
{

    if(last_called>=framedelay)
    {


        if(column==RBank->get_frames(sheet,line)-1)
            column=loop_start;
            else
                column++;

           last_called=0;
    }
    else
        last_called++;
}

void VisualEntity::draw(SDL_Surface *screen)
{
    SDL_Surface *my_sheet=RBank->getSurface(sheet);
    SDL_Rect sheet_pos=RBank->getSprite(sheet,line,column);
    SDL_Rect screen_pos={x,y,0,0,};

    SDL_BlitSurface(my_sheet,&sheet_pos,screen,&screen_pos);
}

int VisualEntity::get_x()
{
    return x;
}

int VisualEntity::get_y()
{
    return y;
}

void VisualEntity::set_drawing_basics(int posx,int posy,int s,int l, int lstart, int fdelay,ResourceBank *pRBank)
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
}
