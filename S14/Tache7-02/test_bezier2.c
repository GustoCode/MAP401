#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "image.h"
#include "calcul_contours.h"
#include "sequence_point.h"
#include "bezier.h"

int main (int argc, char ** argv)
{
    Image I;
    FILE* f1, *f2 ;
    Ensemble_Contours *ES ;
    Ensemble_Bezier2 *EB ;
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
    double d = atof(argv[4]);
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
    EB = simplification_b2_ensemble(ES,d) ;
    printf("\nImage %s simplification par Bezier 2:\n", argv[1]);
    ecrire_bezier2(I,EB,f2) ;

    return 0 ;
}