#ifndef PLAYER_H
    #define PLAYER_H


#include "GameActor.h"


#define max_bonus 10


class Player: public GameActor
{

    int soulscore;
    int bonusspeed,maxgravity;

public:
    Player(int x,int y,int s,int l,int lstart,int fdelay,ResourceBank *pRBank):
        GameActor(x,y,s,l,lstart,fdelay,pRBank){soulscore=0;bonusspeed=0;maxgravity=8;}
    void update(void *event,void *message);


    void update_position();
    void add_score(int v){soulscore+=v;}
    int get_score(){return soulscore;};

    void set_bonus_speed(int val){bonusspeed=val;}
    void set_maxgravity(int v){maxgravity=v;}

    bool resolve_static(Shape2D *shape);
    void escape_jump(){if(usingspeedy<0)usingspeedy=-usingspeedy;}
    bool stand_on_shape(Shape2D *shape);

};
#endif // PLAYER_H
