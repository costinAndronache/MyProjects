#include "GameActor.h"

void GameActor::stop_jumping()
{
    jumping=false;
}

void GameActor::stop_moving()
{
    move_left=move_right=false;
}

void GameActor::set_basic_motion(float sx,float sy,float gr,float acc)
{
    speedx=sx;
    speedy=sy;
    gravity=gr;
    accel=acc;

    move_left=move_right=jump=false;
    use_gravity=jumping=true;
    //get_basic_motion();
}

void GameActor::get_basic_motion()
{
    usingspeedx=speedx;
    usingspeedy=speedy;
    usinggravity=gravity;
    usingaccel=accel;
}

