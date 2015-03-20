#ifndef SHAPE2D_H
    #define SHAPE2D_H

#include "vector2d.h"
#include "projection2D.h"
#define nmax 16

class Shape2D
{
    Vector2D vertices[nmax];
    int n_vertices;
    Vector2D center;

    float area;

    void calculate_center();
    public:

    void init_vertices(Vector2D v[],int n);
    void add_vector(Vector2D &v);
    void get_axes(Vector2D v[],int &n);
    void rotate_around_point(Vector2D &p,float angle);
    Vector2D get_mtv(Shape2D *dynamic_shape);
    bool is_colliding(Shape2D *shape);

    Shape2D(Vector2D v[],int n);
    Shape2D(){n_vertices=0;}

    int get_num();
    Vector2D get_vertice(int i);
    Vector2D get_center();
    Projection2D project(Vector2D &axis);
    Shape2D get_aabb();
    bool aabb_overlap(Shape2D *shape);

};
#endif
