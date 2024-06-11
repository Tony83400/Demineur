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
	static cell plateau[LONGUEUR][LARGEUR];
	static bool initialisationFaite = false;
	if (!initialisationFaite)
	{
		initImage(plateau, 0);
		initialisationFaite = true;
	}

	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	switch (evenement)
	{
	case Initialisation:

		// Configure le systeme pour generer un message Temporisation
		// toutes les 20 millisecondes
		coo CordClick = {-1, -1};
		coo *ptCordClick = &CordClick;

		demandeTemporisation(20);
		break;

	case Temporisation:
		rafraichisFenetre();
		break;

	case Affichage:

		// On part d'un fond d'ecran blanc
		effaceFenetre(255, 255, 255);
		couleurCourante(255, 0, 0);
		// rectangle(largeurFenetre() / 3, hauteurFenetre() - GAP, largeurFenetre() * 2 / 3, GAP);
		quadrillage(plateau, 0);
		cercle(abscisseSouris(), ordonneeSouris(), 1);

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
			targetMouse(ptCordClick, 10, 15);
			break;
		case GaucheRelache:
			printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			break;
		case DroiteAppuye:
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

void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 20; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2. * M_PI / Pas;
	int index;

	for (index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2. * M_PI * index / Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX + rayon * cos(angle), centreY + rayon * sin(angle),
				 centreX + rayon * cos(angle + PasAngulaire), centreY + rayon * sin(angle + PasAngulaire));
		// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
}

void initImage(cell plateau[LONGUEUR][LARGEUR], int difficulty)
{
	// int nbColonne = 10 + difficulty * 5, nbLigne = 15 + difficulty * 5;
	for (int y = 1; y < LONGUEUR - 1; y++)
	{
		for (int x = 1; x < LARGEUR - 1; x++)
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
		}
	}
}

void quadrillage(cell plateau[LONGUEUR][LARGEUR], int diffculty)
{
	int nbColonne = 10 + diffculty * 5, nbLigne = 15 + diffculty * 5;
	for (int i = 0; i < LONGUEUR - 2; i++)
	{
		for (int j = 0; j < LARGEUR - 2; j++)
		{
			if (plateau[i + 1][j + 1].flag == 1)
			{
				plateau[i + 1][j + 1].image = lisBMPRGB("../images/flag.bmp");
			}
			else
			{
				plateau[i + 1][j + 1].image = lisBMPRGB("../images/vide.bmp");
			}

			if (plateau[i + 1][j + 1].revealed == 0)
			{
				ecrisImage(largeurFenetre() / 2 - (COTE_IMAGE * nbColonne) / 2 + COTE_IMAGE * j, hauteurFenetre() / 2 - (COTE_IMAGE * nbLigne) / 2 + COTE_IMAGE * i, COTE_IMAGE, COTE_IMAGE, plateau[i + 1][j + 1].imageDepart->donneesRGB);
			}
			else
			{
				ecrisImage(largeurFenetre() / 2 - (COTE_IMAGE * nbColonne) / 2 + COTE_IMAGE * j, hauteurFenetre() / 2 - (COTE_IMAGE * nbLigne) / 2 + COTE_IMAGE * i, COTE_IMAGE, COTE_IMAGE, plateau[i + 1][j + 1].image->donneesRGB);
			}
		}
	}
}
