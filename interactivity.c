#include <stdlib.h>        // Pour pouvoir utiliser exit()
#include <stdio.h>         // Pour pouvoir utiliser printf()
#include <math.h>          // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "Fonction.h"

bool targetMouse(coo *coord, int difficulty)
{
    int nbColonne = 10 + difficulty * 5, nbLigne = 15 + difficulty * 5;

    if (abscisseSouris() > largeurFenetre() / 2 - (COTE_IMAGE * nbColonne) / 2 && abscisseSouris() < largeurFenetre() / 2 + (COTE_IMAGE * nbColonne) / 2 && ordonneeSouris() > hauteurFenetre() / 2 - (COTE_IMAGE * nbLigne) / 2 && ordonneeSouris() < hauteurFenetre() / 2 + (COTE_IMAGE * nbLigne) / 2)
    {
        coord->y = ((abscisseSouris() - (largeurFenetre() / 2 - (COTE_IMAGE * nbColonne) / 2)) / COTE_IMAGE) + 1;
        coord->x = nbLigne - ((ordonneeSouris() - (hauteurFenetre() / 2 - (COTE_IMAGE * nbLigne) / 2)) / COTE_IMAGE);
        // printf("target : x : %d y : %d \n", coord->x, coord->y);
        return true;
    }
    return false;
}
