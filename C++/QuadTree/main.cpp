#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"
#include "QuadTree.h"
#include "utilities.h"

#define max_shapes 512
#define width 800
#define height 600

QuadTree *Q;
Shape2D shapes[max_shapes];
Vector2D direction[max_shapes];
int n_shapes;

//To create the new shape
int point_x,point_y;
bool point_down;


//SDL stuff
SDL_Surface *screen;
SDL_Event event;
TTF_Font *font;
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

void create_new_shape(int xoff,int yoff,float speedx,float speedy)
{
    Vector2D pts[4];
    pts[0].set_xy(point_x,point_y);
    pts[1].set_xy(point_x+xoff,point_y);
    pts[2].set_xy(point_x+xoff,point_y+yoff);
    pts[3].set_xy(point_x,point_y+yoff);

    shapes[n_shapes].init_vertices(pts,4);
    direction[n_shapes].set_xy(speedx,speedy);
    n_shapes++;
}

void apply_directions()
{
    for(int i=0;i<n_shapes;i++)
    {
        shapes[i].add_vector(direction[i]);
        for(int j=0;j<shapes[i].get_num();j++)
        {
            Vector2D aux=shapes[i].get_vertice(j);
            float x1=aux.get_x();
            float y1=aux.get_y();

            if(x1>width || x1<0)
            {
                direction[i].set_x(direction[i].get_x()*(-1));
                j=128;
            }
            if(y1>height || y1<0)
            {
                direction[i].set_y(direction[i].get_y()*(-1));
                j=128;

            }
        }
    }
}

void resolve_collisions()
{
    Shape2D *check_list[128];
    int n_check;
    Vector2D mtv;

    for(int i=0;i<n_shapes;i++)
    {
        n_check=0;
        Q->retrieve(check_list,n_check,&shapes[i]);
        for(int j=0;j<n_check;j++)
        {
            if(shapes[i].aabb_overlap(check_list[j]))
            {mtv=get_mtv(check_list[j],&shapes[i]);
            if(mtv.modulus())
            {
                mtv.multiply(0.5f);
                Vector2D mtv2=mtv;
                shapes[i].add_vector(mtv);
                mtv2.multiply(-1);
                check_list[j]->add_vector(mtv2);

                //mtv.multiply(3.f);
                direction[i].multiply(-1);
                //j=n_check+1;
            }
            }

        }
    }
}

bool resolve_collisions_naive()
{
    for(int i=0;i<n_shapes-1;i++)
     for(int j=i+1;j<n_shapes;j++)
     {
         Vector2D mtv=get_mtv(&shapes[i],&shapes[j]);
         shapes[j].add_vector(mtv);
     }
}

void see_collisions()
{
    Shape2D *check_list[128];
    int n_check;

    for(int i=0;i<n_shapes;i++)
    {
        n_check=0;
        Q->retrieve(check_list,n_check,&shapes[i]);
        for(int j=0;j<n_check;j++)
        {
            Shape2D bbox=check_list[j]->get_aabb();
            draw_shape(screen,bbox,true,0,255,255);
        }
    }
}



void draw_quadtree(QuadTree *q)
{
    QuadTree *check=q->get_node(0);
     if(check)
       for(int i=0;i<4;i++)
        draw_quadtree(q->get_node(i));
    Shape2D bounds=q->get_bounds();

    Vector2D points[4];
    points[0]=bounds.get_vertice(0);
    points[2]=bounds.get_vertice(1);
    points[1].set_xy(points[2].get_x(),points[0].get_y());
    points[3].set_xy(points[0].get_x(),points[2].get_y());

    Shape2D drawing_shape;
    drawing_shape.init_vertices(points,4);
    draw_shape(screen,drawing_shape,true,0,255,0);
}

void add_objects()
{
    if(Q)
    {Q->clear();
    delete Q;}

    Vector2D pts[2]={Vector2D(0,0),Vector2D(width,height)};
    Shape2D bounds(pts,2);
    Q=new QuadTree(0,bounds);

    for(int i=0;i<n_shapes;i++)
    Q->insert(&shapes[i]);
}

void draw_objects()
{
    for(int i=0;i<n_shapes;i++)
     draw_shape(screen,shapes[i],true,255,0,0);
}

void draw_number()
{

    SDL_Surface *textsurface;
    SDL_Color color={0,255,255};
    char ch[10];
    itoa(n_shapes,ch,9);
    textsurface=TTF_RenderText_Solid(font,ch,color);
    SDL_Rect pos={width-50,0,0,0};

    SDL_BlitSurface(textsurface,NULL,screen,&pos);
    SDL_FreeSurface(textsurface);
}
void mainLoop()
{
    bool quit=false;

    while(!quit)
    {
        while(SDL_PollEvent(&event))
         switch(event.type)
         {
             case SDL_QUIT:
                quit=true;
                    break;

             case SDL_MOUSEBUTTONDOWN:
                point_down=true;
                point_x=event.button.x;
                point_y=event.button.y;
                    break;
             case SDL_MOUSEBUTTONUP:
                point_down=false;
                    break;
            default:break;
         };

         if(point_down)
         {
             //point_down=false;
             if(n_shapes<max_shapes)
             create_new_shape(30,30,1.f,1.f);
         }

         apply_directions();
         //resolve_collisions();
         resolve_collisions_naive();
         add_objects();


         SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
         draw_objects();
         draw_number();
         //see_collisions();
         draw_quadtree(Q);

         SDL_Flip(screen);
         //SDL_Delay(10);
    }
}




int main(int argc,char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    screen=SDL_SetVideoMode(width,height,16,SDL_HWSURFACE);
    font=TTF_OpenFont("newscycle.ttf",16);
    mainLoop();
    SDL_Quit();
    TTF_Quit();

    return 0;
}
