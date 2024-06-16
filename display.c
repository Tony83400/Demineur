#include <stdlib.h>		   // Pour pouvoir utiliser exit()
#include <stdio.h>		   // Pour pouvoir utiliser printf()
#include <math.h>		   // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "Fonction.h"

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */

void gestionEvenement(EvenementGfx evenement)
{

	static int difficulty = 2;
	static int tab_difficulty[3] = {18, 45, 100};
	static int nbFlag = 0;
	static int *ptFlag = &nbFlag;
	static bool aPerdu = false, premierClique = false;

	static cell plateau[LONGUEUR][LARGEUR];
	static bool initialisationFaite = false;
	if (!initialisationFaite)
	{
		nbFlag = tab_difficulty[difficulty];
		initTab(plateau, difficulty);
		initImage(plateau, difficulty);
		afficheTab(plateau, difficulty);
		initialisationFaite = true;
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
		couleurCourante(255, 0, 0);

		quadrillage(plateau, difficulty);

		break;

	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

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
		printf("ASCII %d\n", toucheClavier());

		break;

	case BoutonSouris:
		switch (etatBoutonSouris())
		{
		case GaucheAppuye:
			printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			couleurCourante(0, 255, 0);

			if (targetMouse(ptCordClick, difficulty) && !aPerdu)
			{
				if (!premierClique)
				{
					initBomb(plateau,CordClick.x,CordClick.y,difficulty,nbFlag);
					initNumber(plateau, difficulty);
					initImage(plateau, difficulty);
					afficheTab(plateau, difficulty);
					printf("%d\n", nbBombe(plateau));
					premierClique = true;
				}

				infoCase(plateau, CordClick.x, CordClick.y);
				if (plateau[CordClick.x][CordClick.y].flag == 0)
				{
					if (plateau[CordClick.x][CordClick.y].bomb == 0)
					{
						revealer(plateau, CordClick.x, CordClick.y, difficulty);
					}
					else
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
			break;
		case GaucheRelache:
			printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			break;
		case DroiteAppuye:
			couleurCourante(0, 0, 255);
			if (targetMouse(ptCordClick, difficulty) && !aPerdu)
			{
				flager(plateau, CordClick.x, CordClick.y, ptFlag);
			}
			break;
		case DroiteRelache:
			puts("Bouton droite");
			break;
		case MilieuAppuye:
		case MilieuRelache:
			puts("Bouton milieu");
			break;
		case ScrollDown:
			puts("Scroll down");
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

void initImage(cell plateau[LONGUEUR][LARGEUR], int difficulty)
{
	int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
	for (int y = 1; y < nbLigne - 1; y++)
	{
		for (int x = 1; x < nbColonne - 1; x++)
		{
			plateau[y][x].imageDepart = lisBMPRGB("../images/vide.bmp");

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
			if (plateau[y][x].bomb)
			{
				plateau[y][x].image = lisBMPRGB("../images/bomb.bmp");
			}

			if (plateau[y][x].image == NULL)
			{
				printf("Erreur: échec du chargement de l'image pour plateau[%d][%d]\n", y, x);
				continue;
			}
			if (plateau[y][x].imageDepart == NULL)
			{
				printf("Erreur: échec du chargement de l'imageDepart pour plateau[%d][%d]\n", y, x);
				continue;
			}
		}
	}
}

void quadrillage(cell plateau[LONGUEUR][LARGEUR], int difficulty)
{
	int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
	for (int i = 1; i < nbLigne - 1; i++)
	{
		for (int j = 1; j < nbColonne - 1; j++)
		{
			if (plateau[i][j].revealed == 0)
			{
				ecrisImage(largeurFenetre() / 2 - (COTE_IMAGE * nbColonne) / 2 + COTE_IMAGE * j, hauteurFenetre() / 2 - (COTE_IMAGE * nbLigne) / 2 + COTE_IMAGE * i, COTE_IMAGE, COTE_IMAGE, plateau[i][j].imageDepart->donneesRGB);
			}
			else
			{
				ecrisImage(largeurFenetre() / 2 - (COTE_IMAGE * nbColonne) / 2 + COTE_IMAGE * j, hauteurFenetre() / 2 - (COTE_IMAGE * nbLigne) / 2 + COTE_IMAGE * i, COTE_IMAGE, COTE_IMAGE, plateau[i][j].image->donneesRGB);
			}
		}
	}
}
