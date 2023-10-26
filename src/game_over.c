#include "../header/header.h"


void	 game_over(SDL_Window	**window, SDL_Renderer	**renderer, TTF_Font **font, SDL_bool *game_launched, SDL_bool *program_launched)
{
	SDL_bool is_game_over = SDL_TRUE;
	// Couleur du crayon
	SDL_Color color = { 255, 255, 255 };
	// Taille des boites de texte
	int TextW, TextH;
	SDL_Event event;

	// On reset l'affichage (ici écran noir)
	if (SDL_SetRenderDrawColor(*renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
	{
//		delete_snake(&Tete);
		exitWithError_5("Impossible de changer la couleur pour le rendu", window, renderer, font);
	}
	SDL_RenderClear(*renderer);

	// Texte "Game Over"
	SDL_Surface *surface = TTF_RenderText_Solid(*font, "GAME OVER", color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(*renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH);
	SDL_Rect dstrect = { WINDOW_WIDTH / 2 - TextW / 2, WINDOW_HEIGHT / 3 - TextH / 2, TextW, TextH };
	SDL_RenderCopy(*renderer, texture, NULL, &dstrect);

	// Bouton "Menu Principal"
	surface = TTF_RenderText_Solid(*font, "Menu Principal", color);
	texture = SDL_CreateTextureFromSurface(*renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH);
	dstrect.x = WINDOW_WIDTH / 4 - TextW / 2;
	dstrect.y = WINDOW_HEIGHT / 3 + TextH * 2;
	dstrect.w = TextW;
	dstrect.h = TextH;
	SDL_RenderCopy(*renderer, texture, NULL, &dstrect);

	// Bouton "Quitter"
	surface = TTF_RenderText_Solid(*font, "Quitter", color);
	texture = SDL_CreateTextureFromSurface(*renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH);
	dstrect.x = (WINDOW_WIDTH - WINDOW_WIDTH / 4) - TextW / 2;
	dstrect.y = WINDOW_HEIGHT / 3 + TextH * 2;
	dstrect.w = TextW;
	dstrect.h = TextH;
	SDL_RenderCopy(*renderer, texture, NULL, &dstrect);

	SDL_RenderPresent(*renderer);

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