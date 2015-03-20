#ifndef PROTOCOLS_H
    #define PROTOCOLS_H

struct LevelPlayerP{
enum{bullet,weapon}action;

union
{
    struct{
    enum{left,right}facing;
    int x,y;
    }actiontype;
};


};
#endif // PROTOCOLS_H
