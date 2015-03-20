#include "shape2D.h"

void Shape2D::init_vertices(Vector2D v[],int n)
{
    n_vertices=n;
    for(int i=0;i<n;i++)
    vertices[i]=v[i];
}

void Shape2D::add_vector(Vector2D &v)
{
    for(int i=0;i<n_vertices;i++)
    vertices[i].add(v);
}

int Shape2D::get_num()
{
    return n_vertices;
}

Shape2D::Shape2D(Vector2D v[],int n)
{
    init_vertices(v,n);
}

Vector2D Shape2D::get_vertice(int i)
{
    return vertices[i];
}

Projection2D Shape2D::project(Vector2D &axis)
{
    float min,max;
    min=max=vertices[0].dotproduct(axis);

    for(int i=1;i<n_vertices;i++)
    {
        float val=vertices[i].dotproduct(axis);
        if(val<min)
        min=val;
        if(val>max)
        max=val;
    }

    return Projection2D(min,max);
}

void Shape2D::get_axes(Vector2D v[],int &n)
{
    n=n_vertices;

    for(int i=0;i<n_vertices-1;i++)
    {

        Vector2D aux;
        aux=vertices[i].result_substract(vertices[i+1]);

        v[i]=aux.perp();
    }

    Vector2D aux;
    aux=vertices[n-1].result_substract(vertices[0]);
    v[n-1]=aux.perp();
}

Vector2D Shape2D::get_center()
{
    float x1=0.f,y1=0.f,val;
    float area=0.0f;


    if(n_vertices<=3)
    {
        for(int i=0;i<n_vertices;i++)
        {x1+=vertices[i].get_x();
        y1+=vertices[i].get_y();}

        return Vector2D(x1/n_vertices,y1/n_vertices);
    }

    for(int i=0;i<n_vertices-1;i++)
    {
        val=(vertices[i].get_x()*vertices[i+1].get_y()-vertices[i].get_y()*vertices[i+1].get_x());

        x1+=(vertices[i].get_x()+vertices[i+1].get_x())*val;
        y1+=(vertices[i].get_y()+vertices[i+1].get_y())*val;
        area+=val;
    }

    val=(vertices[n_vertices-1].get_x()*vertices[0].get_y()-vertices[n_vertices-1].get_y()*vertices[0].get_x());
    x1+=(vertices[n_vertices-1].get_x()+vertices[0].get_x())*val;
    y1+=(vertices[n_vertices-1].get_y()+vertices[0].get_y())*val;
    area+=val;

    area/=2.f;
    x1*=1/(6*area);
    y1*=1/(6*area);

    return Vector2D(x1,y1);
}

void Shape2D::rotate_around_point(Vector2D &p,float angle)
{
    for(int i=0;i<n_vertices;i++)
    vertices[i].rotate_around_point(p,angle);
}

Shape2D Shape2D::get_aabb()
{
    float minX,minY,maxX,maxY;
    minX=minY=0x3f3f3f3f;
    maxX=maxY=0.0f;

    for(int i=0;i<n_vertices;i++)
    {
        float x1=vertices[i].get_x(),y1=vertices[i].get_y();

        if(x1<minX)
        minX=x1;
        if(x1>maxX)
        maxX=x1;

        if(y1<minY)
        minY=y1;
        if(y1>maxY)
        maxY=y1;
    }

    Vector2D pts[2]={Vector2D(minX,minY),Vector2D(maxX,maxY)};
    return Shape2D(pts,2);
}

bool Shape2D::aabb_overlap(Shape2D *shape)
{
    Shape2D b1=get_aabb(),b2=shape->get_aabb();

    Vector2D v1,v2,s1,s2;
    v1=b1.get_vertice(0);
    v2=b1.get_vertice(1);
    s1=b2.get_vertice(0);
    s2=b2.get_vertice(1);


    bool x_overlap= ((s1.get_x()<=v2.get_x() && s1.get_x()>=v1.get_x())||
                    (v1.get_x()<=s2.get_x() && v1.get_x()>=s1.get_x()));

    bool y_overlap= ((s1.get_y()<=v2.get_y() && s1.get_y()>=v1.get_y())||
                     (v1.get_y()<=s2.get_y() && v1.get_y()>=s1.get_y()));

    return (x_overlap && y_overlap);
}
