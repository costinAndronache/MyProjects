#ifndef CTEXTUREMANAGER_H
    #define CTEXTUREMANAGER_H

#include "SDL.h"
#include "SDL_image.h"
#include "Definitions.h"
#include <cstdlib>
#include <map>
#include <vector>


using namespace std;





class CTextureManager
{
    map<texture_id, SDL_Texture*> texture_map;
    map<texture_id, ptr_sprite_sequence_map > sequence_map;

    int number_of_textures;

    SDL_Renderer *associated_renderer;
    void read_sprite_data(char *path);
    void free_textures();
    void free_vectors();


public:
    ~CTextureManager();
    CTextureManager(){associated_renderer=NULL;number_of_textures=0;}
    void reinitialize(char *mainfile,SDL_Renderer *renderer);
    SDL_Texture *get_texture(texture_id t_id);
    ptr_sequence_information get_sequence_information(texture_id t_id,sequence_id s_id);

    bool existSeqID(texture_id t,sequence_id s)
    {
        ptr_sprite_sequence_map my_sprite_map;
        my_sprite_map=sequence_map.find(t)->second;
        return !(my_sprite_map->find(s)==my_sprite_map->end());

    }



};

#endif // CTEXTUREMANAGER_H
