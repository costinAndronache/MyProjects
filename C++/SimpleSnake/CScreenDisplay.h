#ifndef CSCREENDISPLAY_H
    #define CSCREENDISPLAY_H

    #include "SDL.h"



class CScreenDisplay
{

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_width,m_height;

public:

    CScreenDisplay(int width,int height,unsigned int flags);
    SDL_Renderer *get_Renderer(){return m_renderer;}
    void reinitialize(int width,int height,unsigned int flags);

    int get_Width(){return m_width;}
    int get_Height(){return m_height;}

    int print_Texture(SDL_Texture *texture,SDL_Rect *screen_location,SDL_Rect *crop_area)
                        {

                            return SDL_RenderCopy(m_renderer,texture,crop_area,screen_location);
                        }
    void refresh()
                        {

                            SDL_RenderPresent(m_renderer);
                        }

    void clear()
    {
        SDL_SetRenderDrawColor(m_renderer,0,0,0,0);
        SDL_RenderClear(m_renderer);
    }

    ~CScreenDisplay(){SDL_DestroyWindow(m_window);SDL_DestroyRenderer(m_renderer);}
};
#endif // CSCREENDISPLAY_H
