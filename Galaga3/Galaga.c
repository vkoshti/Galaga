
#include "Representation.h"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <SDL2/SDL_image.h>



rivals * allocateMemoryForRival(rivals *r)
{
    r = (rivals*)malloc(sizeof(rivals));

    if(r == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    return r;
}

tank *allocateMemoryForTank(tank *t)
{
    t = malloc((sizeof(tank)));
    if(t == NULL)
    {
        printf("Error allocating memory\n");
        return NULL;
    }
    return t;
}

Score *allocateMemoryForScore(Score *score)
{
    score = malloc(sizeof(score));
    if(score == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    return score;

}



void deallocate(rivals *rival,tank *t,Score *score)
{
    free(rival);
    free(t);
    free(score);
}

void handleEvent(SDL_Event *event,tank *t,bullet *b,int *fire)
{
    if(event->type == SDL_KEYDOWN)
    {
        switch(event->key.keysym.sym)
        {
            case SDLK_a:  t->x-=20;break;
            case SDLK_d: t->x+=20;break;
            case SDLK_SPACE : b->x = t->x+(t->w/2);b->y = t->y;*fire = 1;break;
        }
    }
    if(t->x<0)
    {
        t->x = 0;
    }
    if(t->x>540)
    {
        t->x = 540;
    }
}

int checkCollision(bullet *b,rivals *b2)
{
    int leftofb=b2->x ,rightofb =b2->x+b2->w , bottomofa=b->y,bottomofb=b2->y+b2->h , topofa= b->y-b->length , topofb=b2->y;
    int leftofa = b->x;
    int rightofa = b->x;
    if(rightofb<leftofa)
    {
        return false;
    }
    else if(leftofb>rightofa)
    {
        return false;
    }
    else{
        if( bottomofb<topofa)
        {
            return false;
        }
        else if(topofb>bottomofa)
        {
            return false;
        }
        else{

            return true;
        }
    }

}

void render(SDL_Renderer *renderer,rivals *rival,rivals *rival2,tank *t)
{
    SDL_Rect p = {t->x,t->y,t->w,t->h};
    SDL_Rect r = {rival->x,rival->y,rival->w,rival->h};
    SDL_Rect r1 = {rival2->x,rival2->y,rival2->w,rival2->h};
    SDL_RenderCopy(renderer,t->tanktexture,NULL,&p);
    SDL_RenderCopy(renderer,rival->rivaltexture,NULL,&r);
    SDL_RenderCopy(renderer,rival2->rivaltexture,NULL,&r1);
}

void renderBullet(SDL_Renderer *renderer,bullet *b,tank *t,rivals *rival,rivals *rival2,int *fire,Score *score)
{
    SDL_SetRenderDrawColor(renderer,0xff,0xff,0x00,0x00);
    SDL_RenderDrawLine(renderer,b->x,b->y,b->x,b->y-10);
    if(checkCollision(b,rival)){updateRival1(rival,score);setUpBullet(b);fire=0;score->hit+=1;}
    if(checkCollision(b,rival2)){updateRival2(rival2,score);setUpBullet(b);fire=0;score->hit+=1;}
    b->y-=15;
}

int main(int argc,char **argv)
{
    int quit = 1;
    int fire = 0;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    rivals *rival ;
    rivals *rival2;
    tank *t;
    Score *score;
    SDL_Event event;
    SDL_Rect backgroundrect = {0,600,600,600};
    SDL_Rect backgroundrect2 = {0,0,600,600};
    SDL_Texture *backgroundtexture = NULL ;
    SDL_Texture *backgroundtexture2 = NULL;
    bullet *b = malloc(sizeof(bullet));
    if(b==NULL)
    {
        printf("Memory initialization failed\n");
        return 1;
    }
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("Error SDL could not initialize\n");
        return 1;
    }
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&window,&renderer);
    if(window==NULL || renderer==NULL)
    {
        printf("Error loading window or renderer\n");
        return 1;
    }
    if((rival = allocateMemoryForRival(rival))==NULL)
    {
        printf("Error can not allocate memory\n");
        return 1;
    }
        if((rival2 = allocateMemoryForRival(rival2))==NULL)
    {
        printf("Error can not allocate memory\n");
        return 1;
    }
    if((t = allocateMemoryForTank(t))==NULL)
    {
        printf("Error can not allocate memory\n");
        return 1;
    }
    if((score=allocateMemoryForScore(score))==NULL)
    {
        return 1;
    }
    if(!loadRivals(rival,"resources/plane3.jpg",renderer))
    {
        printf("Error loading rivals\n");
        return 1;
    }
    if(!loadRivals(rival2,"resources/plane3.jpg",renderer))
    {
        printf("Error loading rivals\n");
        return 1;
    }
    if (!loadTank(t ,"resources/tank.jpg",renderer))
    {
        printf("Error loading images\n");
        return 1;
    }
    if((backgroundtexture=loadBackground(renderer))==NULL)
    {
        printf("Error loading background\n");
        return 1;
    }
    if((backgroundtexture2=loadBackground(renderer))==NULL)
    {
        printf("Error loading background\n");
        return 1;
    }

    setUpScore(score);
    updateRival1(rival,score);
    updateRival2(rival2,score);


    while(quit)
    {
        if(SDL_PollEvent(&event)>0)
        {
            if(event.type == SDL_QUIT || event.key.keysym.sym==SDLK_ESCAPE)
            {
                quit = 0;
            }
            handleEvent(&event,t,b,&fire);
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,backgroundtexture2,NULL,&backgroundrect2);
        SDL_RenderCopy(renderer,backgroundtexture,NULL,&backgroundrect);
        moveRivals1(rival,score);
        moveRivals2(rival2,score);
        render(renderer,rival,rival2,t);
        if(fire == 1)
        {
            renderBullet(renderer,b,t,rival,rival2,&fire,score);
        }
        SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xff);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        if(score->displayed==20)
        {
            quit = 0;
        }
        backgroundrect.y-=1;
        backgroundrect2.y-=1;
        if(backgroundrect2.y<=0)
        {
            backgroundrect.y = 0;
            backgroundrect2.y = 600;
        }

    }
    printf("Destroyed : %d\nMissed : %d\n",score->hit,score->displayed-score->hit);
    deallocate(rival,t,score);
    return 0;

}
