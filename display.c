#include <stdlib.h>		   // Pour pouvoir utiliser exit()
#include <stdio.h>		   // Pour pouvoir utiliser printf()
#include <math.h>		   // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "Fonction.h"
#include <time.h>
#include <unistd.h>

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */

void gestionEvenement(EvenementGfx evenement)
{

	static int difficulty = 0, nbFlag = 0, tailleImage = 32;
	static int tab_difficulty[3] = {18, 45, 100};
	static int *ptFlag = &nbFlag;
	static bool aPerdu = false, premierClique = false, initialisationFaite = false, difficulteChoisis = false, aGagne = false;
	static int tempsInitial = 0;
	static char chaineTemps[50], chaineDrapeau[50];

	static cell plateau[LONGUEUR][LARGEUR];
	if (!initialisationFaite && difficulteChoisis)
	{
		tempsInitial = time(NULL);
		nbFlag = tab_difficulty[difficulty];
		initTab(plateau, difficulty);
		initImage(plateau, difficulty, tailleImage);
		// afficheTab(plateau, difficulty);
		initialisationFaite = true;
		actualiseChaineDrapeau(chaineDrapeau, nbFlag);
	}

	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	switch (evenement)
	{
	case Initialisation:

		// Configure le systeme pour generer un message Temporisation
		// toutes les 20 millisecondes
		static coo CordClick = {-1, -1};
		static coo *ptCordClick = &CordClick;

		demandeTemporisation(20);
		break;

	case Temporisation:
		rafraichisFenetre();
		break;

	case Affichage:

		// On part d'un fond d'ecran blanc
		effaceFenetre(255, 255, 255);
		if (difficulteChoisis) // Affiche la grille
		{
			// printf("Début affichage %ld \n", time(NULL) - tempsInitial);
			if (COTE_IMAGE * (15 + difficulty * 5) > hauteurFenetre()) // Calcul pour savoir si la grille rentre dans la fenetre
			{
				tailleImage = 16;
			}
			else
			{
				tailleImage = 32;
			}
			// Affichage de la grille
			initImage(plateau, difficulty, tailleImage);
			// printf("Début quadrillage\n");
			quadrillage(plateau, difficulty, tailleImage);
			// printf("Fin quadrillage\n");
			couleurCourante(0, 0, 0);
			epaisseurDeTrait(1);
			afficheChaine(chaineTemps, 14, 0, hauteurFenetre() - 30);
			afficheChaine(chaineDrapeau, 14, largeurFenetre() - 80, hauteurFenetre() - 30);
			// printf("Fin affichage %ld\n \n", time(NULL) - tempsInitial);
		}

		else // Affiche le menu de selection de difficultée
		{
			couleurCourante(0, 255, 0);
			rectangle(largeurFenetre() / 5, hauteurFenetre() / 3, largeurFenetre() * 2 / 5, hauteurFenetre() * 2 / 3);
			couleurCourante(0, 0, 255);
			rectangle(largeurFenetre() * 2 / 5, hauteurFenetre() / 3, largeurFenetre() * 3 / 5, hauteurFenetre() * 2 / 3);
			couleurCourante(255, 0, 0);
			rectangle(largeurFenetre() * 3 / 5, hauteurFenetre() / 3, largeurFenetre() * 4 / 5, hauteurFenetre() * 2 / 3);

			afficheChaine("Selectionnez la difficulte ", 27, largeurFenetre() / 2 - 150, hauteurFenetre() * 2 / 3 + 30);
			afficheChaine("Facile", 20, largeurFenetre() / 5 + 50, hauteurFenetre() / 3 + 50);
		}
		if (aPerdu) // Affiche les elements relative à lorsqu'on perd
		{

			couleurCourante(230, 230, 230);
			rectangle(5, 5, 130, 30);
			couleurCourante(0, 0, 0);
			afficheChaine("Recommencer", 15, 15, 10);
		}
		else if (aGagne) // Affiche les elements relative à lorsqu'on gagne
		{
			couleurCourante(230, 230, 230);
			rectangle(5, 5, 130, 30);
			couleurCourante(0, 0, 0);
			afficheChaine("Recommencer", 15, 15, 10);
			afficheChaine("Victoire", 12, 10, 100);
		}
		else // Actualise le timer si l'on est toujours en partit
		{
			timer(tempsInitial, chaineTemps, aPerdu);
		}

		break;

	case Clavier:
		// printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

		switch (caractereClavier())
		{
		case 'Q': /* Pour sortir quelque peu proprement du programme */
		case 'q':
			termineBoucleEvenements();
			break;

		case 'F':
		case 'f':
			pleinEcran = !pleinEcran; // Changement de mode plein ecran
			if (pleinEcran)
				modePleinEcran();
			else
				redimensionneFenetre(LargeurFenetre, HauteurFenetre);
			break;
		}
		break;

	case ClavierSpecial:
		// printf("ASCII %d\n", toucheClavier());

		break;

	case BoutonSouris:
		switch (etatBoutonSouris())
		{
		case GaucheAppuye:
			// printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			if (!difficulteChoisis) // Selection de la difficulté
			{
				if (cliqueButton(largeurFenetre() / 5, hauteurFenetre() / 3, largeurFenetre() * 2 / 5, hauteurFenetre() * 2 / 3))
				{
					difficulty = 0;
					difficulteChoisis = true;
				}
				else if (cliqueButton(largeurFenetre() * 2 / 5, hauteurFenetre() / 3, largeurFenetre() * 3 / 5, hauteurFenetre() * 2 / 3))
				{
					difficulty = 1;
					difficulteChoisis = true;
				}
				else if (cliqueButton(largeurFenetre() * 3 / 5, hauteurFenetre() / 3, largeurFenetre() * 4 / 5, hauteurFenetre() * 2 / 3))
				{
					difficulty = 2;
					difficulteChoisis = true;
				}
			}

			else if (targetMouse(ptCordClick, difficulty, tailleImage) && !aPerdu && difficulteChoisis)
			{
				if (!premierClique) // Initialisation du tableau avec le premier clique
				{
					initBomb(plateau, CordClick.x, CordClick.y, difficulty, nbFlag);
					initNumber(plateau, difficulty);
					initImage(plateau, difficulty, tailleImage);
					// afficheTab(plateau, difficulty);
					premierClique = true;
				}

				// infoCase(plateau, CordClick.x, CordClick.y);
				if (plateau[CordClick.x][CordClick.y].flag == 0) // Clique normal en verifiant qu'il ne soit pas sur un drapeau
				{
					if (plateau[CordClick.x][CordClick.y].bomb == 0) // Clique meme chose mais pour les bombes
					{
						revealer(plateau, CordClick.x, CordClick.y, difficulty);
						// printf("reveal fait \n");
						nbFlag = tab_difficulty[difficulty];
						trouveFlag(plateau, difficulty, ptFlag);
						// printf("Flag fait \n");

						actualiseChaineDrapeau(chaineDrapeau, *ptFlag);
						// printf("Chaine actualiser \n");
						aGagne = verifAGagne(plateau, difficulty);
						// printf("A gagné fait \n\n");
					}
					else // Clique sur une bombe
					{
						aPerdu = true;
						explosion(plateau, difficulty, CordClick.x, CordClick.y);
						revealBomb(plateau, difficulty);
					}
				}
				else
				{
					printf("Clique sur drapeau \n");
				}
			}
			else
			{
				printf("pas dedans \n");
			}
			if ((aPerdu || aGagne) && cliqueButton(5, 5, 130, 30)) // Cas du clique sur le boutton recommencer
			{
				aPerdu = false, premierClique = false, initialisationFaite = false, difficulteChoisis = false, aGagne = false;
			}

			break;
		case GaucheRelache:
			// printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			break;
		case DroiteAppuye:
			couleurCourante(0, 0, 255);
			if (targetMouse(ptCordClick, difficulty, tailleImage) && !aPerdu && difficulteChoisis)
			{
				flager(plateau, CordClick.x, CordClick.y, ptFlag, tailleImage);
				actualiseChaineDrapeau(chaineDrapeau, nbFlag);
			}
			break;
		case DroiteRelache:
			// puts("Bouton droite");
			break;
		case MilieuAppuye:
		case MilieuRelache:
			puts("Bouton milieu");
			break;
		case ScrollDown:
			puts("Scroll down");
			aGagne = true;
			break;
		case ScrollUp:
			puts("Scroll up");
			break;
		case ScrollRight:
			puts("Scroll right");
			break;
		case ScrollLeft:
			puts("Scroll left");
			break;
		}
		break;

	case Souris: // Si la souris est deplacee
		break;

	case Inactivite: // Quand aucun message n'est disponible
		break;

	case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
		// Donc le systeme nous en informe
		printf("Largeur : %d\t", largeurFenetre());
		printf("Hauteur : %d\n", hauteurFenetre());
		break;
	}
}

void initImage(cell plateau[LONGUEUR][LARGEUR], int difficulty, int tailleImage)
{
	int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
	for (int y = 1; y < nbLigne - 1; y++)
	{
		for (int x = 1; x < nbColonne - 1; x++)
		{
			libereDonneesImageRGB(&plateau[y][x].image);
			libereDonneesImageRGB(&plateau[y][x].imageDepart);

			if (tailleImage == 32)
			{
				if (plateau[y][x].flag == 1)
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/flag.bmp");
				}
				else
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/vide.bmp");
				}
				switch (plateau[y][x].number)
				{
				case 0:
					plateau[y][x].image = lisBMPRGB("../images/0.bmp");
					break;
				case 1:
					plateau[y][x].image = lisBMPRGB("../images/1.bmp");
					break;
				case 2:
					plateau[y][x].image = lisBMPRGB("../images/2.bmp");
					break;
				case 3:
					plateau[y][x].image = lisBMPRGB("../images/3.bmp");
					break;
				case 4:
					plateau[y][x].image = lisBMPRGB("../images/4.bmp");
					break;
				case 5:
					plateau[y][x].image = lisBMPRGB("../images/5.bmp");
					break;
				case 6:
					plateau[y][x].image = lisBMPRGB("../images/6.bmp");
					break;
				case 7:
					plateau[y][x].image = lisBMPRGB("../images/7.bmp");
					break;
				case 8:
					plateau[y][x].image = lisBMPRGB("../images/8.bmp");
					break;
				default:
					break;
				}
				if (plateau[y][x].bomb == 1)
				{
					plateau[y][x].image = lisBMPRGB("../images/bomb.bmp");
				}
				if (plateau[y][x].explosion)
				{
					plateau[y][x].image = lisBMPRGB("../images/boom.bmp");
				}
			}
			else if (tailleImage == 16)
			{
				if (plateau[y][x].flag == 1)
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/flag-16.bmp");
				}
				else
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/vide-16.bmp");
				}

				switch (plateau[y][x].number)
				{
				case 0:
					plateau[y][x].image = lisBMPRGB("../images/0-16.bmp");
					break;
				case 1:
					plateau[y][x].image = lisBMPRGB("../images/1-16.bmp");
					break;
				case 2:
					plateau[y][x].image = lisBMPRGB("../images/2-16.bmp");
					break;
				case 3:
					plateau[y][x].image = lisBMPRGB("../images/3-16.bmp");
					break;
				case 4:
					plateau[y][x].image = lisBMPRGB("../images/4-16.bmp");
					break;
				case 5:
					plateau[y][x].image = lisBMPRGB("../images/5-16.bmp");
					break;
				case 6:
					plateau[y][x].image = lisBMPRGB("../images/6-16.bmp");
					break;
				case 7:
					plateau[y][x].image = lisBMPRGB("../images/7-16.bmp");
					break;
				case 8:
					plateau[y][x].image = lisBMPRGB("../images/8-16.bmp");
					break;
				default:
					break;
				}
				if (plateau[y][x].bomb == 1)
				{
					plateau[y][x].image = lisBMPRGB("../images/bomb-16.bmp");
				}
				if (plateau[y][x].explosion)
				{
					plateau[y][x].image = lisBMPRGB("../images/boom-16.bmp");
				}
			}
		}
	}
}

void quadrillage(cell plateau[LONGUEUR][LARGEUR], int difficulty, int tailleImage)
{

	int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
	for (int i = 1; i < nbLigne - 1; i++)
	{
		for (int j = 1; j < nbColonne - 1; j++)
		{
			// infoCase(plateau, i, j);
			if (plateau[i][j].revealed == 0)
			{
				ecrisImage(largeurFenetre() / 2 - (tailleImage * nbColonne) / 2 + tailleImage * j, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2 + tailleImage * i, tailleImage, tailleImage, plateau[i][j].imageDepart->donneesRGB);
			}
			else
			{
				ecrisImage(largeurFenetre() / 2 - (tailleImage * nbColonne) / 2 + tailleImage * j, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2 + tailleImage * i, tailleImage, tailleImage, plateau[i][j].image->donneesRGB);
			}
		}
	}
}
