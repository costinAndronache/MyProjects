#include "CAnimationInfo.h"
#include <cstring>
using namespace std;

extern void exit_error(char message[]);

CAnimationInfo::CAnimationInfo(texture_id tid,sequence_id sid,CTextureManager *pman)
{
    m_texture_id=tid;
    m_seq_id=sid;
    m_manager=pman;
    current_frame=-1;
    m_initial_run=0;



    if(!m_manager->existSeqID(tid,sid))
    {
        char ctid[10],csid[10];
        itoa(tid,ctid,10);
        itoa(sid,csid,10);
        char err[128]="No such sequence id in texture's map. <texture,seq> ";
        strcat(err,ctid);
        strcat(err,"  ");
        strcat(err,csid);
        exit_error(err);
    }

    m_sequence=m_manager->get_sequence_information(tid,sid);
    m_sequence_size=m_sequence->sprite_vector->size();
    m_timer.start_ticks();
}

void CAnimationInfo::change_sequence(sequence_id sid)
{
    m_seq_id=sid;
    current_frame=-1;
    m_initial_run=0;

    if(!m_manager->existSeqID(m_texture_id,sid))
    {
        char ctid[10],csid[10];
        itoa(m_texture_id,ctid,10);
        itoa(sid,csid,10);
        char err[128]="No such sequence id in texture's map. <texture,seq> ";
        strcat(err,ctid);
        strcat(err,"  ");
        strcat(err,csid);
        exit_error(err);
    }

    m_sequence=m_manager->get_sequence_information(m_texture_id,sid);
    m_sequence_size=m_sequence->sprite_vector->size();
    m_timer.start_ticks();
}

void CAnimationInfo::step_animation()
{
    if(m_timer.get_ElapsedTime()>=m_sequence->frame_delay)
    {
        if(current_frame==m_sequence_size-1)
            current_frame=m_sequence->loop_restart-1;

     ++current_frame;

     m_timer.start_ticks();
    }
}

SDL_Rect CAnimationInfo::get_CurrentFrame()
{
    int index= current_frame==-1?0:current_frame;
    return m_sequence->sprite_vector->at(index);

}
