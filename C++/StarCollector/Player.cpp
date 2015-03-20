#include "Player.h"


void Player::update(void *event=NULL,void *message=NULL)
{
/*    SDL_Event *eventt=(SDL_Event *)event;
        switch(eventt->type)
        {
        case SDL_KEYDOWN:
            switch(eventt->key.keysym.sym)
            {
            case SDLK_LEFT:
                set_move_left(true);
                set_move_right(false);
                break;
            case SDLK_RIGHT:
                set_move_right(true);
                set_move_left(false);
                break;
            case SDLK_UP:
                start_jumping();
                break;
            default:break;
            };
            break;
        case SDL_KEYUP:
            switch(eventt->key.keysym.sym)
            {
            case SDLK_LEFT:
                set_move_left(false);break;
            case SDLK_RIGHT:
                set_move_right(false);break;
            default:break;


            };break;
        default:break;

        };
        */


        Uint8 *keystate=SDL_GetKeyState(NULL);

        if(keystate[SDLK_LEFT])
        {
                set_move_left(true);
                set_move_right(false);

        }
        else
            set_move_left(false);

        if(keystate[SDLK_RIGHT])
        {

                set_move_right(true);
                set_move_left(false);
        }
        else
            set_move_right(false);

        if(keystate[SDLK_UP])
            start_jumping();

        update_position();


}

void Player::update_position()
{
    if(move_left)
    {
        usingspeedx=-(speedx);
        add_x(usingspeedx);
        moving=true;
    }
    else
    if(move_right)
    {
        usingspeedx=speedx;
        add_x(usingspeedx);
        moving=true;    }
    else
        moving=false;

    if(jump)
    {
        jump=false;
        if(!jumping)
        {
            jumping=true;
            moving=false;
            usingspeedy=-(speedy);
        }
    }

    //add the y



    //Modify the gravity with bonuses here.

    if(use_gravity)
    usingspeedy+=gravity;
    if(usingspeedy>maxgravity)
        usingspeedy=maxgravity;


    add_y(usingspeedy);

    if(jumping)
    {
        if(usingspeedx>0)
        {
            int sc=column;
            switch_line(2,RBank->get_frames(sheet,2)-1);
            column=sc;

        }
        else
        {
            int sc=column;
            switch_line(3,RBank->get_frames(sheet,3)-1);
            column=sc;
        }
    }
    else
        if(moving)
        {
        if(usingspeedx>0)
                switch_line(0,0);
            else
                switch_line(1,0);
            }
            else
                {
                if(usingspeedx>0)
                    switch_line(4,1);
                else
                    switch_line(5,1);
                    }



}

bool Player::resolve_static(Shape2D *pshape)
{
    Vector2D mtv=pshape->get_mtv(&BoundingBox);
    if(mtv.modulus())
    {
        if(mtv.get_y())
        {

            float absy=mtv.get_y();
            if(absy<0.f)
                absy=-absy;
                if(absy<1.f)
                    absy+=1.f;



        mtv.set_x(mtv.get_x()/(absy*(speedx/2)));
        }
        BoundingBox.add_vector(mtv);

    set_position_after_box();
    return true;
    }
    return false;

}

bool Player::stand_on_shape(Shape2D *shape)
{
    Shape2D test1,test2;



    Vector2D sv1[2],sv2[2];


    sv1[0]=Vector2D(x+2,y+39);
    sv1[1]=Vector2D(x+2,4000);

    sv2[0]=Vector2D(x+28,y+39);
    sv2[1]=Vector2D(x+28,4000);

    test1.init_vertices(sv1,2);
    test2.init_vertices(sv2,2);

    Vector2D mtv=shape->get_mtv(&test1);
    if(mtv.modulus())
        return true;
    else
    {
        mtv=shape->get_mtv(&test2);
        if(mtv.modulus())
            return true;
        else
            return false;

    }
}
