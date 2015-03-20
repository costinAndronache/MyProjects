#include "SDL_gfxPrimitives.h"
#include "Player.h"
#include "Level.h"
#include "SDL_ttf.h"

using namespace std;

Level levels[10];
const int n_levels=3;

char textlevel[6][120]=
{
    "Assets\\Level1\\Level1.txt",
    "Assets\\Level2\\Level2.txt",
    "Assets\\Level3\\Level3.txt",
    "Assets\\Level4\\Level4.txt",
    "Assets\\Level5\\Level5.txt",
    "Assets\\Level6\\Level6.txt"
};



int main(int argc,char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3|MIX_INIT_FLAC|MIX_INIT_OGG);
    TTF_Init();

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,4096);


    ResourceBank *RBank=ResourceBank::get_instance();
    Player Eddy(100,10,1,4,1,5,RBank);
    Eddy.set_basic_motion(4,16,0.5,0);


   SDL_Surface *screen=SDL_SetVideoMode(640,480,16,SDL_HWSURFACE|SDL_DOUBLEBUF);


   for(int i=0;i<n_levels;i++)
   {
       int state;

       levels[i].initialize(textlevel[i],&Eddy,screen,10*i);
       levels[i].execute(state);

       switch(state)
       {
       case 1:break;
       case -1:
        i=100;break;
        default:break;
       }

       levels[i].~Level();
   }




    Mix_CloseAudio();
    Mix_Quit();

    TTF_Quit();
    SDL_Quit();

    return 0;
}
