#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constante.h"
#include "controle.h"
#include "jouer.h"


int main ( int argc, char** argv )
{
    Entree in;
    memset(&in,0,sizeof(in));



    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *ecran=NULL, *menu=NULL, *dinostart;
    SDL_Rect positionMenu, positionDinoStart;

    menu=IMG_Load("fond.png");
    positionMenu.x=0;
    positionMenu.y=0;

    dinostart=IMG_Load("dinostart.png");
    positionDinoStart.x=100;
    positionDinoStart.y=650;

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE| SDL_FULLSCREEN | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Dinogame", NULL);
    SDL_ShowCursor(SDL_DISABLE);

    while(!in.key[SDLK_ESCAPE] && !in.quit)
	{
		Evenement(&in);
		if (in.key[SDLK_SPACE])
        {
            in.key[SDLK_SPACE]=0;
            SDL_FreeSurface(dinostart);
            SDL_Flip(ecran);
            jouer(ecran);
        }
        SDL_BlitSurface(menu,NULL,ecran,&positionMenu);
        SDL_BlitSurface(dinostart,NULL,ecran,&positionDinoStart);
        SDL_Flip(ecran);

    }

    SDL_FreeSurface(menu);
    SDL_Quit();
    return 0;

}
