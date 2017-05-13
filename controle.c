#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "controle.h"

void Evenement(Entree *in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym]=0;
			break;
		}
	}
}


