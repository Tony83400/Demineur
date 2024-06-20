#include <stdlib.h>		   // Pour pouvoir utiliser exit()
#include <stdio.h>		   // Pour pouvoir utiliser printf()
#include <math.h>		   // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "Fonction.h"
#include <time.h>
#include <unistd.h>

void initImage(cell plateau[LONGUEUR][LARGEUR], int difficulty, int tailleImage)
{
	int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
	for (int y = 1; y < nbLigne - 1; y++)
	{
		for (int x = 1; x < nbColonne - 1; x++)
		{
			libereDonneesImageRGB(&plateau[y][x].image);
			libereDonneesImageRGB(&plateau[y][x].imageDepart);
			// infoCase(plateau,y,x);
			if (tailleImage == 32)
			{
				if (plateau[y][x].flag == 1)
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/x32/flag.bmp");
				}
				else
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/x32/vide.bmp");
				}
				switch (plateau[y][x].number)
				{
				case 0:
					plateau[y][x].image = lisBMPRGB("../images/x32/0.bmp");
					break;
				case 1:
					plateau[y][x].image = lisBMPRGB("../images/x32/1.bmp");
					break;
				case 2:
					plateau[y][x].image = lisBMPRGB("../images/x32/2.bmp");
					break;
				case 3:
					plateau[y][x].image = lisBMPRGB("../images/x32/3.bmp");
					break;
				case 4:
					plateau[y][x].image = lisBMPRGB("../images/x32/4.bmp");
					break;
				case 5:
					plateau[y][x].image = lisBMPRGB("../images/x32/5.bmp");
					break;
				case 6:
					plateau[y][x].image = lisBMPRGB("../images/x32/6.bmp");
					break;
				case 7:
					plateau[y][x].image = lisBMPRGB("../images/x32/7.bmp");
					break;
				case 8:
					plateau[y][x].image = lisBMPRGB("../images/x32/8.bmp");
					break;
				default:
					break;
				}
				if (plateau[y][x].bomb == 1)
				{
					plateau[y][x].image = lisBMPRGB("../images/x32/bomb.bmp");
				}
				if (plateau[y][x].explosion)
				{
					plateau[y][x].image = lisBMPRGB("../images/x32/boom.bmp");
				}
			}
			else if (tailleImage == 16)
			{
				if (plateau[y][x].flag == 1)
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/x16/flag-16.bmp");
				}
				else
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/x16/vide-16.bmp");
				}

				switch (plateau[y][x].number)
				{
				case 0:
					plateau[y][x].image = lisBMPRGB("../images/x16/0-16.bmp");
					break;
				case 1:
					plateau[y][x].image = lisBMPRGB("../images/x16/1-16.bmp");
					break;
				case 2:
					plateau[y][x].image = lisBMPRGB("../images/x16/2-16.bmp");
					break;
				case 3:
					plateau[y][x].image = lisBMPRGB("../images/x16/3-16.bmp");
					break;
				case 4:
					plateau[y][x].image = lisBMPRGB("../images/x16/4-16.bmp");
					break;
				case 5:
					plateau[y][x].image = lisBMPRGB("../images/x16/5-16.bmp");
					break;
				case 6:
					plateau[y][x].image = lisBMPRGB("../images/x16/6-16.bmp");
					break;
				case 7:
					plateau[y][x].image = lisBMPRGB("../images/x16/7-16.bmp");
					break;
				case 8:
					plateau[y][x].image = lisBMPRGB("../images/x16/8-16.bmp");
					break;
				default:
					break;
				}
				if (plateau[y][x].bomb == 1)
				{
					plateau[y][x].image = lisBMPRGB("../images/x16/bomb-16.bmp");
				}
				if (plateau[y][x].explosion)
				{
					plateau[y][x].image = lisBMPRGB("../images/x16/boom-16.bmp");
				}
			}
			else if (tailleImage == 24)
			{
				if (plateau[y][x].flag == 1)
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/x24/flag-24.bmp");
				}
				else
				{
					plateau[y][x].imageDepart = lisBMPRGB("../images/x24/vide-24.bmp");
				}

				switch (plateau[y][x].number)
				{
				case 0:
					plateau[y][x].image = lisBMPRGB("../images/x24/0-24.bmp");
					break;
				case 1:
					plateau[y][x].image = lisBMPRGB("../images/x24/1-24.bmp");
					break;
				case 2:
					plateau[y][x].image = lisBMPRGB("../images/x24/2-24.bmp");
					break;
				case 3:
					plateau[y][x].image = lisBMPRGB("../images/x24/3-24.bmp");
					break;
				case 4:
					plateau[y][x].image = lisBMPRGB("../images/x24/4-24.bmp");
					break;
				case 5:
					plateau[y][x].image = lisBMPRGB("../images/x24/5-24.bmp");
					break;
				case 6:
					plateau[y][x].image = lisBMPRGB("../images/x24/6-24.bmp");
					break;
				case 7:
					plateau[y][x].image = lisBMPRGB("../images/x24/7-24.bmp");
					break;
				case 8:
					plateau[y][x].image = lisBMPRGB("../images/x24/8-24.bmp");
					break;
				default:
					break;
				}
				if (plateau[y][x].bomb == 1)
				{
					plateau[y][x].image = lisBMPRGB("../images/x24/bomb-24.bmp");
				}
				if (plateau[y][x].explosion)
				{
					plateau[y][x].image = lisBMPRGB("../images/x24/boom-24.bmp");
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