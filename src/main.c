/*
*	Rappel de compilation
*	> Windows :
gcc src/main.c src/snake.c src/menu_principal.c src/modifier_snake.c src/pommes.c src/menu_pause.c src/game_over.c src/score.c src/gestion_erreur.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
*	> GNU/Linux, MacOS : gcc src/main.c src/snake.c src/gestion_erreur.c &(sdl2-config --cflags --libs) -o prog
*/

#include "../header/header.h"


int main(int argc, char **argv)
{
	snake_game();

	return (0);
}

// TRUCS A REGLER

/* APPARITION DES POMMES BUGGE == + OU - DONE (essayer de reproduire les bugs)
 *
 *		-> La derniere pomme a parfois un HEIGHT cassé (et apparait avec 1 de largeur et bcp de hauteur)
 *			-> Il faut la manger par dessous pour que ca marche
 *			-> DONE
 *
 *		-> Toutes les pommes n'apparaissent pas apres avoir été mangées
 *			(i.e. 2 pommes apparaissent au lieu de 3)
 *
 *		-> Pommes qui disparait après en avoir mangé une autre ????
 *
 *
 */

// TRUCS A FAIRE

/*	BANDEAU SUPERIEUR POUR AFFICHER LES INFOS
 *		-> Bandeau de 50px? de hauteur sur toute la largeur dans lequel mettre le score & autres infos
 *
 *	GERER LES ERREURS
 *		-> Fichier menu_principal.c
 *		-> Fichier game_over.c
 *
 *
 *
 *	POLICE
 *		-> Faire plusieurs tailles de police
 *			-> Ouvrir plusieurs polices avec (TTF_OpenFont) et donner des tailles différentes
 *
 *
 *	SCORE
 *		-> Afficher le nombre de pommes mangées	DONE
 *		-> Afficher la taille
 *
 *
 *	SAUVEGARDE
 *		-> 1 emplacement de sauvegarde
 *		-> Puis plusieurs
 *
 *
 *	SON
 *		-> Musique de fond
 *		-> Son lorsqu'on mange une pomme
 *
 *
 *	PARAMETRES
 *		-> Voir ci dessous
 *
 *		PLATEAU
 *			-> Choix du plateau (sans, damier, colonnes?, lignes?)
 *			-> Choix des couleurs (Snake, Pommes, Fonds)
 *				-> A faire si pas d'images
 *
 *		IMAGES
 *			-> Tete du serpent, Corps du serpent, Pommes
 *
 *		SON
 *			-> Activer/Desactiver
 *			-> Volume si possible
 *
 */


// TRUCS FAITS

/*	GAME OVER - DONE
 *		-> Bouton Rejouer au lieu de Jouer
 *			-> Donc Reset le Serpent et les Pommes
 *
 *
 */