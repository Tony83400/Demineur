#include <time.h>
#include <unistd.h>

#include <stdlib.h>		   // Pour pouvoir utiliser exit()
#include <stdio.h>		   // Pour pouvoir utiliser printf()
#include <math.h>		   // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "Fonction.h"

void initTab(cell tab[LONGUEUR][LARGEUR], int x, int y, int difficult)
{
    // tab = malloc(sizeof(*cell)*10)
    // for (int i = 0; i < 15; i++)
    // {
    //     tab[i] = malloc(sizeof(cell)*15);
    // }
    int xr;
    int yr;
    for (int i = 1; i < LONGUEUR - 1; i++)
    {
        for (int j = 1; j < LARGEUR - 1; j++)
        {
            tab[i][j].bomb = 0;
        }
    }
    for (int k = 1; k < difficult + 1; k++)
    {
        xr = rand() % 14 + 1;
        yr = rand() % 9 + 1;
        if (xr >= x - 1 && xr <= x + 1 && yr >= y - 1 && yr <= y + 1 || tab[xr][yr].bomb == 1)
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

void afficheTab(cell tab[LONGUEUR][LARGEUR], int x, int y)
{
    for (int i = 1; i < LONGUEUR - 1; i++)
    {
        for (int j = 1; j < LARGEUR - 1; j++)
        {
            // if (i == x && j == y)
            //{
            //	printf(" %2d ", 50);
            // }
            if (tab[i][j].bomb == 1)
            {
                printf(" %2d ", -1);
            }
            else
            {
                printf(" %2d ", tab[i][j].number);
            }
        }
        printf("\n");
    }
    printf("\n");
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

void initNumber(cell tab[LONGUEUR][LARGEUR])
{
    for (int i = 1; i < LONGUEUR - 1; i++)
    {
        for (int j = 1; j < LARGEUR - 1; j++)
        {
            tab[i][j].number = verifVoisin(tab, i, j);
        }
    }
}

int nbBombe(cell tab[LONGUEUR][LARGEUR])
{
    int nbBombe = 0;
    for (int i = 1; i < LONGUEUR - 1; i++)
    {
        for (int j = 1; j < LARGEUR - 1; j++)
        {
            if (tab[i][j].bomb == 1)
            {
                nbBombe = nbBombe + 1;
            }
        }
    }
    return nbBombe;
}

int aGagne(cell tab[LONGUEUR][LARGEUR])
{
    for (int i = 1; i < LONGUEUR - 1; i++)
    {
        for (int j = 1; j < LARGEUR - 1; j++)
        {
            if (tab[i][j].bomb != tab[i][j].flag)
            {
                return 0;
            }
        }
    }
    return 1;
}

int aPerdu(cell tab[LONGUEUR][LARGEUR], int x, int y)
{
    if (tab[x][y].bomb == 1)
    {
        return 1;
    }
    return 0;
}

void flager(cell tab[LONGUEUR][LARGEUR], int x, int y)
{
    tab[x][y].flag = 1;
}

