#ifndef LEVEL_H
    #define LEVEL_H

#include "Player.h"
#include "FromToShape.h"
#include "SDL.h"
#include "DrawUtils.h"
#include "SDL_mixer.h"
#include "ResourceBank.h"
#include "TextDisplay.h"

#define max_ 60

class Level
{
    Player *player;
    SDL_Surface *screen;

    Shape2D *ground;
    Shape2D *rotating_ground;
    int degree_rotating[max_];
    FromToShape *moving_ground;
    VisualCollide *stars;
    bool alive_star[max_];

    int start_x,start_y;
    int n_ground,n_rotating_ground,n_moving_ground,n_star;

    char bg[30],ms[30];

    Mix_Music *music;
    SDL_Surface *background;

     int color;


public:
    bool initialize(char *file,Player *pplayer,SDL_Surface *pscreen,int c);
    void execute(int &state);
    ~Level();



};
#endif // LEVEL_H
