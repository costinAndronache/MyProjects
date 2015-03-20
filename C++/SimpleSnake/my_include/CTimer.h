#ifndef CTIMER_H

    #define CTIMER_H

    #include "SDL.h"

class CTimer
{
    unsigned int m_start;
    unsigned int m_stop;
    unsigned int m_delta;
public:

    CTimer(){m_start=m_stop=0;}

    void start_ticks(){m_start=SDL_GetTicks();}
    void stop_ticks(){m_stop=SDL_GetTicks();}

int get_ElapsedTime()
{
    return SDL_GetTicks()- m_start;
}
};
#endif // CTIMER_H
