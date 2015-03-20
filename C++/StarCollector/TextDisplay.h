#ifndef TEXTDISPLAY_H
    #define TEXTDISPLAY_H

#include "SDL_ttf.h"

class TextDisplay
{
    TTF_Font *font;
public:
    TextDisplay(){font=NULL;}
    ~TextDisplay(){if(font) TTF_CloseFont(font);}
    void initialize(char *pathfont,int ptsize);

    TextDisplay(char *path,int ptsize){initialize(path,ptsize);}

    void print(SDL_Surface *screen,int value,int x,int y,int r,int g,int b);
    void print(SDL_Surface *screen,char *text,int x,int y,int r,int g,int b);
};
#endif // TEXTDISPLAY_H
