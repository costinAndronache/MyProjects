#ifndef VISUALCOLLIDE_H
    #define VISUALCOLLIDE_H

#include "VisualEntity.h"
#include "shape2D.h"
#include "utilities.h"
class VisualCollide : public VisualEntity
{
protected:
    Shape2D BoundingBox;
    void set_box_after_position();
    void set_position_after_box();
public:
    VisualCollide(int posx,int posy,int s,int l, int lstart, int fdelay,ResourceBank *pRBank);
    VisualCollide(){}


    bool check_shape(Shape2D *pshape);
    virtual bool resolve_static(Shape2D *pshape);
    Shape2D *get_shape();

    void set_drawing_basics(int posx,int posy,int s,int l, int lstart, int fdelay,ResourceBank *pRBank);
    void add_x(int val);
    void add_y(int val);

};
#endif // VISUALCOLLIDE_H
