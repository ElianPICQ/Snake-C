#include "../header/header.h"


s_Serpent	*create_elem(int x, int y)
{
	s_Serpent	*new_list;

	new_list = malloc(sizeof(s_Serpent));

	if (new_list)
	{
		new_list->morceauCorps.x = x;
		new_list->morceauCorps.y = y;
		new_list->morceauCorps.w = SQUARE_SIZE;
		new_list->morceauCorps.h = SQUARE_SIZE;

		new_list->suivant = NULL;
	}
	else
	{
		// GESTION DES ERREURS
	}

	return (new_list);
}

// Utilisée pour ajouter un bout de Snake -> Quand il mange des pommes
void	list_push_front(s_Tete	**Tete, int x, int y)
{
	s_Serpent	*newelem;

	newelem = create_elem(x, y);
	newelem->suivant = (*Tete)->premier;
	(*Tete)->premier = newelem;
}

// Utilisée initialiser le Snake
void	list_push_back(s_Tete **Tete)
{
	s_Serpent *newelem;

	newelem = (*Tete)->premier;

	while (newelem->suivant != NULL)
		newelem = newelem->suivant;

	newelem->suivant = create_elem(newelem->morceauCorps.x - SQUARE_SIZE, newelem->morceauCorps.y);
}

// Libère la mémoire allouée (malloc) pour le Serpent
// Et le détruit complètement
void	delete_snake(s_Tete	**Tete)
{
	s_Serpent	*tmp;
	s_Serpent	*list;

	list = (*Tete)->premier;
	tmp = NULL;

	while (list)
	{
		if (list->suivant)
			tmp = list->suivant;
		else
			tmp = NULL;
		free(list);
		list = tmp;
	}

	*Tete = NULL;
}

// Libère la mémoire allouée (malloc) pour le Serpent
// Laisse la Tête et le 1er Element
void	reset_snake(s_Tete	**Tete, int x, int y)
{
	s_Serpent	*tmp;
	s_Serpent	*list;

	list = (*Tete)->premier;
	tmp = NULL;

	list = list->suivant;
	while (list)
	{
		if (list->suivant)
			tmp = list->suivant;
		else
			tmp = NULL;
		free(list);
		list = tmp;
	}
	list = (*Tete)->premier;
	list->suivant = NULL;
	list->morceauCorps.x = x;
	list->morceauCorps.y = y;
}


void	ft_switch(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}


void	move_snake(s_Tete **Tete, int direction, SDL_bool *game_launched, s_Pomme *Pomme, int *pommesAManger, SDL_bool *is_game_over, int *pommesMangees)
{
	s_Serpent *Serpent;
	int x, y;
	SDL_bool grandit = SDL_FALSE;

	Serpent = (*Tete)->premier;
	x = Serpent->morceauCorps.x;
	y = Serpent->morceauCorps.y;

	if (direction)
	{
		switch (direction)
		{
			case UP:
				y -= SQUARE_SIZE;
				if (y < 0)
					y = WINDOW_HEIGHT - SQUARE_SIZE;
				break;
			case DOWN:
				y += SQUARE_SIZE;
				if (y > WINDOW_HEIGHT - SQUARE_SIZE)
					y = 0;
				break;
			case LEFT:
				x -= SQUARE_SIZE;
				if (x < 0)
					x = WINDOW_WIDTH - SQUARE_SIZE;
				break;
			case RIGHT:
				x += SQUARE_SIZE;
				if (x > WINDOW_WIDTH - SQUARE_SIZE)
					x = 0;
				break;

			default: break;
		}

		// On vérifie si on mange une pomme
		for (int i = 0; i < NB_POMMES; i++)
		{
			if (Pomme[i].infoPomme.x == Serpent->morceauCorps.x && Pomme[i].infoPomme.y == Serpent->morceauCorps.y)
			{
				*pommesMangees = *pommesMangees + 1;
				*pommesAManger = *pommesAManger - 1;

				// Déplacer la pomme en dehors du plateau
				Pomme[i].infoPomme.x = 0 - SQUARE_SIZE;
				Pomme[i].infoPomme.y = 0 - SQUARE_SIZE;

				// Si on a mangé toutes les pommes, on aggrandi le Serpent
				if (*pommesAManger == 0)
				{
					grandit = SDL_TRUE;
					list_push_front(Tete, x, y);
				}

				break;
			}
		}

		// On déplace le Serpent
		if (grandit == SDL_FALSE)
		{
			while (Serpent != NULL)
			{
				ft_switch(&x, &Serpent->morceauCorps.x);
				ft_switch(&y, &Serpent->morceauCorps.y);
				Serpent = Serpent->suivant;
			}
			Serpent = (*Tete)->premier;
		}

		// On stocke les coordonnées de la tête
		x = Serpent->morceauCorps.x;
		y = Serpent->morceauCorps.y;
		Serpent = Serpent->suivant;

		// On verifie si on ne s'est pas mangé
		while (Serpent != NULL)
		{
			if (x == Serpent->morceauCorps.x && y == Serpent->morceauCorps.y)
			{
				Serpent = NULL;
				*is_game_over = SDL_TRUE;
			}
			else if (Serpent->suivant)
				Serpent = Serpent->suivant;
			else
			{
				Serpent = (*Tete)->premier;
				break;
			}
		}
	}
}


void	dessiner_serpent(s_Tete **Tete, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font)
{
	s_Serpent *Serpent;

	Serpent = (*Tete)->premier;

	// On dessine la Tete d'une couleur légèrement différente
	if (SDL_SetRenderDrawColor(renderer, 35, 255, 35, SDL_ALPHA_OPAQUE) != 0)
	{
		delete_snake(Tete);
		exitWithError_5("Impossible de changer la couleur pour le Serpent", window, renderer, font);
	}
	if (SDL_RenderFillRect(renderer, &Serpent->morceauCorps) != 0)
	{
		delete_snake(Tete);
		exitWithError_5("Impossible de dessiner le rectangle", window, renderer, font);
	}
	Serpent = Serpent->suivant;

	// On dessine le reste du serpent
	if (SDL_SetRenderDrawColor(renderer, 150, 255, 50, SDL_ALPHA_OPAQUE) != 0)
	{
		delete_snake(Tete);
		exitWithError_5("Impossible de changer la couleur pour le Serpent", window, renderer, font);
	}
	while (Serpent != NULL)
	{
		if (SDL_RenderFillRect(renderer, &Serpent->morceauCorps) != 0)
		{
			delete_snake(Tete);
			exitWithError_5("Impossible de dessiner le rectangle", window, renderer, font);
		}
		Serpent = Serpent->suivant;
	}
}