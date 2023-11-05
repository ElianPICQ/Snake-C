#include "../header/header.h"


int		pause(SDL_Window	*window, SDL_Renderer	*renderer, TTF_Font *font, s_Game *Game)
{
	int i = 0;
	SDL_bool game_paused = SDL_TRUE;
	SDL_Event event;
	SDL_Rect dstrect = {WINDOW_WIDTH / 2 - WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - (WINDOW_HEIGHT / 2 + WINDOW_HEIGHT / 4) / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + WINDOW_HEIGHT / 4};

	char	*boutonTexte[] = {"PAUSE", "Continuer", "Sauvegarder", "Quitter", 0};
	int nbBtn = 0;

	while (boutonTexte[nbBtn] != 0)
		nbBtn++;

	int ecartBtn = 20;
	s_MenuBouton MenuBouton[nbBtn];
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface *surface;
	SDL_Texture *texture;


	// On met tout dans un rectangle transparent qui ne prend pas tout l'écran
	if (SDL_SetRenderDrawColor(renderer, 50, 50, 50, 170) != 0)
	{
		SDL_Log("ERREUR : Impossible de changer la couleur pour le menu Pause > %s", SDL_GetError());
		return (-1);
	}
	if (SDL_RenderFillRect(renderer, &dstrect) != 0)
	{
		SDL_Log("ERREUR : Impossible de creer le fond du menu Pause > %s", SDL_GetError());
		return (-1);
	}

	while (boutonTexte[i] != 0)
	{
		surface = TTF_RenderText_Solid(font, boutonTexte[i], color);
		if (surface == NULL)
		{
			SDL_Log("ERREUR : Impossible de créer la Surface > %s", SDL_GetError());
			return (-1);
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
		{
			SDL_Log("ERREUR : Impossible de créer la Texture > %s", SDL_GetError());
			return (-1);
		}

		if (SDL_QueryTexture(texture, NULL, NULL, &MenuBouton[i].bouton.w, &MenuBouton[i].bouton.h) != 0)
		{
			SDL_Log("ERREUR : La fonction SDL_QueryTexture a echoue > %s", SDL_GetError());
			return (-1);
		}

		// Centrer tous les boutons
		MenuBouton[i].bouton.x = WINDOW_WIDTH / 2 - MenuBouton[i].bouton.w / 2;
		MenuBouton[i].bouton.y = WINDOW_HEIGHT / 2 - (MenuBouton[i].bouton.h * nbBtn + ecartBtn * nbBtn) / 2 + (MenuBouton[i].bouton.h + ecartBtn) * (i - 1);
		
		if (SDL_RenderCopy(renderer, texture, NULL, &MenuBouton[i].bouton) != 0)
		{
			SDL_Log("ERREUR : La fonction SDL_RenderCopy a echoue > %s", SDL_GetError());
			return (-1);
		}

		i++;
	}

	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

	while (game_paused)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				// Croix de fermeture
				case SDL_QUIT:
					game_paused = SDL_FALSE;
					Game->game_launched = SDL_FALSE;
					Game->program_launched = SDL_FALSE;
					break;

				// Event clavier
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						// Quitter le programme -> Changer "Menu Pause"
						case SDLK_ESCAPE:
							game_paused = SDL_FALSE;
							break;

						default: break;
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					// Bouton Continuer
					if (MenuBouton[1].bouton.x <= event.motion.x && event.motion.x <= MenuBouton[1].bouton.x + MenuBouton[1].bouton.w
						&& MenuBouton[1].bouton.y <= event.motion.y && event.motion.y <= MenuBouton[1].bouton.y + MenuBouton[1].bouton.h)
					{
						printf("Bouton Continuer\n");
						game_paused = SDL_FALSE;
					}
					// Bouton Sauvegarder
					else if (MenuBouton[2].bouton.x <= event.motion.x && event.motion.x <= MenuBouton[2].bouton.x + MenuBouton[2].bouton.w
						&& MenuBouton[2].bouton.y <= event.motion.y && event.motion.y <= MenuBouton[2].bouton.y + MenuBouton[2].bouton.h)
					{
						printf("Bouton Sauvegarder\n");
					}
					// Bouton Quitter
					else if (MenuBouton[3].bouton.x <= event.motion.x && event.motion.x <= MenuBouton[3].bouton.x + MenuBouton[3].bouton.w
						&& MenuBouton[3].bouton.y <= event.motion.y && event.motion.y <= MenuBouton[3].bouton.y + MenuBouton[3].bouton.h)
					{
						printf("Bouton Quitter\n");
						game_paused = SDL_FALSE;
						Game->game_launched = SDL_FALSE;
						Game->program_launched = SDL_FALSE;
					}

				default: break;
			}
		}
	}

	// On remet la couleur en noir pour le prochain rendu
	if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
	{
		SDL_Log("ERREUR : Impossible de changer la couleur pour le menu Pause > %s", SDL_GetError());
		return (-1);
	}
	return (0);
}