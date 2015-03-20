#ifndef GAMEACTOR_H
    #define GAMEACTOR_H


#include "VisualCollide.h"
#include "Protocols.h"

class GameActor: public VisualCollide
{
protected:
    bool move_left,move_right,jump,jumping,moving,use_gravity;
    float speedx,speedy,gravity,accel; //base values

    float usingspeedx,usingspeedy,usinggravity,usingaccel; // these will take the base_values + bonuses
    void get_basic_motion();
public:
    void stop_jumping();
    void set_moving(bool value){moving=value;};
    void set_basic_motion(float sx,float sy,float gr,float acc);
    GameActor(int x,int y,int s,int l,int lstart,int fdelay,ResourceBank *pRBank):
        VisualCollide(x,y,s,l,lstart,fdelay,pRBank){usingaccel=usinggravity=usingspeedx=usingspeedy=0;}
    GameActor(){}


    void set_move_left(bool value){move_left=value;}
    void set_move_right(bool value){move_right=value;}
    void start_jumping(){jump=true;}
    void set_jumping(bool val){jumping=val;}
    void stop_moving();

    void set_speedx(float v){speedx=v;}
    void set_speedy(float v){speedy=v;}
    void set_gravity(float v){gravity=v;}
    void use_gravity_setting(bool val){use_gravity=val;}

    int get_speedx(){return speedx;}




    virtual void update(void *event=NULL,void *message=NULL)=0;


};
#endif //
