#ifndef CANIMATIONINFO_H
    #define CANIMATIONINFO_H

#include "CTextureManager.h"
#include "CTimer.h"



class CAnimationInfo
{
    texture_id m_texture_id;
    sequence_id m_seq_id;

    int current_frame;
    ptr_sequence_information m_sequence;
    CTextureManager *m_manager;

    int m_initial_run;
    int m_sequence_size;
    CTimer m_timer;

public:
    CAnimationInfo(texture_id,sequence_id,CTextureManager*);
    void change_sequence(sequence_id);
    void step_animation();

    void reset(){current_frame=0;m_initial_run=0;}
    SDL_Texture *get_Texture(){return m_manager->get_texture(m_texture_id);};
    SDL_Rect get_CurrentFrame();

};
#endif // CANIMATIONINFO_h
