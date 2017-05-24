

#ifndef REPRESENTATION
#define REPRESENTATION

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>


/*Struct that defines rival planes
** This contains information about x and y coordinates
** Width and height of plane
** Collider box that is used to detect collision with bullet
*/
typedef struct rivals
{
    int x ,y , w , h;
    SDL_Rect collider;
    SDL_Texture *rivaltexture;
}rivals;

typedef struct tank
{
    int x,y,w,h;
    SDL_Texture *tanktexture;
}tank;

typedef struct bullet
{
    int x,y,length,bullets;
}bullet;

typedef struct Score
{
    int displayed;
    int hit;
}Score;

typedef struct background
{
    SDL_Texture *backgroundtexture;
}background;

bool loadRivals(rivals *,char *,SDL_Renderer *);
bool loadTank(tank *,char *,SDL_Renderer *);
bool setUpBullet(bullet *);
SDL_Texture *loadBackground(SDL_Renderer *);
void setUpScore(Score *);
void updateRival1(rivals *,Score *);
void updateRival2(rivals *,Score *);
void moveRivals1(rivals *,Score *);
void moveRivals2(rivals *,Score *);

#endif // REPRESENTATION
