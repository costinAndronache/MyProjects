#include "Level.h"
#include <fstream>
#include "TextDisplay.h"

#define LVLW 3200
#define LVLH 2400
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define cam_error 15
#define FPS 25
#define to_rad(x) (3.14*x/180.)


bool Level::initialize(char *file,Player *pplayer,SDL_Surface *pscreen,int c)
{
    color=c;
    stars=NULL;
    ground=rotating_ground=NULL;
    moving_ground=NULL;
    Vector2D aux[20];
    int k;

    player=pplayer;
    screen=pscreen;

    std::ifstream f(file);

    if(!f.good())
    return false;


    //First, the ground shapes

    f>>n_ground;
    if(n_ground)
        ground=new Shape2D[n_ground];
    {
    for(int i=0;i<n_ground;i++)
    {

        f>>k;
         for(int j=0;j<k;j++)
         {
             int x,y;

             f>>x>>y;
             aux[j].set_xy(x,y);
         }

         ground[i].init_vertices(aux,k);
    }
    }

    f>>n_rotating_ground;
    if(n_rotating_ground)
    {
        rotating_ground=new Shape2D[n_rotating_ground];
        for(int i=0;i<n_rotating_ground;i++)
    {
        f>>k>>degree_rotating[i];
         for(int j=0;j<k;j++)
         {
             int x,y;

             f>>x>>y;
             aux[j].set_xy(x,y);
         }

         rotating_ground[i].init_vertices(aux,k);


    }
    }

    f>>n_moving_ground;
    if(n_moving_ground)
    {
        moving_ground=new FromToShape[n_moving_ground];
    for(int i=0;i<n_moving_ground;i++)
    {
        int k,x1,x2,y1,y2;
        float sspeed;
        f>>k>>x1>>y1>>x2>>y2>>sspeed;
         for(int j=0;j<k;j++)
         {
             int x,y;

             f>>x>>y;
             aux[j].set_xy(x,y);
         }

         moving_ground[i].get_shape()->init_vertices(aux,k);
         moving_ground[i].set_direction(Vector2D(x1,y1),Vector2D(x2,y2),sspeed);


    }
    }

    f>>n_star;
    if(n_star)
    {
        stars=new VisualCollide[n_star];
        for(int i=0;i<n_star;i++)
    {
        alive_star[i]=true;
        int x,y,sheet;

        f>>x>>y;
        stars[i].set_drawing_basics(x,y,3,0,0,5,ResourceBank::get_instance());
    }
    }

    f>>start_x>>start_y;


    f>>bg>>ms;



    f.close();
    return true;

}

void Level::execute(int &state)
{


    bool collided=false,sticky=false,on_ground=false,check_ground;
    TextDisplay textdisplay("newscycle.ttf",16);
    int score=0;

    background=IMG_Load(bg);
    music=Mix_LoadMUS(ms);

    SDL_Surface *buffer=SDL_CreateRGBSurface(0,3200,2400,16,0,0,0,0);
    player->set_x(start_x);
    player->set_y(start_y);
    player->add_x(0);

    bool quit=false;
    SDL_Rect camera={0,0,640,480};
    SDL_Event event;


    SDL_Delay(200);

    Mix_VolumeMusic(24);
    Mix_PlayMusic(music,-1);
    while(!quit)
    {

        Uint32 start=SDL_GetTicks();

        while(SDL_PollEvent(&event))
            if(event.type==SDL_QUIT)
            {
                quit=true;
                state=-1;
            }

        player->update((SDL_Event*)&event,NULL);

        for(int i=0;i<n_moving_ground;i++)
               moving_ground[i].update();



        for(int i=0;i<n_rotating_ground;i++)
        {
            Vector2D center=rotating_ground[i].get_center();
            rotating_ground[i].rotate_around_point(center,(float)to_rad(degree_rotating[i]));
        }



        bool val=false;
        for(int i=0;i<n_ground;i++)
        {
                if(player->resolve_static(&ground[i]))
                {

                    player->resolve_static(&ground[i]);
                    //player->stop_jumping();

                    if(player->stand_on_shape(&ground[i]))
                    player->stop_jumping(),val=true;
                    else
                        player->escape_jump();




                }

        }


        player->set_jumping(!val);



            for(int i=0;i<n_rotating_ground;i++)
             if(player->resolve_static(&rotating_ground[i]))
             {
                 player->resolve_static(&rotating_ground[i]);

                 if(player->stand_on_shape(&rotating_ground[i]))
                    player->stop_jumping();
                 else
                    player->escape_jump();
             }


        collided=false;
        int crtx,crty,antx,anty;
        for(int i=0;i<n_moving_ground;i++)
        {
            if(player->resolve_static(moving_ground[i].get_shape()))
            {
                if(player->stand_on_shape(moving_ground[i].get_shape()))
                {
               player->stop_jumping();
               Vector2D center=moving_ground[i].get_shape()->get_vertice(0);


               if(!sticky)
               {
                   sticky=true;
                   antx=center.get_x();
                   anty=center.get_y();

               }
               else
               {
                   crtx=center.get_x();
                   crty=center.get_y();

                   player->add_x(crtx-antx);
                   player->add_y(crty-anty);

                   player->resolve_static(moving_ground[i].get_shape());

                   antx=crtx;
                   anty=crty;
               }

               collided=true;
               i=99;
           }
           else
                player->escape_jump();
        }

        }
        if(!collided)
            sticky=false;




        for(int i=0;i<n_star;i++)
            if(alive_star[i])
             if(player->check_shape(stars[i].get_shape()))
        {
            alive_star[i]=false;
            score++;
        }


        player->step_animation();
        for(int i=0;i<n_star;i++)
            stars[i].step_animation();


        camera.x=player->get_x()+cam_error-(SCREEN_WIDTH/2);
        camera.y=player->get_y()+cam_error-(SCREEN_HEIGHT/2);

                int cx,cy;

        cx=player->get_x();
        cy=player->get_y()-20;


        if(camera.x<0)
        camera.x=0;
        if(camera.x>LVLW-SCREEN_WIDTH)
        camera.x=LVLW-SCREEN_WIDTH;

        if(camera.y<0)
        camera.y=0;
        if(camera.y>LVLH-SCREEN_HEIGHT)
        camera.y=LVLH-SCREEN_HEIGHT;

        if(player->get_y()>LVLH)
            player->set_y(0);



        SDL_BlitSurface(background,&camera,buffer,&camera);


        //SDL_FillRect(buffer,&camera,SDL_MapRGB(buffer->format,0,0,16));
        player->draw(buffer);

        Vector2D auxv[4]={Vector2D(camera.x,camera.y),Vector2D(camera.x+SCREEN_WIDTH,camera.y),
                     Vector2D(camera.x+SCREEN_WIDTH,camera.y+SCREEN_HEIGHT),
                     Vector2D(camera.x,camera.y+SCREEN_HEIGHT)};
        Shape2D auxshape;
        auxshape.init_vertices(auxv,4);

        for(int i=0;i<n_ground;i++)
        {
            if(auxshape.is_colliding(&ground[i]))
                draw_shape_filled(buffer,&ground[i],0,120-3*color,240);
        }

        for(int i=0;i<n_moving_ground;i++)
        {
            if(auxshape.is_colliding(moving_ground[i].get_shape()))
                draw_shape_filled(buffer,moving_ground[i].get_shape(),0,220-6*color,220-6*color);

        }

        for(int i=0;i<n_rotating_ground;i++)
        {
            if(auxshape.is_colliding(&rotating_ground[i]))
                draw_shape_filled(buffer,&rotating_ground[i],140-6*color,0,0);
        }


        for(int i=0;i<n_star;i++)
        {
            if(alive_star[i] && auxshape.is_colliding(stars[i].get_shape()))
                stars[i].draw(buffer);
            }


        //textdisplay.print(buffer,"Daniel",cx,cy,255,0,0);
        SDL_BlitSurface(buffer,&camera,screen,NULL);
        textdisplay.print(screen,score,600,0,0,255,255);
        textdisplay.print(screen,n_star-score,600,18,255,0,0);

        //textdisplay.print(screen,"Pentru Ciprian ",0,0,0,0,250);



        SDL_Flip(screen);

        if(score==n_star)
        {
            quit=true;
            state=1;
        }


        Uint32 stop=SDL_GetTicks();
        float delta=(float)(stop-start);

        if(delta<1000./FPS)
            SDL_Delay(1000./FPS-delta);
    }


    SDL_FreeSurface(buffer);
    SDL_FreeSurface(background);
    Mix_FreeMusic(music);


}

Level::~Level()
{
    if(moving_ground)
        delete[] moving_ground;
    if(rotating_ground)
        delete[] rotating_ground;
    if(ground)
        delete[] rotating_ground;
    if(stars)
        delete[] stars;
}
