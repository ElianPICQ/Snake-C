#include "../header/header.h"



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
		exitWithError_2("Erreur : Creation rendu echoue", &window);

	// Initialisation de SDL_TTF
	if (TTF_Init() != 0)
		exitWithError_3("Erreur : Initialisation de SDL_TTF echouee", &window, &renderer);

	// Ouverture d'une police - Ici Arial (Utiliser la police Windows)
	TTF_Font *font = TTF_OpenFont("fonts/arial.ttf", 25);
	if (font == NULL)
		exitWithError_4("Erreur : Impossible de changer la police", &window, &renderer);

	/*---------------------------------- Execution du Programme  -------------------------------------------*/

	// Booleen du programme
	SDL_bool program_launched = SDL_TRUE;
	// Booleen Jeu lancé/Menu principal
	SDL_bool game_launched = SDL_FALSE;
	// Booleen Play/Pause
	SDL_bool pause = SDL_FALSE;
	// Booleen Game Over
	SDL_bool is_game_over;

	SDL_Event event;

	// Utilisé pour le damier (Donc inutile pour l'instant)
//	SDL_Rect rectangle;

//	rectangle.w = SQUARE_SIZE;
//	rectangle.h = SQUARE_SIZE;

	int direction = 0; // Immobile
	SDL_bool direction_changed = SDL_FALSE;	// Necessaire pour éviter que le serpent fasse demi tour instantanement (dans certains cas)
	int vitesse = SLOW;

	int i;

	srand(time(NULL));	// Initialisation de srand

	s_Tete *Tete;
	Tete = malloc(sizeof(Tete));

	s_Serpent *Serpent;
	Serpent = create_elem(((WINDOW_WIDTH / SQUARE_SIZE) / 2) * SQUARE_SIZE, ((WINDOW_HEIGHT / SQUARE_SIZE) / 2) * SQUARE_SIZE);
	Tete->premier = Serpent;

	if (Tete == NULL || Serpent == NULL)
		exitWithError_5("Erreur lors de la creation de Tete ou Serpent\n", &window, &renderer, &font);
	
	

	// Tableau de Pommes - La taille correspond au nombre de pommes à manger avant de grandir
	// et en afficher à nouveau
	s_Pomme Pomme[NB_POMMES];

	int pommesAManger;


	/*-------------------------------------------------------------------------------------------------*/
	/*---------------------------------- BOUCLE PRINCIPALE  -------------------------------------------*/
	/*-------------------------------------------------------------------------------------------------*/
	while (program_launched)
	{
		// MENU PRINCIPAL
		SDL_RenderClear(renderer);
		menu_principal(&renderer, &font, &program_launched, &game_launched);

		// On met les variables à leur état initial avant de (re)lancer la partie
		is_game_over = SDL_FALSE;
		direction = 0;
		vitesse = SLOW;

		// Initialisation du Serpent (Nécesseite la Tete & la première struct du Serpent)
		for (i = 1; i < INITIAL_SNAKE_SIZE; i++)
			list_push_back(&Tete);

		pommesAManger = 0;
		initialise_pommes(Pomme);

		// BOUCLE DE JEU PRINCIPALE
		while (game_launched)
		{
			SDL_RenderClear(renderer);

			// Construction d'un damier
			// Possibilité de le rendre optionnel depuis les options du Jeu ?
	//		creer_damier(&window, &renderer, rectangle);

			// Replacer les pommes si elles ont toutes été mangées
			if (pommesAManger == 0)
			{
				placer_pommes(&Tete, &renderer, &window, Pomme);
				pommesAManger = NB_POMMES;
			}
			// Dessiner les pommes dans Renderer
			dessiner_pommes(&Tete, &renderer, &window, Pomme, &font);

			// Dessiner le Serpent dans Renderer
			dessiner_serpent(&Tete, &renderer, &window, &font);

			//On remet la couleur noir pour le fond
			// Inutile avec le damier (Mode sans fond et avec dans les options du Jeu ?)
			if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
			{
				delete_snake(&Tete);
				exitWithError_5("Impossible de changer la couleur pour le rendu", &window, &renderer, &font);
			}

			SDL_RenderPresent(renderer);

			// Attente avant le prochain rendu - Ici on peut queue des events
			SDL_Delay(vitesse);

			direction_changed = SDL_FALSE;
			
			/******************* GESTION DES EVENEMENTS *******************/
			// Dans un while pour vider la queue d'events
			while (SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					// Croix de fermeture
					case SDL_QUIT:
						game_launched = SDL_FALSE;
						program_launched = SDL_FALSE;
						break;

					// Event clavier
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{
							// Quitter le programme -> Changer "Menu Pause"
							case SDLK_ESCAPE:
								pause = SDL_TRUE;
								break;

							// Changer de vitesse
							case SDLK_LSHIFT:
								vitesse = (vitesse == SLOW) ? FAST : SLOW;
								break;

							// Snake direction ZQSD / Arrows
							case SDLK_z:
							case SDLK_UP:
								if (direction == DOWN || direction_changed)
									break;
								direction_changed = SDL_TRUE;
								direction = UP;
								break;

							case SDLK_s:
							case SDLK_DOWN:
								if (direction == UP || direction_changed)
									break;
								direction_changed = SDL_TRUE;
								direction = DOWN;
								break;

							case SDLK_q:
							case SDLK_LEFT:
								if (direction == RIGHT || direction_changed)
									break;
								direction_changed = SDL_TRUE;
								direction = LEFT;
								break;

							case SDLK_d:
							case SDLK_RIGHT:
								if (direction == LEFT || direction_changed)
									break;
								direction_changed = SDL_TRUE;
								direction = RIGHT;
								break;

							default: break;
						}
						break;

					default: break;
				}
			}
			/******************* FIN GESTION DES EVENEMENTS *******************/

			// BOUCLE DE PAUSE
			while (pause)
			{
				while (SDL_PollEvent(&event))
				{
					switch(event.type)
					{
						// Croix de fermeture
						case SDL_QUIT:
							pause = SDL_FALSE;
							game_launched = SDL_FALSE;
							program_launched = SDL_FALSE;
							break;

						// Event clavier
						case SDL_KEYDOWN:
							switch(event.key.keysym.sym)
							{
								// Quitter le programme -> Changer "Menu Pause"
								case SDLK_ESCAPE:
									pause = SDL_FALSE;
									break;

								default: break;
							}
							break;

						default: break;
					}
				}
			}
			// Deplacer Snake
			move_snake(&Tete, direction, &game_launched, Pomme, &pommesAManger, &is_game_over);

			if (is_game_over)
			{
				reset_snake(&Tete, ((WINDOW_WIDTH / SQUARE_SIZE) / 2) * SQUARE_SIZE,((WINDOW_HEIGHT / SQUARE_SIZE) / 2) * SQUARE_SIZE);
				game_over(&window, &renderer, &font, &game_launched, &program_launched);
			}
		}
	}
	
	/*------------------------------------------------------------------------------------------------------*/

	
	// On libère la mémoire allouée pour le Serpent et les Pommes
	delete_snake(&Tete);
	// Fermeture de la SDL + Libérer la mémoire qu'elle à allouée
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}