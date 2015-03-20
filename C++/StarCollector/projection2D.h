#ifndef PROJECTION2D_H
    #define PROJECTION2D_H



class Projection2D
{
    float min,max;

    public:

    Projection2D(float min1,float max1);
    Projection2D(){min=max=0.0f;}

    void set(float min1,float max1);

    void set_min(float min1);
    void set_max(float max1);

    float get_min();
    float get_max();

    bool overlap(Projection2D &p);
    float get_overlap_polygon(Projection2D &p);
    float get_overlap_segment(Projection2D &p);
};
#endif
