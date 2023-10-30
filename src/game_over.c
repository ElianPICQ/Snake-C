#include "../header/header.h"


int		game_over(SDL_Window	*window, SDL_Renderer	*renderer, TTF_Font *font, SDL_bool *game_launched, SDL_bool *program_launched)
{
	SDL_bool is_game_over = SDL_TRUE;
	// Couleur du crayon
	SDL_Color color = { 255, 255, 255 };
	// Taille des boites de texte
	int TextW, TextH;
	SDL_Event event;

	// On reset l'affichage (ici écran noir)
	if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
	{
		SDL_Log("ERREUR : Impossible de changer la couleur > %s", SDL_GetError());
		return (-1);
	}

	if (SDL_RenderClear(renderer) != 0)
	{
		SDL_Log("ERREUR : Impossible de changer la couleur > %s", SDL_GetError());
		return (-1);
	}

	// Texte "Game Over"
	SDL_Surface *surface = TTF_RenderText_Solid(font, "GAME OVER", color);
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
	SDL_Rect dstrect = { WINDOW_WIDTH / 2 - TextW / 2, WINDOW_HEIGHT / 3 - TextH / 2, TextW, TextH };
	
	if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_RenderCopy a echoue > %s", SDL_GetError());
		return (-1);
	}

	// Bouton "Menu Principal"
	surface = TTF_RenderText_Solid(font, "Menu Principal", color);
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
	dstrect.x = WINDOW_WIDTH / 4 - TextW / 2;
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
	dstrect.x = (WINDOW_WIDTH - WINDOW_WIDTH / 4) - TextW / 2;
	dstrect.y = WINDOW_HEIGHT / 3 + TextH * 2;
	dstrect.w = TextW;
	dstrect.h = TextH;
	if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_RenderCopy a echoue > %s", SDL_GetError());
		return (-1);
	}	

	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

	while (is_game_over)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					// Bouton "Menu Principal"
					if (WINDOW_WIDTH / 4 - TextW / 2 <= event.motion.x && event.motion.x <= WINDOW_WIDTH / 4 + TextW / 2
						&& WINDOW_HEIGHT / 3 + TextH * 2 <= event.motion.y && event.motion.y <= WINDOW_HEIGHT / 3 + TextH * 2 + TextH)
					{
						is_game_over = SDL_FALSE;
						*game_launched = SDL_FALSE;
					}
					// Bouton "Quitter"
					else if ((WINDOW_WIDTH - WINDOW_WIDTH / 4) - TextW / 2 <= event.motion.x && event.motion.x <= (WINDOW_WIDTH - WINDOW_WIDTH / 4) + TextW / 2
						&& WINDOW_HEIGHT / 3 + TextH * 2 <= event.motion.y && event.motion.y <= WINDOW_HEIGHT / 3 + TextH * 2 + TextH)
					{
						is_game_over = SDL_FALSE;
						*game_launched = SDL_FALSE;
						*program_launched = SDL_FALSE;
					}
					break;

				case SDL_QUIT:
					is_game_over = SDL_FALSE;
					*game_launched = SDL_FALSE;
					*program_launched = SDL_FALSE;
					break;

				default: break;
			}
		}
	}
}