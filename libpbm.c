#include "libpbm.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/*
 ___       ___  ________  ________  ________  _____ ______
|\  \     |\  \|\   __  \|\   __  \|\   __  \|\   _ \  _   \
\ \  \    \ \  \ \  \|\ /\ \  \|\  \ \  \|\ /\ \  \\\__\ \  \
 \ \  \    \ \  \ \   __  \ \   ____\ \   __  \ \  \\|__| \  \
  \ \  \____\ \  \ \  \|\  \ \  \___|\ \  \|\  \ \  \    \ \  \
   \ \_______\ \__\ \_______\ \__\    \ \_______\ \__\    \ \__\
    \|_______|\|__|\|_______|\|__|     \|_______|\|__|     \|__|
*/

/* Variable globale pour la librairie. */
char image[largeur][hauteur]; /* Tableau de char contenant l'image */

/** point description *******************************************/
/* point(x,y) , place un point sur l'image a la coordonnée x,y 	*/
/* retourne 0 si ok 1 sinon 									*/
/****************************************************************/
int Point(int x,int y)
{
/* on teste si nous sommes bien dans le tableau sinon on retourne 1 */
if ((x<0) || (x>=largeur))
	{
	fprintf(stderr,"On sort de l'image x= %d !\n",x);
	return EXIT_FAILURE;
	}
if ((y<0) || (y>=hauteur))
	{
	fprintf(stderr,"On sort de l'image y= %d !\n",y);
	return EXIT_FAILURE;
	}
image[x][y]='1';
return EXIT_SUCCESS;
}


/***************************************/
/* rempli l'image de points blanc '0'  */
/***************************************/
void EffaceImage(void)
{
int x , y;

for (y=0; y<hauteur ; y++) 		/* pour toutes les lignes */
	for (x=0; x<largeur ; x++) 	/* pour chaque colonnes */
		image[x][y]='0';
return;
}

/****************************************/
/* sauve l'image au format pbm			*/
/* crée une image.pbm					*/
/****************************************/
void SauveImage(void)
{
int fd,x,y;
char chaine[100];

sprintf(chaine,"%d %d\n",largeur,hauteur);
fd = open ( "image.pbm"	,O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

if (fd==-1)
	{
	fprintf(stderr,"Pas possible d'ecrire sur le disque\n");
	exit(EXIT_FAILURE);
	}
write (fd, "P1\n",3);
write (fd, chaine,strlen(chaine));
write (fd, "#create to libpbm Caroline DORIAN\n",35);
for (y=0; y<hauteur ; y++)
	for (x=0; x<largeur ; x++)
		{
		write (fd,&image[x][y],1);
		write (fd,"\n",1);
		}
close(fd);
return;
}
/*
 * Ligne Horizontale selon x
 */
void LigneHorizontale(int x,int y,int nbpixel)
{
int deplacement;
for(deplacement=0;deplacement<nbpixel;deplacement++)
Point(x+deplacement,y);
return;
}

/*
 * Ligne Verticale selon y
 */
void LigneVerticale(int x,int y,int nbpixel)
{
int deplacement;
for(deplacement=0;deplacement<nbpixel;deplacement++)
Point(x,y+deplacement);
return;
}

/*
 * ligne selon bresenham
 * https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm
 */

void Ligne(int x0, int y0, int x1, int y1) 
{
int dx,sx,dy,sy,err,e2;

dx = abs(x1 - x0);
if(x0<x1) 	sx=1;
	else 	sx=-1;

dy = abs(y1 - y0);
if(y0<y1) 	sy=1;
	else 	sy=-1;
	
	
if(dx>dy) 	err= dx/2;
else 		err= ((-dy)/2);

do
{
Point(x0, y0);
e2 =err;
if (e2 > -dx) {err = err-dy; x0 = x0+sx; }
if (e2 < dy) {err = err+dx; y0 = y0+sy;}
}while(!(x0 == x1 && y0 == y1));
return;
}


/*
 * Permet de faire un repère orthogonal
 */
void Axes(void)
{
LigneHorizontale(0,hauteur/2,largeur);
LigneVerticale(largeur/2,0,hauteur);
return;
}

/**************************************
 * Permet de nous placer dans un
 * repere orthonormé
 * ou le 0,0 est bien au centre
 * le Ymax =+1	Xmax = pi
 * le Ymin =-1	Xmin = -pi
 * ************************************/

void    Repere_o(float x,float y)
{
#define cx (x*(largeur/2))/M_PI
#define cy (y*(hauteur/2))/1

	int ix,iy;
		ix=(int)(largeur/2)+cx;
		iy=(int)(hauteur/2)+cy*(-1);
		Point (ix,iy);
	return;
}

/*******************************************
 * on va parcourir de -pi à +pi en x pour
 * obtenir le sinus
 * ****************************************/
void    Sinus(void)
{
	float axex,axey;
	for (axex=-3.14 ; axex <= 3.14 ; axex+=0.002)
	{
		axey= sin(axex);
		Repere_o(axex,axey);
	}
return;
}
