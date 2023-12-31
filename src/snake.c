#include "../header/header.h"


void	initialise_jeu(s_Game *Game)
{
	Game->program_launched = SDL_TRUE;
	Game->game_launched = SDL_FALSE;
	Game->game_paused = SDL_FALSE;
	Game->is_game_over = SDL_FALSE;
	Game->load_from_save = SDL_FALSE;
	Game->direction = 0;
	Game->direction_changed = SDL_FALSE;
	Game->vitesse = SLOW;
	Game->pommesMangees = 0;
	Game->pommesAManger = 0;
}

void	snake_game()
{
	SDL_Window	*window = NULL;
	SDL_Renderer	*renderer = NULL;

	// Initialisation SDL | Module vidéo
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exitWithError_0("Erreur : Initialisation SDL echouee");

	// Création de la fenêtre
	window = SDL_CreateWindow("Jeu du Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (window == NULL)
		exitWithError_1("Erreur : Creation fenetre echouee");

	// Création du rendu
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
		exitWithError_2("Erreur : Creation rendu echoue", window);

	// Enable Blend mode (pour pouvoir changer l'alpha)
	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0)
		exitWithError_3("Erreur : SDL_SetRenderDrawBlendMode a echoue", window, renderer);

	// Initialisation de SDL_TTF
	if (TTF_Init() != 0)
		exitWithError_3("Erreur : Initialisation de SDL_TTF echouee", window, renderer);

	// Ouverture d'une police - Ici Arial (Utiliser la police Windows)
	TTF_Font *font = TTF_OpenFont("fonts/arial.ttf", 25);
	if (font == NULL)
		exitWithError_4("Erreur : Impossible de changer la police", window, renderer);

	/*---------------------------------- Execution du Programme  -------------------------------------------*/

	SDL_Event event;

	s_Game Game;

	initialise_jeu(&Game);
/*
	// Booleen du programme
	SDL_bool program_launched = SDL_TRUE;
	// Booleen Jeu lancé/Menu principal
	SDL_bool game_launched = SDL_FALSE;
	// Booleen Play/Pause
	SDL_bool game_paused = SDL_FALSE;
	// Booleen Game Over
	SDL_bool is_game_over = SDL_FALSE;
	// Booleen pour savoir si il faut charger la partie depuis la sauvegarde
	SDL_bool load_from_save = SDL_FALSE;

	// Utilisé pour le damier (Donc inutile pour l'instant)
//	SDL_Rect rectangle;

//	rectangle.w = SQUARE_SIZE;
//	rectangle.h = SQUARE_SIZE;

	int direction = 0; // Immobile
	SDL_bool direction_changed = SDL_FALSE;	// Necessaire pour éviter que le serpent fasse demi tour instantanement (dans certains cas)
	int vitesse = SLOW;
//	int score = 0;
	int pommesMangees = 0;
*/
	// Si besoin d'un itérateur
	int i;

	srand(time(NULL));	// Initialisation de srand

	s_Tete *Tete;
	Tete = (s_Tete*)malloc(sizeof(Tete));

	s_Serpent *Serpent;
	Serpent = create_elem(((WINDOW_WIDTH / SQUARE_SIZE) / 2) * SQUARE_SIZE, ((WINDOW_HEIGHT / SQUARE_SIZE) / 2) * SQUARE_SIZE);
	Tete->premier = Serpent;

	if (Tete == NULL || Serpent == NULL)
		exitWithError_5("Erreur lors de la creation de Tete ou Serpent\n", window, renderer, font);
	
	

	// Tableau de Pommes - La taille correspond au nombre de pommes à manger avant de grandir
	// et en afficher à nouveau
	s_Pomme Pomme[NB_POMMES];

	// Nombre de pommes restant avant d'en affichier de nouvelles
//	int pommesAManger = 0;


	/*-------------------------------------------------------------------------------------------------*/
	/*---------------------------------- BOUCLE PRINCIPALE  -------------------------------------------*/
	/*-------------------------------------------------------------------------------------------------*/
	while (Game.program_launched)
	{
		SDL_RenderClear(renderer);
		// MENU PRINCIPAL
		if (menu_principal(renderer, font, &Game) != 0)
		{
			// Free memory
			exitWithError_noMsg(window, renderer, font, &Tete);
		}

		// Charger la sauvegarde ou initialiser une nouvelle partie
		if (Game.load_from_save)
		{

		}
		else
		{
			// Initialisation du Serpent (Nécesseite la Tete & la première struct du Serpent)
			for (i = 1; i < INITIAL_SNAKE_SIZE; i++)
				list_push_back(&Tete);

			Game.pommesAManger = 0;
			Game.pommesMangees = 0;
			initialise_pommes(Pomme);		
		}

		// On met les variables à leur état initial avant de (re)lancer la partie
		Game.is_game_over = SDL_FALSE;
		Game.game_paused = SDL_FALSE;

		Game.direction = 0;
		Game.vitesse = SLOW;

		// BOUCLE DE JEU PRINCIPALE
		while (Game.game_launched)
		{
			Game.game_paused = SDL_FALSE;
			SDL_RenderClear(renderer);

			// Construction d'un damier
			// Possibilité de le rendre optionnel depuis les options du Jeu ?
	//		creer_damier(&window, &renderer, rectangle);

			// Replacer les pommes si elles ont toutes été mangées
			if (Game.pommesAManger == 0)
			{
				placer_pommes(&Tete, Pomme);
				Game.pommesAManger = NB_POMMES;
			}

			// Dessiner les pommes dans Renderer
			if (dessiner_pommes(&Tete, renderer, window, Pomme, font) != 0)
			{
				// Free memory
				exitWithError_noMsg(window, renderer, font, &Tete);
			}

			// Dessiner le Serpent dans Renderer
			if (dessiner_serpent(&Tete, renderer, window, font) != 0)
			{
				// Free memory
				exitWithError_noMsg(window, renderer, font, &Tete);
			}

			// Dessiner le score en dernier pour qu'il apparaisse au dessus de tout
			if (dessiner_score(renderer, window, Game.pommesMangees, font) != 0)
			{
				// Free memory
				exitWithError_noMsg(window, renderer, font, &Tete);
			}

			//On remet la couleur noir pour le fond
			// Inutile avec le damier (Mode sans fond et avec dans les options du Jeu ?)
			if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
			{
				delete_snake(&Tete);
				exitWithError_5("Impossible de changer la couleur pour le rendu", window, renderer, font);
			}

			SDL_RenderPresent(renderer);

			// Attente avant le prochain rendu - Ici on peut queue des events
			SDL_Delay(Game.vitesse);

			Game.direction_changed = SDL_FALSE;
			
			/******************* GESTION DES EVENEMENTS *******************/
			// Dans un while pour vider la queue d'events
			while (SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					// Croix de fermeture
					case SDL_QUIT:
						Game.game_launched = SDL_FALSE;
						Game.program_launched = SDL_FALSE;
						break;

					// Event clavier
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{
							// Menu Pause
							case SDLK_ESCAPE:
								Game.game_paused = SDL_TRUE;
								break;

							// Changer de vitesse
							case SDLK_LSHIFT:
								Game.vitesse = (Game.vitesse == SLOW) ? FAST : SLOW;
								break;

							// Snake direction ZQSD / Arrows
							case SDLK_z:
							case SDLK_UP:
								if (Game.direction == DOWN || Game.direction_changed)
									break;
								Game.direction_changed = SDL_TRUE;
								Game.direction = UP;
								break;

							case SDLK_s:
							case SDLK_DOWN:
								if (Game.direction == UP || Game.direction_changed)
									break;
								Game.direction_changed = SDL_TRUE;
								Game.direction = DOWN;
								break;

							case SDLK_q:
							case SDLK_LEFT:
								if (Game.direction == RIGHT || Game.direction_changed)
									break;
								Game.direction_changed = SDL_TRUE;
								Game.direction = LEFT;
								break;

							case SDLK_d:
							case SDLK_RIGHT:
								if (Game.direction == LEFT || Game.direction_changed)
									break;
								Game.direction_changed = SDL_TRUE;
								Game.direction = RIGHT;
								break;

							default: break;
						}
						break;

					default: break;
				}
			}
			/******************* FIN GESTION DES EVENEMENTS *******************/

			// BOUCLE DE PAUSE
			if (Game.game_paused)
			{
				if (pause(window, renderer, font, &Game) != 0)
				{
					// Free memory
					exitWithError_noMsg(window, renderer, font, &Tete);
				}
			}

			// Deplacer Snake
			move_snake(&Tete, Pomme, &Game);

			if (Game.is_game_over)
			{
				reset_snake(&Tete, ((WINDOW_WIDTH / SQUARE_SIZE) / 2) * SQUARE_SIZE,((WINDOW_HEIGHT / SQUARE_SIZE) / 2) * SQUARE_SIZE);
				
				if (game_over(window, renderer, font, &Game) != 0)
				{
					// Free memory
					exitWithError_noMsg(window, renderer, font, &Tete);
				}
			}
		}
	}
	
	/*------------------------------------------------------------------------------------------------------*/

	
	// On libère la mémoire allouée par malloc()
	delete_snake(&Tete);
	// Fermeture de la SDL + Libérer la mémoire qu'elle à allouée
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}