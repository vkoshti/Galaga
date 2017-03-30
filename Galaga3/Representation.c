#include "Representation.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

bool loadRivals(rivals * rival ,char *path,SDL_Renderer *renderer)
{
    SDL_Surface *rivalsurface  = NULL;
    SDL_Texture *rivaltexture = NULL;
    rivalsurface = IMG_Load(path);
    if(rivalsurface==NULL)
    {
        printf("Error loading rivals :  %s\n",IMG_GetError());
        return false;
    }
    rivaltexture = SDL_CreateTextureFromSurface(renderer,rivalsurface);
    if(rivaltexture==NULL)
    {
        printf("Error loading rival : %s\n",IMG_GetError());
        return false;
    }
    rival->x = 0;
    rival->y = 0;
    rival->w = rivalsurface->w;
    rival->h = rivalsurface->h;
    rival->collider.x = 0;
    rival->collider.y = 0;
    rival->collider.w = rival->w;
    rival->collider.h = rival->h;
    rival->rivaltexture = rivaltexture;
    return true;
}

bool loadTank(tank *t , char *path,SDL_Renderer *renderer)
{
    SDL_Surface *tanksurface  = NULL;
    SDL_Texture *tanktexture = NULL;
    tanksurface = IMG_Load(path);
    if(tanksurface==NULL)
    {
        printf("Error loading rivals :  %s\n",IMG_GetError());
        return false;
    }
    tanktexture = SDL_CreateTextureFromSurface(renderer,tanksurface);
    if(tanktexture==NULL)
    {
        printf("Error loading rival : %s\n",IMG_GetError());
        return false;
    }
    t->x = 300;
    t->y = 540;
    t->w = tanksurface->w;
    t->h = tanksurface->h;
    t->tanktexture = tanktexture;
    return true;
}


SDL_Texture* loadBackground(SDL_Renderer *renderer)
{
    SDL_Texture *backtexture = NULL;
    SDL_Surface *backgroundsurface = IMG_Load("resources/background.jpg");
    if(backgroundsurface==NULL)
    {
        printf("Error while loading image : %s",IMG_GetError());
        return NULL;
    }
    backtexture = SDL_CreateTextureFromSurface(renderer,backgroundsurface);
    SDL_FreeSurface(backgroundsurface);
    return backtexture;
}


void setUpScore(Score *score)
{
    score->displayed = 0;
    score->hit = 0;
}
bool setUpBullet(bullet *b)
{
    b->x = 0;
    b->y = 0;
    b->length = 10;
    b->bullets = 4;
    return true;
}

void updateRival1(rivals *rival,Score *score)
{
    rival->x = rand()%270;
    rival->y = -200;
    score->displayed+=1;

}

void updateRival2(rivals *rival,Score *score)
{
    rival->x = 300 + (rand() % (int)(540 - 300 + 1));
    rival->y = -200;
    score->displayed+=1;
}

void moveRivals1(rivals *rival,Score *score)
{
    rival->y +=2;
    if(rival->y>=400)
    {
        updateRival1(rival,score);
    }
}


void moveRivals2(rivals *rival,Score *score)
{
    rival->y +=3;
    if(rival->y>=400)
    {
        updateRival2(rival,score);
    }
}
