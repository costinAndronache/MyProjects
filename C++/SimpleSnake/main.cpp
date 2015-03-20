#include <iostream>
#include "Headers/CTerrainMatrix.h"
#include "CScreenDisplay.h"
#include "Headers/CSnake.h"
#include "CTimer.h"
#include "Headers/CFoodManager.h"
#include "Headers/CBlockManager.h"
using namespace std;



enum LevelState{running,over_won,over_lost,quit}myLevel;

void updateDirection(SDL_Event e,simple_point &dir)
{
    if(e.type==SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            dir.x=0,dir.y=-1;
            break;
        case SDLK_DOWN:
            dir.x=0,dir.y=1;
            break;
        case SDLK_LEFT:
            dir.x=-1,dir.y=0;
            break;
        case SDLK_RIGHT:
            dir.x=1,dir.y=0;
            break;
        default:
            break;
        }
    }

}

CTerrainMatrix my_TerrainMatrix(WIDTH/CELL_SIZE,HEIGHT/CELL_SIZE);
int main(int argc,char *argv[])
{

    levelInfo Levels[]={{125,16,32},{55,48,32},{25,96,48}};
    //cout << (&my_TerrainMatrix)->getLines()<< endl;

    SDL_Init(SDL_INIT_VIDEO);
    CScreenDisplay my_Screen(WIDTH,HEIGHT,SDL_WINDOWPOS_CENTERED);



    snake_struct snk1={{{0,0}},1};
    simple_point direction={0,0},basic_direction={0,0};

    CSnake mySnake(&snk1,&direction,&my_TerrainMatrix);
    CFoodManager myFoodManager(1,&my_TerrainMatrix);
    CBlockManager myBlockManager(&my_TerrainMatrix);

    SDL_Event event;
    CTimer myTimer;
    CTimer myTTW;






    for(int i=0;i<3;i++)
    {

    myLevel=running;

    my_TerrainMatrix.clear();


    direction=basic_direction;
    mySnake.changeDirection(&basic_direction);
    mySnake.changeSnake(&snk1);
    mySnake.printOnTerrain(BLOCK_SNAKE1);


    myBlockManager.increaseBlocksBy(Levels[i].blocks_to_add);
    myBlockManager.populateTerrainMatrix();
    myBlockManager.printOnTerrainMatrix();


    myTTW.start_ticks();


    bool paused=false;

    while(myLevel==running)
    {

        myTimer.start_ticks();
        while(SDL_PollEvent(&event))
            if(event.type==SDL_QUIT)
                myLevel=quit;
            else
                if(event.type==SDL_MOUSEBUTTONDOWN)
                 paused=!paused;
                 else
                    updateDirection(event,direction);

        if(!paused)
       {

        myFoodManager.populateWithFood();
        my_TerrainMatrix.clear();
        myBlockManager.printOnTerrainMatrix();

        myFoodManager.printOnTerrain();



        mySnake.printOnTerrain(BLOCK_SNAKE2);

        if(myTTW.get_ElapsedTime()>=Levels[i].time_to_wait)
        {


            mySnake.changeDirection(&direction);
            mySnake.stepInStatus();
            myTTW.start_ticks();

        }
       }




        my_Screen.clear();
        my_TerrainMatrix.drawOnRenderer(my_Screen.get_Renderer());

        my_Screen.refresh();

        int delta=myTimer.get_ElapsedTime();

        if(delta<1000./FPS)
            SDL_Delay(1000./FPS - delta);


        if(!mySnake.isAlive())
            myLevel=over_lost;

        if(mySnake.getLength()==Levels[i].snake_length_win)
            myLevel=over_won;

    }

    switch(myLevel)
    {
case over_won:
    //TO DO CODE FOR WINNING
    break;
case over_lost:
    //TO DO CODE FOR LOSING
    return 0;
    break;
default:
    return 0;
    }
    }

    SDL_Quit();

    return 0;
}
