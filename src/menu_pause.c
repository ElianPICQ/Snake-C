#include "../header/header.h"


void	pause(SDL_Window	**window, SDL_Renderer	**renderer, TTF_Font **font, SDL_bool *game_launched, SDL_bool *program_launched)
{
	SDL_bool game_paused = SDL_TRUE;
	// Couleur du crayon
	SDL_Color color = { 255, 255, 255 };
	// Taille des boites de texte
	int TextW, TextH;
	SDL_Event event;

	// On met tout dans un rectangle noir qui ne prend pas tout l'écran

	// Texte "Pause"
	SDL_Surface *surface = TTF_RenderText_Solid(*font, "PAUSE", color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(*renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH);
	SDL_Rect dstrect = { WINDOW_WIDTH / 2 - TextW / 2, WINDOW_HEIGHT / 3 - TextH / 2, TextW, TextH };
	SDL_RenderCopy(*renderer, texture, NULL, &dstrect);

	// Bouton "Continuer"
	surface = TTF_RenderText_Solid(*font, "Continuer", color);
	texture = SDL_CreateTextureFromSurface(*renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH);
	dstrect.x = WINDOW_WIDTH / 2 - TextW / 2;
	dstrect.y = WINDOW_HEIGHT / 3 + TextH;
	dstrect.w = TextW;
	dstrect.h = TextH;
	SDL_RenderCopy(*renderer, texture, NULL, &dstrect);

	// Bouton "Quitter"
	surface = TTF_RenderText_Solid(*font, "Quitter", color);
	texture = SDL_CreateTextureFromSurface(*renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH);
	dstrect.x = WINDOW_WIDTH / 2 - TextW / 2;
	dstrect.y = WINDOW_HEIGHT / 3 + TextH * 2;
	dstrect.w = TextW;
	dstrect.h = TextH;
	SDL_RenderCopy(*renderer, texture, NULL, &dstrect);

	SDL_RenderPresent(*renderer);

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

				default: break;
			}
		}
	}
}