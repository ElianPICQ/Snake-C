#include "../header/header.h"


// Rendu du menu principal
int		menu_principal(SDL_Renderer	*renderer, TTF_Font *font, SDL_bool *program_launched, SDL_bool *game_launched)
{
	SDL_bool menu_principal = SDL_TRUE;
	int playBtnW, playBtnH, quitBtnW, quitBtnH;
	SDL_Event event;

	// Bouton Jouer
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface *surface = TTF_RenderText_Solid(font, "JOUER AU SNAKE", color);
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
	if (SDL_QueryTexture(texture, NULL, NULL, &playBtnW, &playBtnH) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_QueryTexture a echoue > %s", SDL_GetError());
		return (-1);
	}
	SDL_Rect dstrect = { WINDOW_WIDTH / 2 - playBtnW / 2, WINDOW_HEIGHT / 2 - playBtnH / 2, playBtnW, playBtnH };
	if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_RenderCopy a echoue > %s", SDL_GetError());
		return (-1);
	}

	// Bouton Quitter
	surface = TTF_RenderText_Solid(font, "QUITTER", color);
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
	if (SDL_QueryTexture(texture, NULL, NULL, &quitBtnW, &quitBtnH) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_QueryTexture a echoue > %s", SDL_GetError());
		return (-1);
	}
	dstrect.x = WINDOW_WIDTH / 2 - quitBtnW / 2;
	dstrect.y = WINDOW_HEIGHT / 2 + playBtnH * 2;
	dstrect.w = quitBtnW;
	dstrect.h = quitBtnH;
	if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_RenderCopy a echoue > %s", SDL_GetError());
		return (-1);
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
					*program_launched = SDL_FALSE;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							menu_principal = SDL_FALSE;
							*program_launched = SDL_FALSE;
							break;

						case SDLK_RETURN:
							menu_principal = SDL_FALSE;
							*game_launched = SDL_TRUE;
							break;

						default: break;
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					// Bouton Jouer
					if (WINDOW_WIDTH / 2 - playBtnW / 2 <= event.motion.x && event.motion.x <= WINDOW_WIDTH / 2 + playBtnW / 2
						&& WINDOW_HEIGHT / 2 - playBtnH / 2 <= event.motion.y && event.motion.y <= WINDOW_HEIGHT / 2 + playBtnH / 2)
					{
						menu_principal = SDL_FALSE;
						*game_launched = SDL_TRUE;
					}
					// Bouton Quitter
					else if (WINDOW_WIDTH / 2 - quitBtnW / 2 <= event.motion.x && event.motion.x <= WINDOW_WIDTH / 2 + quitBtnW / 2
						&& WINDOW_HEIGHT / 2 + playBtnH * 2 <= event.motion.y && event.motion.y <= WINDOW_HEIGHT / 2 + playBtnH * 2 + quitBtnH)
					{
						menu_principal = SDL_FALSE;
						*program_launched = SDL_FALSE;
					}
					break;

				default: break;
			}		
		}
	}

	// Tout s'est bien passé -> 0
	return (0);
}