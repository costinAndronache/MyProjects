#include"SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"
#include <sstream>
#include<fstream>
#include "vector2d.h"
#include "projection2D.h"
#include "shape2D.h"
using namespace std;


#define LVLW 3200
#define LVLH 2400
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define cam_error 0

#define FPS 20
#define max_stuff 150

SDL_Surface *screen,*textsurface;
SDL_Event event;
TTF_Font *font;
std::stringstream sstm;

    Shape2D box1,box2,triangle1;
    Vector2D points[max_stuff];
    Shape2D shapes[max_stuff];
    int crt_point=0,n_shapes=0;

    Vector2D stars[max_stuff];
    int n_stars;



float to_rad(int angle)
{
    return angle*3.14/180;
}

void init_shape(Shape2D &shape,char *file)
{
    std::ifstream f(file);
    Vector2D v[max_stuff];
    int n;
    float x,y;

    f>>n;
    for(int i=0;i<n;i++)
    {
        f>>x>>y;
        v[i].set_xy(x,y);
    }

    shape.init_vertices(v,n);
    f.close();
}

void read_shapes()
{
    std::ifstream f("writefile.txt");

    f>>n_shapes;

    Vector2D v[max_stuff];
    int n,x,y;


    for(int i=0;i<n_shapes;i++)
    {
        f>>n;
        for(int k=0;k<n;k++)
            {
                f>>x>>y;
                v[k].set_xy(x,y);
            }
        shapes[i].init_vertices(v,n);

    }

    f>>n_stars;
    for(int i=0;i<n_stars;i++)
    {
        int x,y;
        f>>x>>y;
        stars[i].set_xy(x,y);
    }
}


void set_camera_shape(Shape2D *shape,SDL_Rect *camera)
{
    Vector2D point=shape->get_center();

        camera->x=point.get_x()+cam_error-(SCREEN_WIDTH/2);
        camera->y=point.get_y()+cam_error-(SCREEN_HEIGHT/2);


        if(camera->x<0)
        camera->x=0;
        if(camera->x>LVLW-SCREEN_WIDTH)
        camera->x=LVLW-SCREEN_WIDTH;

        if(camera->y<0)
        camera->y=0;
        if(camera->y>LVLH-SCREEN_HEIGHT)
        camera->y=LVLH-SCREEN_HEIGHT;

}

void draw_shape(SDL_Surface *screen,Shape2D &shape,bool last,int r,int g,int b)
{
    for(int i=0;i<shape.get_num()-1;i++)
    {
        Vector2D v1=shape.get_vertice(i);
        Vector2D v2=shape.get_vertice(i+1);

        lineRGBA(screen,(Sint16)v1.get_x(),(Sint16)v1.get_y(),
                         (Sint16)v2.get_x(),(Sint16)v2.get_y(),
                  r,g,b,255);
    }
    Vector2D v1=shape.get_vertice(shape.get_num()-1);
    Vector2D v2=shape.get_vertice(0);
    if(last)
        lineRGBA(screen,(Sint16)v1.get_x(),(Sint16)v1.get_y(),
                         (Sint16)v2.get_x(),(Sint16)v2.get_y(),
                  r,g,b,255);

}

Vector2D get_mtv(Shape2D &static_shape,Shape2D &dynamic_shape)
{
    float overlap=0x3f3f3f3f,oaux;
    int n_axis1,n_axis2;
    int n_static=static_shape.get_num(),n_dynamic=dynamic_shape.get_num();

    Vector2D smallest,mtv;
    Vector2D axis1[max_stuff],axis2[max_stuff];

    Projection2D p1;
    Projection2D p2;
    Projection2D save1,save2;

    static_shape.get_axes(axis1,n_axis1);
    dynamic_shape.get_axes(axis2,n_axis2);

    for(int i=0;i<n_axis1;i++)
    {
        p1=static_shape.project(axis1[i]);
        p2=dynamic_shape.project(axis1[i]);

        if(!p1.overlap(p2))
        {
            mtv.set_xy(0,0);
            return mtv;
        }
        else
        {
            if(n_static==2 || n_dynamic==2)
            oaux=p1.get_overlap_segment(p2);
           else
            oaux=p1.get_overlap_polygon(p2);
            if(oaux<overlap)
            {
                overlap=oaux;
                smallest=axis1[i];
                save1=p1;
                save2=p2;
            }
        }
    }

    for(int i=0;i<n_axis2;i++)
    {
        p1=static_shape.project(axis2[i]);
        p2=dynamic_shape.project(axis2[i]);

        if(!p1.overlap(p2))
        return Vector2D(0,0);
        else
        {
            if(n_static==2 || n_dynamic==2)
            oaux=p1.get_overlap_segment(p2);
            else
            oaux=p1.get_overlap_polygon(p2);
            if(oaux<overlap)
            {
                overlap=oaux;
                smallest=axis2[i];
                save1=p1;
                save2=p2;
            }
        }
    }

    mtv=smallest;
    mtv.multiply(overlap);

    Vector2D center_static,center_dynamic,center_v;
    center_static=static_shape.get_center();
    center_dynamic=dynamic_shape.get_center();

    center_v=center_dynamic.result_substract(center_static);

    if(mtv.dotproduct(center_v)<0.f)
    {
        mtv.multiply(-1);
    }

    return mtv;
}

void write();

int main(int argc,char *argv[])
{


    Projection2D pbox,ptriangle;

    init_shape(box1,"box1.txt");
    //init_shape(box2,"box2.txt");
    read_shapes();
    //init_shape(triangle1,"triangle1.txt");




    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *buffer=SDL_CreateRGBSurface(0,3200,2400,16,0,0,0,0);

    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,16,SDL_HWSURFACE|SDL_DOUBLEBUF);


    SDL_Rect camera={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    bool quit=false;
    bool move_up=false,move_down=false,move_left=false,move_right=false,put_star=false;

    bool mouse_click=false,end_shape=false,end_box=false,mouse_move=false;
    bool collision_on=true,show_center=false,show_mtv=false;
    bool rotate=false;

    int coordx,coordy,mcoordx,mcoordy,scoordx,scoordy;
    const float velx=15.f,vely=14.f,angle=to_rad(15);

    Vector2D dir(0,0);
    while(!quit)
    {
        Uint32 start=SDL_GetTicks();
        while(SDL_PollEvent(&event))
        switch(event.type)
        {
            case SDL_QUIT:
                quit=true;
                    break;
            case SDL_KEYDOWN:
             switch(event.key.keysym.sym)
             {
                 case SDLK_t:
                     put_star=true;
                     scoordx=event.button.x;
                     scoordy=event.button.y;
                     break;
                 case SDLK_c:
                    collision_on=!collision_on;
                    break;
                 case SDLK_b:
                    end_box=true;
                    break;
                 case SDLK_LEFT:
                    move_left=true;
                        break;
                 case SDLK_RIGHT:
                    move_right=true;
                        break;
                 case SDLK_UP:
                    move_up=true;
                        break;
                 case SDLK_DOWN:
                    move_down=true;
                        break;
                 case SDLK_e:
                    end_shape=true;
                        break;
                 case SDLK_s:
                    show_center=!show_center;
                        break;
                 case SDLK_m:
                    show_mtv=!show_mtv;
                        break;
                 case SDLK_r:
                    rotate=true;
                        break;
                        break;
                default:break;
             };
                break;
            case SDL_KEYUP:
             switch(event.key.keysym.sym)
             {
                 case SDLK_LEFT:
                    move_left=false;
                        break;
                 case SDLK_RIGHT:
                    move_right=false;
                        break;
                 case SDLK_UP:
                    move_up=false;
                        break;
                 case SDLK_DOWN:
                    move_down=false;
                 case SDLK_r:
                    rotate=false;
                        break;
                 default: break;
             };
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse_click=true;
                coordx=event.button.x;
                coordy=event.button.y;
                        break;

            case SDL_MOUSEMOTION:
                mcoordx=event.button.x;
                mcoordy=event.button.y;
                mouse_move=true;
                        break;

            default:break;
        };

        if(put_star && n_stars<max_stuff)
        {
            put_star=false;
            SDL_GetMouseState(&scoordx,&scoordy);
            stars[n_stars++]=Vector2D(scoordx+camera.x,scoordy+camera.y);


        }


        if(mouse_click)
        {
            mouse_click=false;
            points[crt_point].set_xy((float)coordx+camera.x,(float)coordy+camera.y);
            crt_point++;
        }

        if(end_shape && n_shapes<max_stuff)
        {
            end_shape=false;
            shapes[n_shapes].init_vertices(points,crt_point);
            n_shapes++;
            crt_point=0;
        }

        if(end_box)
        {
            end_box=false;
            box1.init_vertices(points,crt_point);
            crt_point=0;
        }
        if(rotate)
        {
            Vector2D center=box1.get_center();
            box1.rotate_around_point(center,angle);
        }



        if(move_left)
            dir.set_x(-velx);
            else
            if(move_right)
                dir.set_x(velx);
                else
                    dir.set_x(0.f);

        if(move_up)
            dir.set_y(-vely);
            else
            if(move_down)
                dir.set_y(vely);
                else
                dir.set_y(0.f);


        set_camera_shape(&box1,&camera);

        SDL_FillRect(buffer,&camera,SDL_MapRGB(screen->format,0,0,0));


        box1.add_vector(dir);

        Vector2D cv[2];
        cv[0]=box1.get_center();

        Vector2D mtv,draw_mtv,start_mtv;

        //Testeaza player-ul impotriva fiecarei figuri
        //De asemenea deseneaza si MTV adica Minimum Translation Vector
        //Practic, e vectorul folosit pentru a impinge player-ul in afara figurei cu care intra
        //in ciocnire

        for(int i=0;i<n_shapes;i++)
        {
            mtv=get_mtv(shapes[i],box1);
            if(collision_on)
            {box1.add_vector(mtv);}

        if(show_mtv)
        {start_mtv=box1.get_center();
        draw_mtv=start_mtv.result_add(mtv);
        lineRGBA(buffer,(Sint16)start_mtv.get_x(),(Sint16)start_mtv.get_y(),
                        (Sint16)draw_mtv.get_x(),(Sint16)draw_mtv.get_y(),
                 0,255,255,255);
        }
        }



        //Deseneaza player-ul si toate figurile curente.
        //Totodata se deseneaza si linia ce uneste centrul fiecarei figuri cu centrul jucatorului
        draw_shape(buffer,box1,true,0,0,255);
        for(int i=0;i<n_shapes;i++)
        {draw_shape(buffer,shapes[i],true,255,125,0);

         if(show_center)
         {cv[1]=shapes[i].get_center();
         lineRGBA(screen,(Sint16)cv[0].get_x(),(Sint16)cv[0].get_y(),
                         (Sint16)cv[1].get_x(),(Sint16)cv[1].get_y(),
                  255,255,255,255);
         }
        }


        //Aici se deseneaza figura care este in constructie
        //Nu intra in ciocnire cu player-ul decat dupa ce constructia e finalizata
        Shape2D drawing_shape;
        if(crt_point>=1)
        {

            drawing_shape.init_vertices(points,crt_point);
            draw_shape(buffer,drawing_shape,false,0,255,0);

            //if(mouse_move)
            {
                mouse_move=false;
                Vector2D v1=drawing_shape.get_vertice(crt_point-1),v2(mcoordx+camera.x,mcoordy+camera.y);

                        lineRGBA(buffer,(Sint16)v1.get_x(),(Sint16)v1.get_y(),
                         (Sint16)v2.get_x(),(Sint16)v2.get_y(),
                  255,0,0,255);
            }

        }

        for(int i=0;i<n_stars;i++)
            circleRGBA(buffer,(Sint16)stars[i].get_x(),(Sint16)stars[i].get_y(),5,255,120,0,255);


        SDL_BlitSurface(buffer,&camera,screen,NULL);
        SDL_Flip(screen);

        Uint32 stop=SDL_GetTicks();
        float diff=(float)(stop-start);

        if(diff<1000./FPS)
        SDL_Delay(1000./FPS-diff);
    }

    write();

    SDL_Quit();
    return 0;
}

void write()
{
    std::ofstream g("writefile.txt");

    g<<n_shapes<<'\n';

    for(int i=0;i<n_shapes;i++)
    {
        int num=shapes[i].get_num();
        g<<num<<'\n';

        for(int j=0;j<num;j++)
        {
            Vector2D vertice=shapes[i].get_vertice(j);

            g<<(int)vertice.get_x()<<' '<<(int)vertice.get_y()<<'\n';
        }
    }

    g<<"\n\n\n"<<n_stars<<'\n';

    for(int i=0;i<n_stars;i++)
        g<<(int)stars[i].get_x()<<' '<<stars[i].get_y()<<'\n';

    g.close();

}




 /*   Vector2D mtv=get_mtv(box1,triangle1);
    if(mtv.modulus()>0.0f)
    {
        //cout<<"Ciocnire! Rezolv.\n\n";
        //cout<<"Vectorul de translatie: "<<mtv.get_x()<<' '<<mtv.get_y()<<'\n'<<'\n';
        triangle1.add_vector(mtv);

        for(int i=0;i<triangle1.get_num();i++)
        {
            Vector2D aux=triangle1.get_vertice(i);
          //  cout<<aux.get_x()<<' '<<aux.get_y()<<'\n';
        }
    }



    return 0;
}
*/
