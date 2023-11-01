#ifndef HEADER_H
	#define HEADER_H

#include <stdio.h>
#include <stdlib.h>		// exit(), itoa()
#include <time.h>		// srand(), rand()
#include <string.h>		// strncat()
#include <SDL.h>
#include <SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SQUARE_SIZE 40
#define INITIAL_SNAKE_SIZE 6

#define NB_POMMES 3

#define UP		1
#define RIGHT	2
#define DOWN	3
#define LEFT	4

// Defini le delay entre chaque frame
#define SLOW	500
#define FAST	200

// Structures pour le Serpent
typedef struct Serpent s_Serpent;
struct Serpent
{
	SDL_Rect morceauCorps;

	s_Serpent	*suivant;
};

typedef struct Tete s_Tete;
struct Tete
{
	s_Serpent	*premier;
};


// Structures pour les Pommes
typedef struct Pomme s_Pomme;
struct Pomme
{
	SDL_Rect infoPomme;
};

// Stock les taille des boutons de menu
typedef struct MenuBouton s_MenuBouton;
struct MenuBouton {
	SDL_Rect bouton;
};

// Prototypes des fonctions
// Fichier snake.c
void	snake_game();

// Fichier creer_damier.c
//void	creer_damier(SDL_Window **window, SDL_Renderer	**renderer, SDL_Rect rectangle);

// Fichier menu_principal.c
int		menu_principal(SDL_Renderer	*renderer, TTF_Font *font, SDL_bool *program_launched, SDL_bool *game_launched);

// Fichier pomme.c
void	initialise_pommes(s_Pomme *Pomme);
void	placer_pommes(s_Tete **Tete, s_Pomme *Pomme);
int		checkPositionPomme(s_Pomme *Pomme, int i, s_Tete **Tete);
void	dessiner_pommes(s_Tete **Tete, SDL_Renderer *renderer, SDL_Window *window, s_Pomme *Pomme, TTF_Font *font);

// Fichier modifier_snake.c
void	move_snake(s_Tete **Tete, int direction, SDL_bool *game_launched, s_Pomme *Pomme, int *pommesAManger, SDL_bool *is_game_over, int *pommesMangees);
void	dessiner_serpent(s_Tete **Tete, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font);

s_Serpent	*create_elem(int x, int y);
void	list_push_front(s_Tete	**s_Tete, int x, int y);
void	list_push_back(s_Tete **Tete);
void	delete_snake(s_Tete	**Tete);
void	reset_snake(s_Tete	**Tete, int x, int y);

void	ft_switch(int *a, int *b);

// Fichier game_over.c
int		game_over(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, SDL_bool *game_launched, SDL_bool *program_launched);

// Fichier pause.c
int		pause(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, SDL_bool *game_launched, SDL_bool *program_launched);

// Fichier score.c
int		dessiner_score(SDL_Renderer	*renderer, SDL_Window *window, int pommesMangees, TTF_Font *font);

// Fichier gestion_erreur.c
void	exitWithError_0(const char *message);
void	exitWithError_1(const char *message);
void	exitWithError_2(const char *message, SDL_Window *window);
void	exitWithError_3(const char *message, SDL_Window *window, SDL_Renderer *renderer);
void	exitWithError_4(const char *message, SDL_Window *window, SDL_Renderer *renderer);
void	exitWithError_5(const char *message, SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);
void	exitWithError_noMsg(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);


#endif // HEADER_H