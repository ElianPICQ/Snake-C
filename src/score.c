#include "../header/header.h"


int		dessiner_score(SDL_Renderer	*renderer, SDL_Window *window, int pommesMangees, TTF_Font *font)
{
	// Couleur du crayon
	SDL_Color color = { 255, 255, 255 };
	// Taille des boites de texte
	int TextW, TextH;
	char asciiScore[5];
	char ScoreText[12] = {'s', 'c', 'o', 'r', 'e', ':', ' ', 0, 0, 0, 0, 0};
	strncat(ScoreText, itoa(pommesMangees, asciiScore, 10), 4);

	SDL_Surface *surface = TTF_RenderText_Solid(font, ScoreText, color);
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
	SDL_Rect dstrect = { 5, 3, TextW, TextH };
	if (SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0)
	{
		SDL_Log("ERREUR : La fonction SDL_RenderCopy a echoue > %s", SDL_GetError());
		return (-1);
	}
}