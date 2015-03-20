#ifndef FROMTOSHAPE_H
    #define FROMTOSHAPE_H

#include "shape2D.h"

class FromToShape
{
    Shape2D shape;
    Vector2D start,stop,direction;
    enum {tostop,tostart}dir;
    float speed;

    void go_to_dir();
public:

    Shape2D *get_shape(){return &shape;}
    void update();
    void set_direction(Vector2D sstart,Vector2D sstop,float sspeed);

};
#endif // FROMTOSHAPE_H
