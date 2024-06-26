#ifndef __DEMINEUR_H__

#define __DEMINEUR_H__

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600
#define COTE_IMAGE 32

#define LONGUEUR 27
#define LARGEUR 22

typedef struct cell
{
    int number;
    int revealed;
    int flag;
    int bomb;
    DonneesImageRGB *image;
    DonneesImageRGB *imageDepart;
    bool explosion;
} cell;

typedef struct coo
{
    int x;
    int y;
} coo;

void afficheTab(cell tab[LONGUEUR][LARGEUR], int difficulty);

int verifVoisin(cell tab[LONGUEUR][LARGEUR], int x, int y);
void initTab(cell tab[LONGUEUR][LARGEUR], int difficulty);
void initNumber(cell tab[LONGUEUR][LARGEUR], int difficulty);
bool verifAGagne(cell tab[LONGUEUR][LARGEUR], int difficulty);
void flager(cell tab[LONGUEUR][LARGEUR], int x, int y, int *nbFlag, int tailleImage);
void revealer(cell tab[LONGUEUR][LARGEUR], int x, int y, int difficulty);
void copieList(coo tab1[LARGEUR * LONGUEUR], coo tab2[LARGEUR * LONGUEUR], int difficulty);
void revealBomb(cell tab[LONGUEUR][LARGEUR], int difficulty);
void explosion(cell tab[LONGUEUR][LARGEUR], int difficulty, int x, int y);
void initBomb(cell tab[LONGUEUR][LARGEUR], int x, int y, int difficulty, int nbBomb);
void timer(int time0, char *chaine, bool aPerdu);
void actualiseChaineDrapeau(char chaineDrapeau[50], int nbDrapeau);
void trouveFlag(cell tab[LONGUEUR][LARGEUR], int difficulty, int *ptFlag);


bool targetMouse(coo *coord, int difficulty, int tailleImage);
bool cliqueButton(int x1Button, int y1Button, int x2Button, int y2Button);

void gestionEvenement(EvenementGfx evenement);
void initImage(cell plateau[LONGUEUR][LARGEUR], int difficulty, int tailleImage);
void quadrillage(cell plateau[LONGUEUR][LARGEUR], int difficulty, int tailleImage);

#endif
