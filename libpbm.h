#ifndef _libpbm_

#define _libpbm_

#include <unistd.h>
#define largeur 800
#define hauteur 600
int 	Point(int x,int y);
void 	EffaceImage(void);
void 	SauveImage(void);
void 	LigneHorizontale(int x,int y,int nbpixel);
void 	LigneVerticale(int x,int y,int nbpixel);
void 	Ligne(int x0, int y0, int x1, int y1);
void 	Axes(void);
void    Repere_o(float x,float y);
void    Sinus(void);
#endif
