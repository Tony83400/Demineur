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
	static DonneesImageRGB *imageVictoire;
	static DonneesImageRGB *imageDefaite;
	static DonneesImageRGB *imageFacile, *imageNormal, *imageHard;
	int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;

	static cell plateau[LONGUEUR][LARGEUR];
	if (!initialisationFaite && difficulteChoisis)
	{
		tempsInitial = time(NULL);
		nbFlag = tab_difficulty[difficulty];
		initTab(plateau, difficulty);
		initImage(plateau, difficulty, tailleImage);
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
			if (COTE_IMAGE * (nbLigne) + 140 < hauteurFenetre() && COTE_IMAGE * (nbColonne) < largeurFenetre()) // Calcul pour savoir si la grille rentre dans la fenetre
			{
				tailleImage = 32;
			}
			else if (COTE_IMAGE * 3 / 4 * (nbLigne) + 140 < hauteurFenetre() && COTE_IMAGE * 3 / 4 * (nbColonne) < largeurFenetre())
			{
				tailleImage = 24;
			}

			else
			{
				tailleImage = 16;
			}
			// Affichage de la grille
			initImage(plateau, difficulty, tailleImage);
			quadrillage(plateau, difficulty, tailleImage);
			couleurCourante(0, 0, 0);
			epaisseurDeTrait(1);
			afficheChaine(chaineTemps, 14, 0, hauteurFenetre() - 30);
			afficheChaine(chaineDrapeau, 14, largeurFenetre() - 80, hauteurFenetre() - 30);
		}

		else // Affiche le menu de selection de difficultée
		{
			
			imageFacile = lisBMPRGB("../images/easy.bmp");
			imageNormal = lisBMPRGB("../images/normal.bmp");
			imageHard = lisBMPRGB("../images/hard.bmp");

			ecrisImage(largeurFenetre() / 2 - 288, hauteurFenetre() / 2 - 96, imageFacile->largeurImage, imageFacile->hauteurImage, imageFacile->donneesRGB);
			afficheChaine("Facile", 24, largeurFenetre() / 2 - 230, hauteurFenetre() / 2 - 144);

			ecrisImage(largeurFenetre() / 2 - 96, hauteurFenetre() / 2 - 96, imageNormal->largeurImage, imageNormal->hauteurImage, imageNormal->donneesRGB);
			afficheChaine("Moyen", 24, largeurFenetre() / 2 - 36, hauteurFenetre() / 2 - 144);

			ecrisImage(largeurFenetre() / 2 + 96, hauteurFenetre() / 2 - 96, imageHard->largeurImage, imageHard->hauteurImage, imageHard->donneesRGB);
			afficheChaine("Difficile", 24, largeurFenetre() / 2 + 144, hauteurFenetre() / 2 - 144);

			couleurCourante(0, 0, 0);
			afficheChaine("Selectionnez la difficulte ", 27, largeurFenetre() / 2 - 150, hauteurFenetre() * 2 / 3 + 30);
		}
		if (aPerdu) // Affiche les elements relative à lorsqu'on perd
		{

			couleurCourante(230, 230, 230);
			rectangle(largeurFenetre() / 2 - 96, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2, largeurFenetre() / 2 + 96, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2 - 40);
			couleurCourante(0, 0, 0);
			afficheChaine("Recommencer", 24, largeurFenetre() / 2 - 86, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2 - 30);

			imageDefaite = lisBMPRGB("../images/failure.bmp");
			ecrisImage(largeurFenetre() / 2 - 88, hauteurFenetre() - (hauteurFenetre() / 2 - nbLigne * tailleImage / 2) - 14, imageDefaite->largeurImage, imageDefaite->hauteurImage, imageDefaite->donneesRGB);
		}
		else if (aGagne) // Affiche les elements relative à lorsqu'on gagne
		{
			couleurCourante(230, 230, 230);
			rectangle(largeurFenetre() / 2 - 96, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2, largeurFenetre() / 2 + 96, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2 - 40);
			couleurCourante(0, 0, 0);
			afficheChaine("Recommencer", 24, largeurFenetre() / 2 - 86, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2 - 30);

			imageVictoire = lisBMPRGB("../images/success.bmp");
			ecrisImage(largeurFenetre() / 2 - 88, hauteurFenetre() - (hauteurFenetre() / 2 - nbLigne * tailleImage / 2) - 14, imageVictoire->largeurImage, imageVictoire->hauteurImage, imageVictoire->donneesRGB);
			couleurCourante(255, 0, 0);
		}
		else // Actualise le timer si l'on est toujours en partit
		{
			timer(tempsInitial, chaineTemps, aPerdu);
		}

		break;

	case Clavier:

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
			{
				redimensionneFenetre(LargeurFenetre, HauteurFenetre);
			}
			break;
		}
		break;

	case ClavierSpecial:

		break;

	case BoutonSouris:
		switch (etatBoutonSouris())
		{
		case GaucheAppuye:

			if (!difficulteChoisis) // Selection de la difficulté
			{
				if (cliqueButton(largeurFenetre() / 2 - 288, hauteurFenetre() / 2 - 144, largeurFenetre() / 2 - 96, hauteurFenetre() / 2 + 96))
				{
					difficulty = 0;
					difficulteChoisis = true;
				}
				else if (cliqueButton(largeurFenetre() / 2 - 96, hauteurFenetre() / 2 - 144, largeurFenetre() / 2 + 96, hauteurFenetre() / 2 + 96))
				{
					difficulty = 1;
					difficulteChoisis = true;
				}
				else if (cliqueButton(largeurFenetre() / 2 + 96, hauteurFenetre() / 2 - 144, largeurFenetre() / 2 + 288, hauteurFenetre() / 2 + 96))
				{
					difficulty = 2;
					difficulteChoisis = true;
				}
			}

			else if (targetMouse(ptCordClick, difficulty, tailleImage) && !aPerdu && !aGagne && difficulteChoisis)
			{
				if (!premierClique) // Initialisation du tableau avec le premier clique
				{
					initBomb(plateau, CordClick.x, CordClick.y, difficulty, nbFlag);
					initNumber(plateau, difficulty);
					initImage(plateau, difficulty, tailleImage);
					premierClique = true;
				}

				if (plateau[CordClick.x][CordClick.y].flag == 0) // Clique normal en verifiant qu'il ne soit pas sur un drapeau
				{
					if (plateau[CordClick.x][CordClick.y].bomb == 0) // Clique meme chose mais pour les bombes
					{
						revealer(plateau, CordClick.x, CordClick.y, difficulty);

						nbFlag = tab_difficulty[difficulty];
						trouveFlag(plateau, difficulty, ptFlag);

						actualiseChaineDrapeau(chaineDrapeau, *ptFlag);
						aGagne = verifAGagne(plateau, difficulty);
					}
					else // Clique sur une bombe
					{
						aPerdu = true;
						explosion(plateau, difficulty, CordClick.x, CordClick.y);
						revealBomb(plateau, difficulty);
					}
				}
			}
			if ((aPerdu || aGagne) && cliqueButton(largeurFenetre() / 2 - 96, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2 - 40, largeurFenetre() / 2 + 96, hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2)) // Cas du clique sur le boutton recommencer
			{
				aPerdu = false, premierClique = false, initialisationFaite = false, difficulteChoisis = false, aGagne = false;
				libereDonneesImageRGB(&imageDefaite);
				libereDonneesImageRGB(&imageVictoire);
				libereDonneesImageRGB(&imageFacile);
				libereDonneesImageRGB(&imageNormal);
				libereDonneesImageRGB(&imageHard);
			}

			break;
		case GaucheRelache:

			break;
		case DroiteAppuye:
			couleurCourante(0, 0, 255);
			if (targetMouse(ptCordClick, difficulty, tailleImage) && !aPerdu && difficulteChoisis && premierClique)
			{
				flager(plateau, CordClick.x, CordClick.y, ptFlag, tailleImage);
				actualiseChaineDrapeau(chaineDrapeau, nbFlag);
			}
			break;
		case DroiteRelache:

			break;
		case MilieuAppuye:
		case MilieuRelache:
			break;
		case ScrollDown:
			break;
		case ScrollUp:
			break;
		case ScrollRight:
			break;
		case ScrollLeft:
			break;
		}
		break;

	case Souris: // Si la souris est deplacee
		break;

	case Inactivite: // Quand aucun message n'est disponible
		break;

	case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
		// Donc le systeme nous en informe
		break;
	}
}
