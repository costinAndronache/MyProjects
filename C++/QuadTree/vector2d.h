#ifndef VECTOR2D_H
    #define VECTOR2D_H



class Vector2D
{
    private:
    float x,y;

    public:
    Vector2D(float x1,float y1){x=x1,y=y1;}
    Vector2D(){x=y=0.0f;}

    void set_xy(float x1,float y1);
    void set_x(float x1);
    void set_y(float y1);

    float get_x();
    float get_y();

    void add(Vector2D &u);
    void substract(Vector2D &u);

    Vector2D result_add(Vector2D &u);
    Vector2D result_substract(Vector2D &u);

    void multiply(float scalar);
    float dotproduct(Vector2D &u);
    void normalize();
    float modulus();

    void rotate_around_point(Vector2D &p,float angle);
    Vector2D perp();
};
#endif


