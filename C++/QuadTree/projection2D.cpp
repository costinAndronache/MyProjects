#include "projection2D.h"

void Projection2D::set(float min1,float max1)
{
    if(min1<max1)
    min=min1,max=max1;
    else
    min=max1,max=min1;
}

Projection2D::Projection2D(float min1,float max1)
{
    set(min1,max1);
}

void Projection2D::set_max(float max1)
{
    set(min,max1);
}

void Projection2D::set_min(float min1)
{
    set(min1,max);
}

float Projection2D::get_max()
{
    return max;
}

float Projection2D::get_min()
{
    return min;
}

bool Projection2D::overlap(Projection2D &p)
{
    return
    ((min<p.get_max() && p.get_min()<max)
     ||
     (p.get_min()<max && min<p.get_max()));
}

float Projection2D::get_overlap_polygon(Projection2D &p)
{


    float d1=min-p.get_max();
    float d2=p.get_min()-max;

    if(d1>0.f || d2>0.f)
    return 0.f;

    if(d1<0.f)
    d1=-d1;
    if(d2<0.f)
    d2=-d2;

    if(d1<d2)
    return d1;
    else
    return d2;
}

float Projection2D::get_overlap_segment(Projection2D &p)
{
        if(min<p.get_max() && p.get_min()<max)
            return max-p.get_min();
                    else
                        if(p.get_min()<max && min<p.get_max())
                            return p.get_max()-min;
                                else
                                    return 0.0f;

}
