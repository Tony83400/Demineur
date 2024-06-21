#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>        // Pour pouvoir utiliser exit()
#include <stdio.h>         // Pour pouvoir utiliser printf()
#include <math.h>          // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "Fonction.h"
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

void trouveFlag(cell tab[LONGUEUR][LARGEUR], int difficulty, int *ptFlag)
{
    int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;

    for (int i = 1; i < nbLigne - 1; i++)
    {
        for (int j = 1; j < nbColonne - 1; j++)
        {
            if (tab[i][j].flag == 1)
            {
                *ptFlag = *ptFlag - 1;
            }
        }
    }
}

bool verifAGagne(cell tab[LONGUEUR][LARGEUR], int difficulty)
{
    int nbColonne = 10 + difficulty * 5 + 2, nbLigne = 15 + difficulty * 5 + 2;

    for (int i = 1; i < nbLigne - 1; i++)
    {
        for (int j = 1; j < nbColonne - 1; j++)
        {
            if (tab[i][j].bomb == tab[i][j].revealed)
            {
                return false;
            }
        }
    }
    return true;
}


void flager(cell tab[LONGUEUR][LARGEUR], int x, int y, int *nbFlag, int tailleImage)
{
    if (tab[x][y].revealed == 0)
    {
        if (tab[x][y].flag == 0)
        {
            tab[x][y].flag = 1;
            *nbFlag = *nbFlag - 1;
        }
        else
        {
            tab[x][y].flag = 0;
            *nbFlag = *nbFlag + 1;
        }
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
                    tab[cx - 1][cy - 1].flag = 0;

                    tab2[indice].x = cx - 1;
                    tab2[indice].y = cy - 1;
                    indice++;
                }
                if (cy - 1 > 0 && tab[cx][cy - 1].revealed == 0)
                {
                    tab[cx][cy - 1].revealed = 1;
                    tab[cx][cy - 1].flag = 0;

                    tab2[indice].x = cx;
                    tab2[indice].y = cy - 1;
                    indice++;
                }
                if (cx + 1 < nbLigne - 1 && cy - 1 > 0 && tab[cx + 1][cy - 1].revealed == 0)
                {
                    tab[cx + 1][cy - 1].revealed = 1;
                    tab[cx + 1][cy - 1].flag = 0;

                    tab2[indice].x = cx + 1;
                    tab2[indice].y = cy - 1;
                    indice++;
                }
                if (cx - 1 > 0 && tab[cx - 1][cy].revealed == 0)
                {
                    tab[cx - 1][cy].revealed = 1;
                    tab[cx - 1][cy].flag = 0;

                    tab2[indice].x = cx - 1;
                    tab2[indice].y = cy;
                    indice++;
                }
                if (cx + 1 < nbLigne - 1 && tab[cx + 1][cy].revealed == 0)
                {
                    tab[cx + 1][cy].revealed = 1;
                    tab[cx + 1][cy].flag = 0;

                    tab2[indice].x = cx + 1;
                    tab2[indice].y = cy;
                    indice++;
                }
                if (cx - 1 > 0 && cy + 1 < nbColonne - 1 && tab[cx - 1][cy + 1].revealed == 0)
                {
                    tab[cx - 1][cy + 1].revealed = 1;
                    tab[cx - 1][cy + 1].flag = 0;

                    tab2[indice].x = cx - 1;
                    tab2[indice].y = cy + 1;
                    indice++;
                }
                if (cy + 1 < nbColonne - 1 && tab[cx][cy + 1].revealed == 0)
                {
                    tab[cx][cy + 1].revealed = 1;
                    tab[cx][cy + 1].flag = 0;

                    tab2[indice].x = cx;
                    tab2[indice].y = cy + 1;
                    indice++;
                }
                if (cx + 1 < nbLigne - 1 && cy + 1 < nbColonne - 1 && tab[cx + 1][cy + 1].revealed == 0)
                {
                    tab[cx + 1][cy + 1].revealed = 1;
                    tab[cx + 1][cy + 1].flag = 0;

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
                tab[i][j].flag = 0;
            }
        }
    }
}
void explosion(cell tab[LONGUEUR][LARGEUR], int difficulty, int x, int y)
{
    tab[x][y].explosion = true;
    tab[x][y].revealed = 1;
}

void timer(int time0, char *chaine, bool aPerdu)
{
    if (!aPerdu)
    {
        char chaineSec[50], chaineMin[50];
        int temps = time(NULL);

        int minute = (temps - time0) / 60;
        int seconde = (temps - time0) - 60 * (minute);
        sprintf(chaineSec, "%d", seconde);
        strcat(chaineSec, " sec");

        if (minute > 0)
        {
            sprintf(chaineMin, "%d", minute);
            strcat(chaineMin, " min ");
            strcat(chaineMin, chaineSec);
            strcpy(chaine, chaineMin);
        }
        else
        {
            strcpy(chaine, chaineSec);
        }
    }
}

void actualiseChaineDrapeau(char chaineDrapeau[50], int nbDrapeau)
{
    char chaineTemp[50];
    sprintf(chaineTemp, "%d", nbDrapeau);
    strcat(chaineTemp, " flag");
    strcpy(chaineDrapeau, chaineTemp);
}
