#include "../header/header.h"


// Rendu du menu principal
int		menu_principal(SDL_Renderer	*renderer, TTF_Font *font, s_Game *Game)
{
	int i = 0;
	SDL_bool menu_principal = SDL_TRUE;
	SDL_Event event;
	SDL_Rect dstrect;

	char	*boutonTexte[] = {"MENU PRINCIPAL", "Lancer une partie", "Charger la sauvegarde", "Quitter", 0};
	int nbBtn = 0;

	while (boutonTexte[nbBtn] != 0)
		nbBtn++;

	int ecartBtn = 20;
	s_MenuBouton MenuBouton[nbBtn];
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface *surface;
	SDL_Texture *texture;

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

		if (i == 0)
		{
			MenuBouton[i].bouton.x = MenuBouton[i].bouton.h;
			MenuBouton[i].bouton.y = MenuBouton[i].bouton.h;
		}
		else
		{
			MenuBouton[i].bouton.x = WINDOW_WIDTH / 2 - MenuBouton[i].bouton.w / 2;
			MenuBouton[i].bouton.y = WINDOW_HEIGHT / 2 - (MenuBouton[i].bouton.h * nbBtn + ecartBtn * nbBtn) / 2 + (MenuBouton[i].bouton.h + ecartBtn) * (i - 1);
		}
		
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

	while (menu_principal)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				// Croix de fermeture
				case SDL_QUIT:
					menu_principal = SDL_FALSE;
					Game->program_launched = SDL_FALSE;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							menu_principal = SDL_FALSE;
							Game->program_launched = SDL_FALSE;
							break;

						case SDLK_RETURN:
							menu_principal = SDL_FALSE;
							Game->game_launched = SDL_TRUE;
							break;

						default: break;
					}
					break;

				// Clic sur un Bouton
				case SDL_MOUSEBUTTONDOWN:
					// Bouton Jouer
					if (MenuBouton[1].bouton.x <= event.motion.x && event.motion.x <= MenuBouton[1].bouton.x + MenuBouton[1].bouton.w
						&& MenuBouton[1].bouton.y <= event.motion.y && event.motion.y <= MenuBouton[1].bouton.y + MenuBouton[1].bouton.h)
					{
						printf("Jouer\n");
						menu_principal = SDL_FALSE;
						Game->game_launched = SDL_TRUE;
					}

					// Bouton Continuer (charger la sauvegarde)
					else if (MenuBouton[2].bouton.x <= event.motion.x && event.motion.x <= MenuBouton[2].bouton.x + MenuBouton[2].bouton.w
						&& MenuBouton[2].bouton.y <= event.motion.y && event.motion.y <= MenuBouton[2].bouton.y + MenuBouton[2].bouton.h)
					{
						printf("Btn Charger la Sauvegarde\n");
					}

					// Bouton Quitter
					else if (MenuBouton[3].bouton.x <= event.motion.x && event.motion.x <= MenuBouton[3].bouton.x + MenuBouton[3].bouton.w
						&& MenuBouton[3].bouton.y <= event.motion.y && event.motion.y <= MenuBouton[3].bouton.y + MenuBouton[3].bouton.h)
					{
						printf("Btn Quitter\n");
						menu_principal = SDL_FALSE;
						Game->program_launched = SDL_FALSE;
					}
					break;

				default: break;
			}		
		}
	}

	// Tout s'est bien passé -> 0
	return (0);
}