#include "../header/header.h"


void	initialise_pommes(s_Pomme *Pomme)
{
	for (int i = 0; i < NB_POMMES; i++)
	{
		// On met les pommes à l'exterieur de l'ecran pour éviter quelconque conflit
		Pomme[i].infoPomme.x = 0 - SQUARE_SIZE;
		Pomme[i].infoPomme.y = 0 - SQUARE_SIZE;
		Pomme[i].infoPomme.w = SQUARE_SIZE;
		Pomme[i].infoPomme.h = SQUARE_SIZE;
	}
}

int		checkPositionPomme(s_Pomme *Pomme, int i, s_Tete **Tete)
{
	s_Serpent	*Serpent;

	Serpent = (*Tete)->premier;
	// On ne veut pas mettre de pomme dans un bloc de Serpent
	while (Serpent != NULL)
	{
		if (Pomme[i].infoPomme.x == Serpent->morceauCorps.x && Pomme[i].infoPomme.y == Serpent->morceauCorps.y)
			return (0);
		Serpent = Serpent->suivant;
	}

	// On ne veut pas mettre de pomme là où il y en a déjà
	for (int a = 0; a < NB_POMMES; a++)
	{
		if (a == i)
			a++;
		else if (Pomme[i].infoPomme.x == Pomme[a].infoPomme.x && Pomme[i].infoPomme.y == Pomme[a].infoPomme.y)
				return (0);
	}
	return (1);
}

void	placer_pommes(s_Tete **Tete, SDL_Renderer **renderer, SDL_Window **window, s_Pomme *Pomme)
{
	int plateauWidth, plateauHeight;
	int i = 0;

	plateauWidth = WINDOW_WIDTH / SQUARE_SIZE;
	plateauHeight = WINDOW_HEIGHT / SQUARE_SIZE;

	// Placer les Pommes sur le Plateau
	while (i < NB_POMMES)
	{
		Pomme[i].infoPomme.x = (rand() % plateauWidth) * SQUARE_SIZE;
		Pomme[i].infoPomme.y = (rand() % plateauHeight) * SQUARE_SIZE;

		// Refixe width & height pour corriger un bug
		// Dans certains cas, height de la dernière pomme était égal à
		// un nombre négatif très élevé (???)
		Pomme[i].infoPomme.w = SQUARE_SIZE;
		Pomme[i].infoPomme.h = SQUARE_SIZE;


		// checkPositionPomme renvoie 1 si la position est correcte
		if (checkPositionPomme(Pomme, i, Tete) == 1)
			i++;
	}
}

void	dessiner_pommes(s_Tete **Tete, SDL_Renderer **renderer, SDL_Window **window, s_Pomme *Pomme, TTF_Font **font)
{
	// Couleur Pommes (Vert)
	if (SDL_SetRenderDrawColor(*renderer, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0)
	{
		delete_snake(Tete);
		exitWithError_5("Impossible de changer la couleur pour les pommes", window, renderer, font);
	}

	for (int i = 0; i < NB_POMMES; i++)
	{
		if (SDL_RenderFillRect(*renderer, &Pomme[i].infoPomme) != 0)
		{
			delete_snake(Tete);
			exitWithError_5("Impossible de dessiner la pomme", window, renderer, font);
		}
	}
}