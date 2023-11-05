#include "../header/header.h"


int		game_over(SDL_Window	*window, SDL_Renderer	*renderer, TTF_Font *font, s_Game *Game)
{
	int i = 0;
	SDL_bool is_game_over = SDL_TRUE;
	SDL_Event event;
	SDL_Rect dstrect;


	char asciiScore[5];
	char ScoreText[12] = {'S', 'C', 'O', 'R', 'E', ':', ' ', 0, 0, 0, 0, 0};
	strncat(ScoreText, itoa(Game->pommesMangees, asciiScore, 10), 4);

	char	*boutonTexte[] = {"GAME OVER", ScoreText, "Retourner au Menu Principal", "Quitter", 0};
	int nbBtn = 0;

	while (boutonTexte[nbBtn] != 0)
		nbBtn++;

	int ecartBtn = 20;
	s_MenuBouton MenuBouton[nbBtn];
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface *surface;
	SDL_Texture *texture;

	SDL_RenderClear(renderer);

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

	while (is_game_over)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					is_game_over = SDL_FALSE;
					Game->game_launched = SDL_FALSE;
					Game->program_launched = SDL_FALSE;
					break;

				case SDL_MOUSEBUTTONDOWN:
					// Bouton "Menu Principal"
					if (MenuBouton[2].bouton.x <= event.motion.x && event.motion.x <= MenuBouton[2].bouton.x + MenuBouton[2].bouton.w
						&& MenuBouton[2].bouton.y <= event.motion.y && event.motion.y <= MenuBouton[2].bouton.y + MenuBouton[2].bouton.h)
					{
						printf("Menu Principal\n");
						is_game_over = SDL_FALSE;
						Game->game_launched = SDL_FALSE;
					}
					// Bouton "Quitter"
					else if (MenuBouton[3].bouton.x <= event.motion.x && event.motion.x <= MenuBouton[3].bouton.x + MenuBouton[3].bouton.w
						&& MenuBouton[3].bouton.y <= event.motion.y && event.motion.y <= MenuBouton[3].bouton.y + MenuBouton[3].bouton.h)
					{
						printf("Quitter\n");
						is_game_over = SDL_FALSE;
						Game->game_launched = SDL_FALSE;
						Game->program_launched = SDL_FALSE;
					}
					break;

				default: break;
			}
		}
	}
}