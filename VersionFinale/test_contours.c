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
    int eps = atoi(argv[3]); // 0 type  de sortie : .contours et 1 type de sortie: .eps
    I =lire_fichier_image(argv[1]);
    ES = contours_image(I);
    ecrire_contour(I,ES, f, eps) ;
    printf("\n");
    return 1 ;
}