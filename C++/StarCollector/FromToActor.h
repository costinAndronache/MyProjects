#ifndef FROMTOACTOR_H
    #define FROMTOACTOR_H

#include "shape2D.h"

class FromToShape
{
    Shape2D shape;
    Vector2D start,stop,direction;
    enum {tostop,tostart}dir;

    void go_to_dir();
public:
    void update();
    void set_direction(Vector2D sstart,Vector2D sstop);

};
#endif // FROMTOACTOR_H
