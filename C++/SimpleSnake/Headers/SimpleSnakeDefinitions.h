#ifndef SIMPLESNAKEDEFINITIONS_H
    #define SIMPLESNAKEDEFINITIONS_H

#define EMPTY 0
#define BLOCK_RED 1
#define BLOCK_GREEN 2
#define BLOCK_BLUE 3

#define BLOCK_SNAKE1 'p'
#define BLOCK_SNAKE2 'q'

#define BLOCK_FOOD 'f'

#define MAX_SNAKE_SIZE 128

#define CELL_SIZE 16
#define WIDTH 800
#define HEIGHT 600


#define MAX_BLOCK_ITEMS 128
#define MAX_FOOD_ITEMS 2
#define FPS 10

struct simple_point
{
    int x,y;
};

struct snake_struct
{

    simple_point snake_vector[MAX_SNAKE_SIZE];
    int m_length;
   };


struct levelInfo
{
    unsigned int time_to_wait;
    unsigned int snake_length_win;
    unsigned int blocks_to_add;
};

#endif // SIMPLESNAKEDEFINITIONS_H
