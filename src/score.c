#include "../header/header.h"


void	dessiner_score(SDL_Renderer	*renderer, SDL_Window *window, int pommesMangees, TTF_Font *font)
{
	// Couleur du crayon
	SDL_Color color = { 255, 255, 255 };
	// Taille des boites de texte
	int TextW, TextH;
	char asciiScore[5];
	char ScoreText[12] = {'s', 'c', 'o', 'r', 'e', ':', ' ', 0, 0, 0, 0, 0};
	strncat(ScoreText, itoa(pommesMangees, asciiScore, 10), 4);

	SDL_Surface *surface = TTF_RenderText_Solid(font, ScoreText, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &TextW, &TextH);
	SDL_Rect dstrect = { 5, 3, TextW, TextH };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}