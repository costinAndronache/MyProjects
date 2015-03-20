#ifndef DEFINITIONS_H
    #define DEFINITIONS_H

#include "SDL.h"
#include <map>
#include <vector>
using namespace std;

typedef vector<SDL_Rect>  sprite_sequence;
typedef vector<SDL_Rect>* ptr_sprite_sequence;
typedef int texture_id;
typedef int sequence_id;

struct sequence_information
{
    ptr_sprite_sequence sprite_vector;
    int frame_delay;
    int loop_restart;
};

typedef map<sequence_id,sequence_information> sprite_sequence_map, *ptr_sprite_sequence_map;
typedef sequence_information *ptr_sequence_information;

#endif // DEFINITIONS_H
