#ifndef __DEMINEUR_H__

#define __DEMINEUR_H__

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600
#define GAP_FACILE 300
#define COTE_IMAGE 32

#define LONGUEUR 17
#define LARGEUR 12

typedef struct cell
{
	int number;
	int revealed;
	int flag;
	int bomb;
    DonneesImageRGB *image;
    DonneesImageRGB *imageDepart;
}cell;



typedef struct coo
{
    int x;
    int y;
}coo;

int verifVoisin(cell tab[LONGUEUR][LARGEUR], int x, int y);
void initTab(cell tab[LONGUEUR][LARGEUR], int  x, int  y, int difficult);
void afficheTab(cell tab[LONGUEUR][LARGEUR], int  x, int  y);
void initNumber(cell tab[LONGUEUR][LARGEUR]);
int nbBombe(cell tab[LONGUEUR][LARGEUR]);
int aGagne(cell tab[LONGUEUR][LARGEUR]);
int aPerdu(cell tab[LONGUEUR][LARGEUR], int x, int y);
void flager(cell tab[LONGUEUR][LARGEUR], int x, int y);


bool targetMouse(coo * coord, int nbColonne, int nbLigne);
void cercle(float centreX, float centreY, float rayon);
void gestionEvenement(EvenementGfx evenement);
void initImage(cell plateau[LONGUEUR][LARGEUR], int difficulty);
void quadrillage(cell plateau[LONGUEUR][LARGEUR], int diffculty);

#endif
