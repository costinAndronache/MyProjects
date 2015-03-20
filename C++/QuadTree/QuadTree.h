#ifndef QUADTREE_H
    #define QUADTREE_H


#include "shape2D.h"

#define max_levels 8
#define max_objects 4

class QuadTree
{
    Shape2D *list[max_objects];
    bool exists[max_objects];

    int level,n_objects;
    Shape2D bounds;
    QuadTree *nodes[4];

    int get_index(Shape2D *shape);
    void split();

    public:
    QuadTree(int plevel,Shape2D &pbounds);
    QuadTree();

    void clear();
    void insert(Shape2D *shape);
    void retrieve(Shape2D *in_list[],int &n_inlist,Shape2D *shape);
    QuadTree *get_node(int i){return nodes[i];}
    Shape2D get_bounds(){return bounds;}

};
#endif
