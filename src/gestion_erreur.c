#include "../header/header.h"


// Utiliser lorsque rien n'a été initialiser
void	exitWithError_0(const char *message)
{
	SDL_Log("ERREUR : %s > %s", message, SDL_GetError());
	exit(EXIT_FAILURE);
}

/* Utiliser si à été initialisé:
 *	- La SDL
*/
void	exitWithError_1(const char *message)
{
	SDL_Log("ERREUR : %s > %s", message, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

/* Utiliser si à été initialisé:
 *	- La fenêtre (SDL_Window *window)
 *	- La SDL
*/
void	exitWithError_2(const char *message, SDL_Window *window)
{
	SDL_Log("ERREUR : %s > %s", message, SDL_GetError());
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(EXIT_FAILURE);
}

/* Utiliser si à été initialisé:
 *	- Le rendu (SDL_Renderer *renderer)
 *	- La fenêtre (SDL_Window *window)
 *	- La SDL
*/
void	exitWithError_3(const char *message, SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_Log("ERREUR : %s > %s", message, SDL_GetError());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(EXIT_FAILURE);
}

/* Utiliser si à été initialisé:
 *	- Le module TTF
 *	- Le rendu (SDL_Renderer *renderer)
 *	- La fenêtre (SDL_Window *window)
 *	- La SDL
*/
void	exitWithError_4(const char *message, SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_Log("ERREUR : %s > %s", message, SDL_GetError());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_FAILURE);
}

/* Utiliser si à été initialisé:
 *	- La Police (TTF_Font *font)
 *	- Le module TTF
 *	- Le rendu (SDL_Renderer *renderer)
 *	- La fenêtre (SDL_Window *window)
 *	- La SDL
*/
void	exitWithError_5(const char *message, SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font)
{
	SDL_Log("ERREUR : %s > %s", message, SDL_GetError());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_FAILURE);
}
/*
void	exitWithError(const char *message, SDL_Window **window, SDL_Renderer **renderer)
{
	SDL_Log("ERREUR : %s > %s", message, SDL_GetError());
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_FAILURE);
}
*/