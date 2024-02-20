#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"
#include "calcul_contours.h"


int main (int argc, char ** argv)
{
    Image I;
    FILE *f ;
    Ensemble_Contours *ES ;
    f = fopen(argv[2], "w");
	if (f == (FILE *)NULL)
	{
		printf("ouverture du fichier d'écrirture (argument 2) impossible\n");
        return 0 ;
	}
    I =lire_fichier_image(argv[1]);
    ES = contours_image(I);
    printf ("Premier élément de la liste ajoutée : (%0.f,%0.f)\n", ES->head->first->data.x,ES->head->first->data.y );
    ecrire_contour_fichier(ES, f) ;
    printf("\n");
    return 1 ;
}