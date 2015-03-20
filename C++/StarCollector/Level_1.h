#ifndef LEVEL_1_H
    #define LEVEL_1_H

#include "AbstractLevel.h"
#include "Player.h"
#include "FromToActor.h"
#include "QuadTree.h"

class Level_1: public Level
{
    Player *player;
    SDL_Surface *screen;
    FromToActor Boxes[3];
    VisualCollide land,soul;
    SDL_Rect camera;
    SDL_Surface *drawbuffer;
public:
    void execute();
    void set_player(Player *pplayer){player=pplayer;}
    void set_screen(SDL_Surface *pscreen){screen=pscreen;}
    void initialize(Player *pplayer,SDL_Surface *pscreen);

};


#endif // LEVEL_1_H
