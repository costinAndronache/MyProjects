#include "Level_1.h"

#include "DefineList.h"
#include "DrawUtils.h"

#define LVLW 3200
#define LVLH 2400
void Level_1::initialize(Player *pplayer,SDL_Surface *pscreen)
{
    player=pplayer;
    screen=pscreen;

    for(int i=0;i<3;i++)
    {
        Boxes[i].set_drawing_basics(0,0,0,0,i+1,10,ResourceBank::get_instance());
        Boxes[i].set_basic_motion(2,3,0,0);
    }

    Boxes[0].set_direction(Vector2D(150,100),Vector2D(2000,100));
    Boxes[1].set_direction(Vector2D(300,400),Vector2D(300,100));
    Boxes[2].set_direction(Vector2D(300,400),Vector2D(600,100));

    land.set_drawing_basics(0,410,2,0,1,1,ResourceBank::get_instance());
    soul.set_drawing_basics(100,350,3,0,0,4,ResourceBank::get_instance());
}

void Level_1::execute()
{
    bool quit=false;
    bool soulalive=true;

    bool sticky=false;
    int antx,anty,crtx,crty;

    drawbuffer=SDL_CreateRGBSurface(0,LVLW,LVLH,16,0,0,0,0);
    camera.w=SCREEN_WIDTH;
    camera.h=SCREEN_HEIGHT;

    //SDL_Surface *background=IMG_Load("Assets\\Level_1\\background.png");


   while(!quit)
    {
        SDL_Event event;
        Uint32 start=SDL_GetTicks();

        while(SDL_PollEvent(&event))
            switch(event.type)
        {
            case SDL_QUIT:
                quit=true;break;

        default:break;

        };

        player->update((void *)&event,NULL);

        for(int i=0;i<3;i++)
        Boxes[i].update(NULL,NULL);

        if(player->resolve_static(land.get_shape()))
            player->stop_jumping();
        bool collided=false;
        for(int i=0;i<3;i++)
        {
            if(player->resolve_static(Boxes[i].get_shape()))
            {if(player->get_y()+30<Boxes[i].get_y())
                {
               player->stop_jumping();


               if(!sticky)
               {
                   sticky=true;
                   antx=Boxes[i].get_x();
                   anty=Boxes[i].get_y();

               }
               else
               {
                   crtx=Boxes[i].get_x();
                   crty=Boxes[i].get_y();

                   player->add_x(crtx-antx);
                   player->add_y(crty-anty);

                   player->resolve_static(Boxes[i].get_shape());

                   antx=crtx;
                   anty=crty;
               }

               collided=true;
               i=99;
           }
           else
            if(player->get_y()>Boxes[i].get_y()+73)
                player->escape_jump();
        }

        }
        if(!collided)
            sticky=false;

        if(soulalive)
        if(player->check_shape(soul.get_shape()))
        {
            soulalive=false;
            player->add_score(1);
        }





        player->step_animation();
        soul.step_animation();
        //land.step_animation();
        for(int i=0;i<3;i++)
        Boxes[i].step_animation();


        camera.x=player->get_x()+cam_error-(SCREEN_WIDTH/2);
        camera.y=player->get_y()+cam_error-(SCREEN_HEIGHT/2);


        if(camera.x<0)
        camera.x=0;
        if(camera.x>LVLW-SCREEN_WIDTH)
        camera.x=LVLW-SCREEN_WIDTH;

        if(camera.y<0)
        camera.y=0;
        if(camera.y>LVLH-SCREEN_HEIGHT)
        camera.y=LVLH-SCREEN_HEIGHT;


//        if(background)
            //SDL_BlitSurface(background,NULL,drawbuffer,&camera);
        else

        SDL_FillRect(drawbuffer,NULL,SDL_MapRGB(screen->format,0,0,120));
        player->draw(drawbuffer);

        land.draw(drawbuffer);
        if(soulalive)
        soul.draw(drawbuffer);


        for(int i=0;i<3;i++)
        {
            Boxes[i].draw(drawbuffer);
            draw_shape(drawbuffer,Boxes[i].get_shape(),255,0,0);
        }

        SDL_BlitSurface(drawbuffer,&camera,screen,NULL);
        SDL_Flip(screen);

        Uint32 stop=SDL_GetTicks();

        float dife=(float)(stop-start);

        if(dife<(1000./FPS))
            SDL_Delay((Uint32)1000./FPS-dife);

    }
    SDL_FreeSurface(drawbuffer);
   // if(background)
       // SDL_FreeSurface(background);
}
