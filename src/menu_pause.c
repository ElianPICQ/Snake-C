#include "../header/header.h"


void	pause(SDL_Window	*window, SDL_Renderer	*renderer, TTF_Font *font, SDL_bool *game_launched, SDL_bool *program_launched)
{
	SDL_bool game_paused = SDL_TRUE;
	// Couleur du crayon
	SDL_Color color = { 255, 255, 255 };
	// Taille des boites de texte
	int TextW, TextH;
	SDL_Event event;
	SDL_Rect dstrect = {WINDOW_WIDTH / 2 - WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - (WINDOW_HEIGHT / 2 + WINDOW_HEIGHT / 4) / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + WINDOW_HEIGHT / 4};

	// On met tout dans un rectangle noir qui ne prend pas tout l'écran
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

	// Texte "Pause"
	SDL_Surface *surface = TTF_RenderText_Solid(font, "PAUSE", color);
	if (surface == NULL)
	{
		SDL_Log("ERREUR : Impossible de créer la Surface > %s", SDL_GetError());
		return (-1);
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		SDL_Log("ERREUR : Impossible de créer la Texture > %s", SDL_GetError());
		return (-1);
	}
	if (SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_QueryTexture a echoue > %s", SDL_GetError());
		return (-1);
	}
	dstrect.x = WINDOW_WIDTH / 2 - TextW / 2;
	dstrect.y = WINDOW_HEIGHT / 3 - TextH / 2;
	dstrect.w = TextW;
	dstrect.h = TextH;
	if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_RenderCopy a echoue > %s", SDL_GetError());
		return (-1);
	}

	// Bouton "Continuer"
	surface = TTF_RenderText_Solid(font, "Continuer", color);
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
	if (SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_QueryTexture a echoue > %s", SDL_GetError());
		return (-1);
	}
	dstrect.x = WINDOW_WIDTH / 2 - TextW / 2;
	dstrect.y = WINDOW_HEIGHT / 3 + TextH;
	dstrect.w = TextW;
	dstrect.h = TextH;
	if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_RenderCopy a echoue > %s", SDL_GetError());
		return (-1);
	}

	// Bouton "Sauvegarder"
	surface = TTF_RenderText_Solid(font, "Sauvegarder", color);
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
	if (SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_QueryTexture a echoue > %s", SDL_GetError());
		return (-1);
	}
	dstrect.x = WINDOW_WIDTH / 2 - TextW / 2;
	dstrect.y = WINDOW_HEIGHT / 3 + TextH * 2;
	dstrect.w = TextW;
	dstrect.h = TextH;
	if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_RenderCopy a echoue > %s", SDL_GetError());
		return (-1);
	}

	// Bouton "Quitter"
	surface = TTF_RenderText_Solid(font, "Quitter", color);
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
	if (SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_QueryTexture a echoue > %s", SDL_GetError());
		return (-1);
	}
	dstrect.x = WINDOW_WIDTH / 2 - TextW / 2;
	dstrect.y = WINDOW_HEIGHT / 3 + TextH * 3;
	dstrect.w = TextW;
	dstrect.h = TextH;
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

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
					*game_launched = SDL_FALSE;
					*program_launched = SDL_FALSE;
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
					if (WINDOW_WIDTH / 2 - TextW / 2 <= event.motion.x && event.motion.x <= WINDOW_WIDTH / 2 + TextW / 2
						&& WINDOW_HEIGHT / 3 + TextH <= event.motion.y && event.motion.y <= WINDOW_HEIGHT / 3 + TextH * 2)
					{
						game_paused = SDL_FALSE;
					}
					// Bouton Sauvegarder
					else if (WINDOW_WIDTH / 2 - TextW / 2 <= event.motion.x && event.motion.x <= WINDOW_WIDTH / 2 + TextW / 2
						&& WINDOW_HEIGHT / 3 + TextH * 2 <= event.motion.y && event.motion.y <= WINDOW_HEIGHT / 3 + TextH * 2 + TextH)
					{
						printf("Bouton Sauvegarder\n");
					}
					// Bouton Quitter
					else if (WINDOW_WIDTH / 2 - TextW / 2 <= event.motion.x && event.motion.x <= WINDOW_WIDTH / 2 + TextW / 2
						&& WINDOW_HEIGHT / 3 + TextH * 3 <= event.motion.y && event.motion.y <= WINDOW_HEIGHT / 3 + TextH * 3 + TextH)
					{
						game_paused = SDL_FALSE;
						*game_launched = SDL_FALSE;
						*program_launched = SDL_FALSE;
					}

				default: break;
			}
		}
	}

	if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
	{
		SDL_Log("ERREUR : Impossible de changer la couleur pour le menu Pause > %s", SDL_GetError());
		return (-1);
	}
	return (0);
}