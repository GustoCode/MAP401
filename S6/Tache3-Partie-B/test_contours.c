#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"
#include "calcul_contours.h"


int main (int argc, char ** argv)
{
    Image I;
    FILE *f ;
    Contour C ;
     f = fopen(argv[2], "w");
	if (f == (FILE *)NULL)
	{
		printf("ouverture du fichier d'écrirture (argument 2) impossible\n");
        return 0 ;
	}
    I =lire_fichier_image(argv[1]);
    C = contours_image(I);
    ecrire_contour_fichier(C, f) ;
    printf("\n");
    return 1 ;
}