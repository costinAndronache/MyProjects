#ifndef VISUALENTITY_H
    #define VISUALENTITY_H

#include "ResourceBank.h"

class VisualEntity
{
protected:

    ResourceBank *RBank;
    int sheet,line,column;
    Uint32 framedelay, last_called;
    int loop_start;



    int x,y;

public:

    VisualEntity();
    VisualEntity(int posx,int posy,int s,int l, int lstart, int fdelay,ResourceBank *pRBank);

    void set_x(int px);
    void set_y(int py);
    int get_x();
    int get_y();
    void switch_line(int l, int ls);

    virtual void set_drawing_basics(int posx,int posy,int s,int l, int lstart, int fdelay,ResourceBank *pRBank);


    void step_animation();
    void draw(SDL_Surface *screen);

};

#endif // VISUALENTITY_H
