#include "CTextureManager.h"


#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void exit_error(char message[])
{
        //std::ofstream g("ERROR_CTEXT.txt");
        std::cout<<message;
        //g.close();
        exit(0);

}

void CTextureManager::read_sprite_data(char *path)
{
    if(!path)
        exit_error("Null pointer in read sprite data");

    ifstream f(path);
    if(f.fail())
    {
        char err[128]="could not open the sprite data file ";
        strcat(err,path);
        exit_error(err);
    }

    texture_id t_id;
    int n_of_seqs;

    f>>t_id>>n_of_seqs;

    if(texture_map.find(t_id)==texture_map.end())
    {
        char err[128]="id not found in the sprite data file ";
        strcat(err,path);
        exit_error(err);
    }

    ptr_sprite_sequence_map pmap=new sprite_sequence_map;

    for(int i=1;i<=n_of_seqs;i++)
    {
        sequence_id seq_id;
        int n_of_sprites;
        ptr_sprite_sequence p=NULL;
        SDL_Rect rect;
        int framedelay,loop_restart;

        f>>seq_id>>n_of_sprites>>framedelay>>loop_restart;

        if(loop_restart>=n_of_sprites)
        {
            char err[300]="Loop restart too high. Numbering starts from 0. <SeqId,SpriteFile> ";
            char ch[9];
            itoa(seq_id,ch,10);
            strcat(err,ch);
            strcat(err,path);
            exit_error(err);
        }
        if(pmap->find(seq_id)!=pmap->end())
        {
            char err[256]="multiple sequence id in sprite data file:  ";
            strcat(err,path);
            char num[16];
            itoa(seq_id,num,10);
            strcat(err,num);
            exit_error(err);
        }


        p=new sprite_sequence;
        for(int k=1;k<=n_of_sprites;k++)
        {
            f>>rect.x>>rect.y>>rect.w>>rect.h;
            p->push_back(rect);
        }

        sequence_information inf;
        inf.frame_delay=framedelay;
        inf.loop_restart=loop_restart;
        inf.sprite_vector=p;
        pmap->insert(make_pair(seq_id,inf));


    }

    sequence_map.insert(make_pair(t_id,pmap));

    f.close();




}

SDL_Texture *create_texture(char *file,SDL_Renderer *renderer)
{
    SDL_Surface *surface=NULL;
    surface=IMG_Load(file);
    if(!surface)
        return NULL;
    return SDL_CreateTextureFromSurface(renderer,surface);
}


void CTextureManager::reinitialize(char *mainfile,SDL_Renderer *renderer)
{
    free_textures();
    free_vectors();
    texture_map.clear();
    sequence_map.clear();
    if(!mainfile)
        exit_error("null pointer to mainfile");

    if(!renderer)
        exit_error("null renderer");

    associated_renderer=renderer;

    char image_paths[50],sprite_paths[50];

    ifstream mainf(mainfile);

    if (mainf.fail())
     exit_error("error in opening the main file");


    mainf>>image_paths>>sprite_paths;

    mainf.close();

    ifstream imp_file(image_paths);

    if(imp_file.fail())
        exit_error("The image paths file does not exist or it is corrupted.");


    while(!imp_file.eof())
    {
        int id;
        char path[50];

        imp_file>>id>>path;
        SDL_Texture *ptext=create_texture(path,associated_renderer);

        if(!ptext)
        {
            char err[50]="could not load the texture with id: ";
            char num[10];
            itoa(id,num,10);
            strcat(err,num);
            exit_error(err);
        }

        if(texture_map.find(id)!=texture_map.end())
        {
            char err[50]="multiple texture id ";
            char num[10];
            itoa(id,num,10);
            strcat(err,num);
            exit_error(err);
        }

        texture_map.insert(make_pair(id,ptext));

    }


    imp_file.close();

    ifstream spp_file(sprite_paths);

    if(spp_file.fail())
        exit_error("could not open sprite paths file");




    char sprite_file_path[50];

    while(!spp_file.eof())
    {
     spp_file>>sprite_file_path;
     read_sprite_data(sprite_file_path);

    }


}



SDL_Texture *CTextureManager::get_texture(texture_id t_id)
{
    map<texture_id,SDL_Texture*>::iterator it=texture_map.find(t_id);

    if(it==texture_map.end())
        return NULL;
    return it->second;
}

ptr_sequence_information CTextureManager::get_sequence_information(texture_id t_id,sequence_id s_id)
{
    map<texture_id, ptr_sprite_sequence_map >::iterator it=sequence_map.find(t_id);
    if(it==sequence_map.end())
     return NULL;

 sprite_sequence_map::iterator it2=it->second->find(s_id);
     if(it2==it->second->end())
        return NULL;


     return &it2->second;
}

void CTextureManager::free_textures()
{
    map<texture_id, SDL_Texture*>::iterator it=texture_map.begin(),
                                              it_stop=texture_map.end();


    while(it!=it_stop)
    {
        SDL_DestroyTexture(it->second);
        it++;
    }
}

void CTextureManager::free_vectors()
{
    map<texture_id, ptr_sprite_sequence_map >::iterator it=sequence_map.begin(),
                                                          stop=sequence_map.end();

    while(it!=stop)
    {
        delete it->second;
        it++;
    }
}

CTextureManager::~CTextureManager()
{
    free_textures();
    free_vectors();
    texture_map.clear();
    sequence_map.clear();
}
