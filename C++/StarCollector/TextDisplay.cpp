#include "TextDisplay.h"

void TextDisplay::print(SDL_Surface *screen,int value,int x,int y,int r,int g,int b)
{
    SDL_Surface *textsurface;
    SDL_Color color={r,g,b};
    char ch[10];
    itoa(value,ch,10);
    textsurface=TTF_RenderText_Solid(font,ch,color);
    SDL_Rect pos={x,y,0,0};

    SDL_BlitSurface(textsurface,NULL,screen,&pos);
    SDL_FreeSurface(textsurface);
}

void TextDisplay::print(SDL_Surface *screen,char *text,int x,int y,int r,int g,int b)
{
    SDL_Surface *textsurface;
    SDL_Color color={r,g,b};

    textsurface=TTF_RenderText_Solid(font,text,color);
    SDL_Rect pos={x,y,0,0};

    SDL_BlitSurface(textsurface,NULL,screen,&pos);
    SDL_FreeSurface(textsurface);
}

void TextDisplay::initialize(char *pathfont,int ptsize)
{
    font=TTF_OpenFont(pathfont,ptsize);

}
