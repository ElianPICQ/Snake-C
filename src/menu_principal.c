#include "../header/header.h"


// Rendu du menu principal
void	menu_principal(SDL_Renderer	**renderer, TTF_Font **font, SDL_bool *program_launched, SDL_bool *game_launched)
{
	SDL_bool menu_principal = SDL_TRUE;
	int playBtnW, playBtnH, quitBtnW, quitBtnH;
	SDL_Event event;

	// Bouton Jouer
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface *surface = TTF_RenderText_Solid(*font, "JOUER AU SNAKE", color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(*renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &playBtnW, &playBtnH);
	SDL_Rect dstrect = { WINDOW_WIDTH / 2 - playBtnW / 2, WINDOW_HEIGHT / 2 - playBtnH / 2, playBtnW, playBtnH };
	SDL_RenderCopy(*renderer, texture, NULL, &dstrect);

	// Bouton Quitter
	surface = TTF_RenderText_Solid(*font, "QUITTER", color);
	texture = SDL_CreateTextureFromSurface(*renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &quitBtnW, &quitBtnH);
	dstrect.x = WINDOW_WIDTH / 2 - quitBtnW / 2;
	dstrect.y = WINDOW_HEIGHT / 2 + playBtnH * 2;
	dstrect.w = quitBtnW;
	dstrect.h = quitBtnH;
	SDL_RenderCopy(*renderer, texture, NULL, &dstrect);

	SDL_RenderPresent(*renderer);

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
}