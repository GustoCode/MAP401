#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"
#include "calcul_contours.h"
#include "simplification_contours.h"
#include "sequence_point.h"

int main (int argc, char ** argv)
{
    Image I;
    FILE* f1, *f2 ;
    Ensemble_Contours *ES ;
    f1 = fopen(argv[2], "w");
	if (f1 == (FILE *)NULL)
	{
		printf("ouverture du fichier d'écrirture (argument 2) impossible\n");
        return 1 ;
	}
    f2 = fopen(argv[3], "w");
	if (f2 == (FILE *)NULL)
	{
		printf("ouverture du fichier d'écrirture (argument 3) impossible\n");
        return 1 ;
	}
    /* f3 = fopen(argv[4], "w");
	if (f3 == (FILE *)NULL)
	{
		printf("ouverture du fichier d'écrirture (argument 4) impossible\n");
        return 1 ;
	} */
    I =lire_fichier_image(argv[1]);
    ES = contours_image(I);
    printf("\nImage %s sans simplification :\n\n", argv[1]);
    ecrire_contour(I,ES, f1, true) ;
    Simplification_Segment_Ensemble_Contours(ES, 2);
    printf("\nImage %s simplification par segement:\n", argv[1]);
    ecrire_contour(I,ES, f2, true) ;

    printf("\n");
    return 0 ;
}