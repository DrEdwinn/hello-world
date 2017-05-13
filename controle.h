#ifndef CONTROLE_H_INCLUDED
#define CONTROLE_H_INCLUDED

typedef struct
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
    char quit;
} Entree;

void Evenement(Entree *in);


#endif // CONTROLE_H_INCLUDED
