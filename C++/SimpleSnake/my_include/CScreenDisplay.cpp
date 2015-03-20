#include "CScreenDisplay.h"

void CScreenDisplay::reinitialize(int width,int height,unsigned int flags)
{
    if(m_window && m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);

    }

    SDL_CreateWindowAndRenderer(width,height,flags,&m_window,&m_renderer);
    m_width=width;
    m_height=height;
}

CScreenDisplay::CScreenDisplay(int width,int height,unsigned int flags)
{
    m_window=NULL;
    m_renderer=NULL;
    SDL_CreateWindowAndRenderer(width,height,flags,&m_window,&m_renderer);
    m_width=width;
    m_height=height;
}
