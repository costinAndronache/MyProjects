#include "FromToShape.h"

void FromToShape::set_direction(Vector2D sstart,Vector2D sstop,float sspeed)
{
    speed=sspeed;
    start=sstart;
    stop=sstop;


    if(start.get_x()>stop.get_x())
    {
        Vector2D aux=start;
        start=stop;
        stop=aux;
    }
    else
        if((int)start.get_x()==(int)stop.get_x() && start.get_y()>stop.get_y())
    {Vector2D aux=start;
        start=stop;
        stop=aux;
    }

    direction=stop.result_substract(start);
    direction.normalize();

    Vector2D center=shape.get_center();

    Vector2D addv=start.result_substract(center);

    shape.add_vector(addv);


    dir=tostop;

}

void FromToShape::go_to_dir()
{
    Vector2D addv=direction;
    addv.multiply(speed);

    shape.add_vector(addv);

}
void FromToShape::update()
{
    Vector2D center=shape.get_center();
    float x=center.get_x(),y=center.get_y();
    if(dir==tostop)
    {
        if((int)start.get_x()==(int)stop.get_x())
           {

            if(y>(int)stop.get_y())
                {
                    direction.multiply(-1);
                    dir=tostart;

                    }
            else
             go_to_dir();

           }
        else
            {
               if(x>(int)stop.get_x())
               {
                   direction.multiply(-1);
                   dir=tostart;
               }
               else
                go_to_dir();
            }
    }
    else
    {
        if((int)start.get_x()==(int)stop.get_x())
           {

            if(y<(int)start.get_y())
                {
                    direction.multiply(-1);
                    dir=tostop;

                    }
            else
             go_to_dir();

           }
        else
            {
               if(x<(int)start.get_x())
               {
                   direction.multiply(-1);
                   dir=tostop;
               }
               else
                go_to_dir();
            }
    }
}
