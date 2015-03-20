#include "utilities.h"

float Q_rsqrt( float number )
{
        long i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        y  = number;
        i  = * ( long * ) &y;                       // evil floating point bit level hacking
        i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
        y  = * ( float * ) &i;
        y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
        y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
        y  = y * ( threehalfs - ( x2 * y * y ) );

        return y;
}

float SquareRootFloat(float number) {
    long i;
    float x, y;
    const float f = 1.5F;

    x = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = * ( float * ) &i;
    y  = y * ( f - ( x * y * y ) );
    y  = y * ( f - ( x * y * y ) );
    y  = y * ( f - ( x * y * y ) );
    return number * y;
}

Vector2D get_mtv(Shape2D *static_shape,Shape2D *dynamic_shape)
{
    float overlap=0x3f3f3f3f,oaux;
    int n_axis1,n_axis2;
    int n_static=static_shape->get_num(),n_dynamic=dynamic_shape->get_num();

    Vector2D smallest,mtv;
    Vector2D axis1[nmax],axis2[nmax];

    Projection2D p1;
    Projection2D p2;
    Projection2D save1,save2;

    static_shape->get_axes(axis1,n_axis1);
    dynamic_shape->get_axes(axis2,n_axis2);

    for(int i=0;i<n_axis1;i++)
    {
        p1=static_shape->project(axis1[i]);
        p2=dynamic_shape->project(axis1[i]);

        if(!p1.overlap(p2))
        {
            mtv.set_xy(0,0);
            return mtv;
        }
        else
        {
            if(n_static==2 || n_dynamic==2)
            oaux=p1.get_overlap_segment(p2);
           else
            oaux=p1.get_overlap_polygon(p2);
            if(oaux<overlap)
            {
                overlap=oaux;
                smallest=axis1[i];
                save1=p1;
                save2=p2;
            }
        }
    }

    for(int i=0;i<n_axis2;i++)
    {
        p1=static_shape->project(axis2[i]);
        p2=dynamic_shape->project(axis2[i]);

        if(!p1.overlap(p2))
        return Vector2D(0,0);
        else
        {
            if(n_static==2 || n_dynamic==2)
            oaux=p1.get_overlap_segment(p2);
            else
            oaux=p1.get_overlap_polygon(p2);
            if(oaux<overlap)
            {
                overlap=oaux;
                smallest=axis2[i];
                save1=p1;
                save2=p2;
            }
        }
    }

    mtv=smallest;
    mtv.multiply(overlap);

    Vector2D center_static,center_dynamic,center_v;
    center_static=static_shape->get_center();
    center_dynamic=dynamic_shape->get_center();

    center_v=center_dynamic.result_substract(center_static);

    if(mtv.dotproduct(center_v)<0.f)
    {
        mtv.multiply(-1);
    }

    return mtv;
}

