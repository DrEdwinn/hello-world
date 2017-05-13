#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "controle.h"
#include "jouer.h"


void jouer(SDL_Surface *ecran)
{
    srand(time(NULL));
    SDL_Surface *fond1, *fond2, *dino[2], *dinoMort, *dinoSaut, *actuelDino, *cactus0, *cactus1, *cactus2, *cactus3, *cactus4;
    SDL_Rect positionFond1, positionFond2, positionDino, fondPart1, fondPart2, posCactus0, posCactus1, posCactus2, posCactus3, posCactus4, cactusPart0, cactusPart1, cactusPart2, cactusPart3, cactusPart4;
    int vitesse=50, compte=0, n=5, sauttime=0, gametime=0, ensaut=0, hauteurSaut=70, c0=1, c1=0, c2=0, c3=0, c4=0, nbCactusEnJeu=0, aleatoire=0, distanceCactus=0, mort=0;

    Entree in;
    memset(&in,0,sizeof(in));

    fond1 = IMG_Load("fond.png");
    fond2 = IMG_Load("fond.png");

    dino[0] = IMG_Load("dino0.png");
    dino[1] = IMG_Load("dino1.png");
    dinoSaut=IMG_Load("dinostart.png");
    dinoMort=IMG_Load("dinomort.png");

    cactus0=IMG_Load("cactus0.png");
    cactus1=IMG_Load("cactus1.png");
    cactus2=IMG_Load("cactus2.png");
    cactus3=IMG_Load("cactus3.png");
    cactus4=IMG_Load("cactus4.png");

    posCactus0.x=0;
    posCactus0.y=620;
    posCactus1.x=0;
    posCactus1.y=620;
    posCactus2.x=0;
    posCactus2.y=620;
    posCactus3.x=0;
    posCactus3.y=620;
    posCactus4.x=0;
    posCactus4.y=620;

    cactusPart0.x=0;
    cactusPart0.y=0;
    cactusPart0.h=100;
    cactusPart0.w=2200;
    cactusPart1.x=2200;
    cactusPart1.y=0;
    cactusPart1.h=100;
    cactusPart1.w=2200;
    cactusPart2.x=2200;
    cactusPart2.y=0;
    cactusPart2.h=100;
    cactusPart2.w=2200;
    cactusPart3.x=2200;
    cactusPart3.y=0;
    cactusPart3.h=100;
    cactusPart3.w=2200;
    cactusPart4.x=2200;
    cactusPart4.y=0;
    cactusPart4.h=100;
    cactusPart4.w=2200;

    positionDino.x=100;
    positionDino.y=650;

    positionFond1.x=0;
    positionFond1.y=0;
    positionFond2.x=1900;
    positionFond2.y=0;

    fondPart1.x=0;
    fondPart1.y=0;
    fondPart1.h=1000;
    fondPart1.w=1900;

    fondPart2.x=0;
    fondPart2.y=0;
    fondPart2.h=1000;
    fondPart2.w=1900;

    while(!in.key[SDLK_ESCAPE] && !in.quit)
    {
        Evenement(&in);
        if(in.key[SDLK_SPACE] || in.key[SDLK_UP])
        {
            in.key[SDLK_UP]=0;
            in.key[SDLK_SPACE]=0;
            if (!ensaut)
            {
                sauttime=SDL_GetTicks();   //On enregistre le moment où le joueur appuie sur la touche saut
                ensaut=1;
                actuelDino=dinoSaut;
            }

        }

        // defilement decor
        fondPart1.x+=vitesse;            //A chaque tour de la boucle while, le decor et les cactus bougent d'un certain nombre de pixels vers la gauche. Ce nombre de pixels est la vitesse.
        positionFond2.x-=vitesse;

        if(positionFond2.x<=0)
        {
            positionFond2.x=1900;
            fondPart1.x=0;
        }

        //defilement cactus
        if (cactusPart0.x<2200)
        {
            cactusPart0.x+=vitesse;
        }
        else
        {
            c0=0;
        }
        if (cactusPart1.x<2200)
        {
            cactusPart1.x+=vitesse;
        }
        else
        {
            c1=0;
        }
        if (cactusPart2.x<2200)
        {
            cactusPart2.x+=vitesse;
        }
        else
        {
            c2=0;
        }
        if (cactusPart3.x<2200)
        {
            cactusPart3.x+=vitesse;
        }
        else
        {
            c3=0;
        }
        if (cactusPart4.x<2200)
        {
            cactusPart4.x+=vitesse;
        }
        else
        {
            c4=0;
        }



        //vitesse du jeu
        compte+=1;                     //La vitesse augmente au fur et à mesure que la partie dure. Plus la partie dure, plus la vitesse augmente lentement.
        if (compte==n)
        {
            vitesse+=1;
            compte=0;
            n+=1;
        }

        //saut
        gametime=SDL_GetTicks();
        if(ensaut)
        {
            positionDino.y-=hauteurSaut;
        }
        if(gametime-sauttime>150)           //Si un certain temps s'est écoulé depuis le moment où le joueur a appuyé sur la touche saut, le dino retombe.
        {
            hauteurSaut=-70;
        }
        if(positionDino.y==650)
        {
            ensaut=0;
            hauteurSaut=70;
        }

        // generation aléatoire cactus
        nbCactusEnJeu=c0+c1+c2+c3+c4;
        distanceCactus+=vitesse;
        if (nbCactusEnJeu<2)                                                        //On tire un numéro pour savoir quel cactus entrera en jeu.
        {                                                                           // S'il n'est pas déjà en jeu et si la distance avec le dernier cactus est suffisante, il entre en jeu.
            aleatoire=(rand()%5);
            if(aleatoire==0 && c0==0 && distanceCactus>500)
            {
                cactusPart0.x=0;
                c0=1;
                distanceCactus=0;
            }
            if(aleatoire==1 && c1==0 && distanceCactus>500)
            {
                cactusPart1.x=0;
                c1=1;
                distanceCactus=0;
            }
            if(aleatoire==2 && c2==0 && distanceCactus>500)
            {
                cactusPart2.x=0;
                c2=1;
                distanceCactus=0;
            }
            if(aleatoire==3 && c3==0 && distanceCactus>1000)
            {
                cactusPart3.x=0;
                c3=1;
                distanceCactus=0;
            }
            if(aleatoire==4 && c4==0 && distanceCactus>1000)
            {
                cactusPart4.x=0;
                c4=1;
                distanceCactus=0;
            }
        }

        //Collision
        if ((cactusPart0.x>1975 && cactusPart0.x<2100 && positionDino.y>550))
        {
            mort=1;
        }

        if (cactusPart1.x>1950 && cactusPart1.x<2100 && positionDino.y>595)
        {
            mort=1;
        }
        if (cactusPart2.x>1970 && cactusPart2.x<2100 && positionDino.y>595)
        {
            mort=1;
        }
        if (cactusPart3.x>1925 && cactusPart3.x<2080 && positionDino.y>550)
        {
            mort=1;
        }
        if (cactusPart4.x>1885 && cactusPart4.x<2050 && positionDino.y>550)
        {
            mort=1;
        }

        if(!ensaut)
        {
            actuelDino=dino[(SDL_GetTicks()/100)%2];
        }
        if(mort)
        {
            actuelDino=dinoMort;
            vitesse=0;
            hauteurSaut=0;
            n=0;
        }
        SDL_BlitSurface(fond1, &fondPart1, ecran, &positionFond1);
        SDL_BlitSurface(fond2, &fondPart2, ecran, &positionFond2);
        SDL_BlitSurface(cactus0, &cactusPart0, ecran, &posCactus0);
        SDL_BlitSurface(cactus1, &cactusPart1, ecran, &posCactus1);
        SDL_BlitSurface(cactus2, &cactusPart2, ecran, &posCactus2);
        SDL_BlitSurface(cactus3, &cactusPart3, ecran, &posCactus3);
        SDL_BlitSurface(cactus4, &cactusPart4, ecran, &posCactus4);
        SDL_BlitSurface(actuelDino,NULL, ecran, &positionDino);
        SDL_Flip(ecran);
    }
    in.key[SDLK_ESCAPE]=0;
}



