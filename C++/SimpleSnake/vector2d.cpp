#include "vector2d.h"
#include "utilities.h"
#include <cmath>
void Vector2D::set_xy(float x1,float y1)
{
    x=x1;
    y=y1;
}

void Vector2D::set_x(float x1){x=x1;}
void Vector2D::set_y(float y1){y=y1;}

float Vector2D::get_x(){return x;}
float Vector2D::get_y(){return y;}

float Vector2D::modulus()
{
    return  SquareRootFloat(x*x+y*y);
}


void Vector2D::add(Vector2D &u)
{
    x+=u.get_x();
    y+=u.get_y();
}

void Vector2D::multiply(float scalar)
{
    x*=scalar;
    y*=scalar;
}

float Vector2D::dotproduct(Vector2D &u)
{
    return x*u.get_x()+y*u.get_y();
}

void Vector2D::normalize()
{
    float multp=Q_rsqrt(x*x+y*y);
    x*=multp;
    y*=multp;
}

Vector2D Vector2D::perp()
{
    Vector2D perp_normal(y,-x);

    perp_normal.normalize();
    return perp_normal;
}

void Vector2D::substract(Vector2D &u)
{
    x-=u.get_x();
    y-=u.get_y();
}

Vector2D Vector2D::result_add(Vector2D &u)
{
    float x1,y1;
    x1=x+u.get_x();
    y1=y+u.get_y();

    return Vector2D(x1,y1);
}

Vector2D Vector2D::result_substract(Vector2D &u)
{
    float x1,y1;
    x1=x-u.get_x();
    y1=y-u.get_y();

    return Vector2D(x1,y1);
}

void Vector2D::rotate_around_point(Vector2D &p,float angle)
{
    float x1,y1;
    float cosv=cos(angle),sinv=sin(angle);

    x1=cosv*(x-p.get_x())-sinv*(y-p.get_y())+p.get_x();
    y1=sinv*(x-p.get_x())+cosv*(y-p.get_y())+p.get_y();

    x=x1;
    y=y1;
}


