/************************************************/
/** Image avec points de 800 x 600 		       **/
/** V1.Bogt2024 LtDorian 			           **/
/** 05/03/2024 					               **/
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "libpbm.h"




/************************* principale *****************************/
int main()
{
EffaceImage();
Axes();
/* Ligne(10,10,100,120); */
Sinus();
SauveImage();
return EXIT_SUCCESS;
}
