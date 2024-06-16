#ifndef __DEMINEUR_H__

#define __DEMINEUR_H__

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600
#define GAP_FACILE 300
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
} cell;

typedef struct coo
{
    int x;
    int y;
} coo;

int verifVoisin(cell tab[LONGUEUR][LARGEUR], int x, int y);
void initTab(cell tab[LONGUEUR][LARGEUR], int difficulty);
void afficheTab(cell tab[LONGUEUR][LARGEUR], int difficulty);
void initNumber(cell tab[LONGUEUR][LARGEUR], int difficulty);
int nbBombe(cell tab[LONGUEUR][LARGEUR]);
int aGagne(cell tab[LONGUEUR][LARGEUR]);
int aPerdu(cell tab[LONGUEUR][LARGEUR], int x, int y);
void flager(cell tab[LONGUEUR][LARGEUR], int x, int y, int *nbFlag);
void revealer(cell tab[LONGUEUR][LARGEUR], int x, int y, int difficulty);
void copieList(coo tab1[LARGEUR * LONGUEUR], coo tab2[LARGEUR * LONGUEUR], int difficulty);
void revealBomb(cell tab[LONGUEUR][LARGEUR], int difficulty);
void explosion(cell tab[LONGUEUR][LARGEUR], int difficulty, int x, int y);
void initBomb(cell tab[LONGUEUR][LARGEUR], int x, int y, int difficulty, int nbBomb);

bool targetMouse(coo *coord, int difficulty);
void gestionEvenement(EvenementGfx evenement);
void initImage(cell plateau[LONGUEUR][LARGEUR], int difficulty);
void quadrillage(cell plateau[LONGUEUR][LARGEUR], int diffculty);
void infoCase(cell tab[LONGUEUR][LARGEUR], int x, int y);

#endif
