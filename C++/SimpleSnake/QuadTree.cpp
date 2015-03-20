#include "QuadTree.h"

QuadTree::QuadTree(int plevel,Shape2D &pbounds)
{
    level=plevel;
    bounds=pbounds;
    for(int i=0;i<max_objects;i++)
    exists[i]=false;
    for(int i=0;i<4;i++)
    nodes[i]=0;
    n_objects=0;
}

QuadTree::QuadTree()
{
    level=max_levels+1;
    for(int i=0;i<max_objects;i++)
    exists[i]=false;
    for(int i=0;i<4;i++)
    nodes[i]=0;
    n_objects=0;
}

void QuadTree::clear()
{

    for(int i=0;i<max_objects;i++)
    exists[i]=false;
    n_objects=0;

    if(nodes[0])
    {
        for(int i=0;i<4;i++)
        {
            nodes[i]->clear();
            delete nodes[i];
            nodes[i]=0;
        }
    }
}

void QuadTree::split()
{
    int midX,midY;
    Vector2D v1=bounds.get_vertice(0),v2=bounds.get_vertice(1);

    midX=(v1.get_x()+v2.get_x())/2;
    midY=(v1.get_y()+v2.get_y())/2;

    Vector2D pts[2];
    Shape2D pbounds;

    //Cadranul 1 --->0
    pts[0].set_xy(midX,v1.get_y());
    pts[1].set_xy(v2.get_x(),midY);
    pbounds.init_vertices(pts,2);
    nodes[0]= new QuadTree(level+1,pbounds);

    //Cadranul 2--->1
    pts[0]=v1;
    pts[1].set_xy(midX,midY);
    pbounds.init_vertices(pts,2);
    nodes[1]= new QuadTree(level+1,pbounds);

    //Cadranul 3--->2
    pts[0].set_xy(v1.get_x(),midY);
    pts[1].set_xy(midX,v2.get_y());
    pbounds.init_vertices(pts,2);
    nodes[2]= new QuadTree(level+1,pbounds);

    //Cadranul 4--->3
    pts[0].set_xy(midX,midY);
    pts[1]=v2;
    pbounds.init_vertices(pts,2);
    nodes[3]= new QuadTree(level+1,pbounds);
}

int QuadTree::get_index(Shape2D *shape)
{
    int midX,midY;
    Shape2D box=shape->get_aabb();
    Vector2D v1=bounds.get_vertice(0),v2=bounds.get_vertice(1);

    midX=(v1.get_x()+v2.get_x())/2;
    midY=(v1.get_y()+v2.get_y())/2;

    v1=box.get_vertice(0);
    v2=box.get_vertice(1);

    //testing for the first quadrant

    if(v1.get_x()>midX && v2.get_y()<midY)
    return 0;

    //quadrant 2
    if(v2.get_x()<midX && v2.get_y()<midY)
    return 1;

    //quadrant 3
    if(v2.get_x()<midX && v1.get_y()>midY)
    return 2;

    //quadrant 4
    if(v1.get_x()>midX && v1.get_y()>midY)
    return 3;

    return -1;
}

void QuadTree::insert(Shape2D *shape)
{
    if(nodes[0])
    {
        int quadrant=get_index(shape);
        if(quadrant!=-1)
        {
            nodes[quadrant]->insert(shape);
            return;
        }
    }

    for(int i=0;i<max_objects;i++)
     if(!exists[i])
     {
         exists[i]=true;
         list[i]=shape;
         i=max_objects+10;
         n_objects++;
     }

     if(n_objects==max_objects && level<max_levels)
     {
         if(!nodes[0])
         split();

         for(int i=0;i<max_objects;i++)
         if(exists[i])
         {
             int quadrant=get_index(list[i]);
              if(quadrant!=-1)
              {
                  exists[i]=false;
                  n_objects--;
                  nodes[quadrant]->insert(list[i]);

              }
         }
     }
}

void QuadTree::retrieve(Shape2D *in_list[],int &n_inlist,Shape2D *shape)
{
    int quadrant=get_index(shape);
     if(quadrant!=-1 && nodes[0])
       nodes[quadrant]->retrieve(in_list,n_inlist,shape);

    int k=0;
    for(int i=0;i<max_objects;i++)
    if(exists[i] && list[i]!=shape)
    {
        in_list[n_inlist+k]=list[i];
        k++;
    }

    n_inlist+=k;
}


