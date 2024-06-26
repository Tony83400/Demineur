#include <stdlib.h>        // Pour pouvoir utiliser exit()
#include <stdio.h>         // Pour pouvoir utiliser printf()
#include <math.h>          // Pour pouvoir utiliser sin() et cos()
#include "GFXlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "Fonction.h"

bool targetMouse(coo *coord, int difficulty, int tailleImage)
{
    int nbColonne = 10 + difficulty * 5, nbLigne = 15 + difficulty * 5;

    if (abscisseSouris() > largeurFenetre() / 2 - (tailleImage * nbColonne) / 2 && abscisseSouris() < largeurFenetre() / 2 + (tailleImage * nbColonne) / 2 && ordonneeSouris() > hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2 && ordonneeSouris() < hauteurFenetre() / 2 + (tailleImage * nbLigne) / 2)
    {
        coord->y = ((abscisseSouris() - (largeurFenetre() / 2 - (tailleImage * nbColonne) / 2)) / tailleImage) + 1;
        coord->x = ((ordonneeSouris() - (hauteurFenetre() / 2 - (tailleImage * nbLigne) / 2)) / tailleImage) + 1;
        return true;
    }
    return false;
}
bool cliqueButton(int x1Button, int y1Button, int x2Button, int y2Button)
{
    if (abscisseSouris() > x1Button && abscisseSouris() < x2Button && ordonneeSouris() > y1Button && ordonneeSouris() < y2Button)
    {
        return true;
    }
    return false;
}
