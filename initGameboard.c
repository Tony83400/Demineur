#include <stdlib.h>		   // Pour pouvoir utiliser exit()
#include <stdio.h>		   // Pour pouvoir utiliser printf()
#include <math.h>		   // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "Fonction.h"
#include <time.h>
#include <unistd.h>

void initTab(cell tab[LONGUEUR][LARGEUR], int difficulty)
{
    int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;

    for (int i = 1; i < nbLigne - 1; i++)
    {
        for (int j = 1; j < nbColonne - 1; j++)
        {
            tab[i][j].bomb = 0;
            tab[i][j].flag = 0;
            tab[i][j].number = 0;
            tab[i][j].revealed = 0;
            tab[i][j].imageDepart = lisBMPRGB("../images/x32/vide.bmp");
            tab[i][j].explosion = 0;
        }
    }
}

void initBomb(cell tab[LONGUEUR][LARGEUR], int x, int y, int difficulty, int nbBomb)
{
    int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
    int xr;
    int yr;

    for (int k = 1; k <= nbBomb; k++)
    {
        xr = rand() % (nbLigne - 2) + 1;
        yr = rand() % (nbColonne - 2) + 1;
        if ((xr >= x - 1 && xr <= x + 1 && yr >= y - 1 && yr <= y + 1) || tab[xr][yr].bomb == 1)
        {
            k = k - 1;
        }
        else
        {
            tab[xr][yr].bomb = 1;
        }
    }

    tab[x - 1][y - 1].bomb = 0;
    tab[x - 1][y].bomb = 0;
    tab[x - 1][y + 1].bomb = 0;
    tab[x][y - 1].bomb = 0;
    tab[x][y].bomb = 0;
    tab[x][y + 1].bomb = 0;
    tab[x + 1][y - 1].bomb = 0;
    tab[x + 1][y].bomb = 0;
    tab[x + 1][y + 1].bomb = 0;
}


int verifVoisin(cell tab[LONGUEUR][LARGEUR], int x, int y)
{
    int voisin = 0;
    if (tab[x - 1][y - 1].bomb == 1)
    {
        voisin = voisin + 1;
    }
    if (tab[x][y - 1].bomb == 1)
    {
        voisin = voisin + 1;
    }
    if (tab[x + 1][y - 1].bomb == 1)
    {
        voisin = voisin + 1;
    }
    if (tab[x - 1][y].bomb == 1)
    {
        voisin = voisin + 1;
    }
    if (tab[x + 1][y].bomb == 1)
    {
        voisin = voisin + 1;
    }
    if (tab[x - 1][y + 1].bomb == 1)
    {
        voisin = voisin + 1;
    }
    if (tab[x][y + 1].bomb == 1)
    {
        voisin = voisin + 1;
    }
    if (tab[x + 1][y + 1].bomb == 1)
    {
        voisin = voisin + 1;
    }
    return voisin;
}

void initNumber(cell tab[LONGUEUR][LARGEUR], int difficulty)
{
    int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
    for (int i = 1; i < nbLigne - 1; i++)
    {
        for (int j = 1; j < nbColonne - 1; j++)
        {
            if (tab[i][j].bomb == 0)
            {
                tab[i][j].number = verifVoisin(tab, i, j);
            }
            else
            {
                tab[i][j].number = -1;
            }
        }
    }
}