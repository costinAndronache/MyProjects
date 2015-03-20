#ifndef SHAPE2D_H
    #define SHAPE2D_H

#include "vector2d.h"
#include "projection2D.h"
#define nmax 16

class Shape2D
{
    Vector2D vertices[nmax];
    int n_vertices;

    public:

    void init_vertices(Vector2D v[],int n);
    void add_vector(Vector2D &v);
    void get_axes(Vector2D v[],int &n);
    void rotate_around_point(Vector2D &p,float angle);

    Shape2D(Vector2D v[],int n);
    Shape2D(){n_vertices=0;}

    int get_num();
    Vector2D get_vertice(int i);
    Vector2D get_center();
    Projection2D project(Vector2D &axis);

};
#endif
