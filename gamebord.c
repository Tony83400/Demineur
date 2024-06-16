#include <time.h>
#include <unistd.h>

#include <stdlib.h>        // Pour pouvoir utiliser exit()
#include <stdio.h>         // Pour pouvoir utiliser printf()
#include <math.h>          // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "Fonction.h"

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
        xr = rand() % (nbLigne - 1) + 1;
        yr = rand() % (nbColonne - 1) + 1;
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

void afficheTab(cell tab[LONGUEUR][LARGEUR], int difficulty)
{
    int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
    for (int i = 1; i < nbLigne - 1; i++)
    {
        for (int j = 1; j < nbColonne - 1; j++)
        {

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

void flager(cell tab[LONGUEUR][LARGEUR], int x, int y, int *nbFlag)
{
    if (tab[x][y].flag == 0)
    {
        tab[x][y].flag = 1;
        tab[x][y].imageDepart = lisBMPRGB("../images/flag.bmp");
        *nbFlag = *nbFlag - 1;
    }
    else
    {
        tab[x][y].flag = 0;
        tab[x][y].imageDepart = lisBMPRGB("../images/vide.bmp");
        *nbFlag = *nbFlag + 1;
    }
}

void copieList(coo tab1[LARGEUR * LONGUEUR], coo tab2[LARGEUR * LONGUEUR], int difficulty)
{
    int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
    for (int i = 0; i < nbColonne * nbLigne; i++)
    {
        tab1[i] = tab2[i];
    }
}

void revealer(cell tab[LONGUEUR][LARGEUR], int x, int y, int difficulty)
{
    int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
    tab[x][y].revealed = 1;
    coo tab1[nbLigne * nbColonne];
    tab1[0].x = x;
    tab1[0].y = y;
    int nbrVoisin = 1;

    while (nbrVoisin > 0)
    {
        coo tab2[nbLigne * nbColonne];
        int indice = 0;

        for (int i = 0; i < nbrVoisin; i++)
        {
            int cx = tab1[i].x;
            int cy = tab1[i].y;

            if (tab[cx][cy].number == 0)
            {
                if (cx - 1 > 0 && cy - 1 > 0 && tab[cx - 1][cy - 1].revealed == 0)
                {
                    tab[cx - 1][cy - 1].revealed = 1;
                    tab2[indice].x = cx - 1;
                    tab2[indice].y = cy - 1;
                    indice++;
                }
                if (cy - 1 > 0 && tab[cx][cy - 1].revealed == 0)
                {
                    tab[cx][cy - 1].revealed = 1;
                    tab2[indice].x = cx;
                    tab2[indice].y = cy - 1;
                    indice++;
                }
                if (cx + 1 < nbLigne - 1 && cy - 1 > 0 && tab[cx + 1][cy - 1].revealed == 0)
                {
                    tab[cx + 1][cy - 1].revealed = 1;
                    tab2[indice].x = cx + 1;
                    tab2[indice].y = cy - 1;
                    indice++;
                }
                if (cx - 1 > 0 && tab[cx - 1][cy].revealed == 0)
                {
                    tab[cx - 1][cy].revealed = 1;
                    tab2[indice].x = cx - 1;
                    tab2[indice].y = cy;
                    indice++;
                }
                if (cx + 1 < nbLigne - 1 && tab[cx + 1][cy].revealed == 0)
                {
                    tab[cx + 1][cy].revealed = 1;
                    tab2[indice].x = cx + 1;
                    tab2[indice].y = cy;
                    indice++;
                }
                if (cx - 1 > 0 && cy + 1 < nbColonne - 1 && tab[cx - 1][cy + 1].revealed == 0)
                {
                    tab[cx - 1][cy + 1].revealed = 1;
                    tab2[indice].x = cx - 1;
                    tab2[indice].y = cy + 1;
                    indice++;
                }
                if (cy + 1 < nbColonne - 1 && tab[cx][cy + 1].revealed == 0)
                {
                    tab[cx][cy + 1].revealed = 1;
                    tab2[indice].x = cx;
                    tab2[indice].y = cy + 1;
                    indice++;
                }
                if (cx + 1 < nbLigne - 1 && cy + 1 < nbColonne - 1 && tab[cx + 1][cy + 1].revealed == 0)
                {
                    tab[cx + 1][cy + 1].revealed = 1;
                    tab2[indice].x = cx + 1;
                    tab2[indice].y = cy + 1;
                    indice++;
                }
            }
        }

        nbrVoisin = indice;
        copieList(tab1, tab2, difficulty);
    }
}
void infoCase(cell tab[LONGUEUR][LARGEUR], int x, int y)
{
    printf("x : %d , y : %d \n", x, y);
    printf("Nombre : %d \n", tab[x][y].number);
    printf("Bombe : %d \n", tab[x][y].bomb);
    printf("Drapeau : %d \n", tab[x][y].flag);
    printf("Reveal : %d \n", tab[x][y].revealed);
}

void revealBomb(cell tab[LONGUEUR][LARGEUR], int difficulty)
{
    int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;
    for (int i = 0; i < nbLigne; i++)
    {
        for (int j = 0; j < nbColonne; j++)
        {
            if (tab[i][j].bomb == 1)
            {
                tab[i][j].revealed = 1;
            }
        }
    }
}
void explosion(cell tab[LONGUEUR][LARGEUR], int difficulty, int x, int y)
{
    tab[x][y].image = lisBMPRGB("../images/boom.bmp");
    tab[x][y].revealed = 1;
}
