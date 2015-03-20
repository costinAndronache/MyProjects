#include "ResourceBank.h"
#include<fstream>

ResourceBank *ResourceBank::instance=NULL;

ResourceBank* ResourceBank::get_instance()
{
    if(!instance)
       instance=new ResourceBank();
    return instance;


}

void ResourceBank::initialize()
{
    std::ifstream f("MainFile.txt");
    char mainsheetfile[30],mainspritelist[30];
    f>>mainsheetfile>>mainspritelist;
    f.close();

    std::ifstream sheetfile(mainsheetfile);
    sheetfile>>num_of_sheets;
    for(int i=0;i<num_of_sheets;i++)
    {
        char address[30];
        sheetfile>>address;
        sheets[i]=IMG_Load(address);
    }
    sheetfile.close();

    std::ifstream spritefilelist(mainspritelist),current;
    for(int i=0;i<num_of_sheets;i++)
    {
        char address[30];
        spritefilelist>>address;
        current.open(address);

        int num_rows,k,j,num_cols;
        SDL_Rect rect1;
        current>>num_rows;
        for(k=0;k<num_rows;k++)
        {
            current>>num_cols;
            frames[i][k]=num_cols;
            for(j=0;j<num_cols;j++)
            {
                current>>rect1.x>>rect1.y>>rect1.w>>rect1.h;
                sprites[i][k][j]=rect1;
            }
        }

        current.close();

    }
    spritefilelist.close();
}

SDL_Surface *ResourceBank::getSurface(int surface)
{
    return sheets[surface];
}

SDL_Rect ResourceBank::getSprite(int sheet,int x,int y)
{
    return sprites[sheet][x][y];
}

int ResourceBank::get_frames(int sheet,int row)
{
    return frames[sheet][row];
}
