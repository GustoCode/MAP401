#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "calcul_contours.h"
#include "sequence_point.h"
#include "bezier.h"
#include "calcul_bezier3.h"

int main (int argc, char ** argv)
{
    Image I;
    FILE* f1, *f2 ;
    Ensemble_Contours *ES ;
    Ensemble_Bezier3 *EB ;
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
    EB = simplification_b3_ensemble(ES,d) ;
    printf("\nImage %s simplification par Bezier 3:\n", argv[1]);
    ecrire_bezier3(I,EB,f2) ;
/*     Point A = {0,0} ;
	Point B = {1,0} ;
	Point C = {1,1} ;
	Point D = {1,2} ;
	Point E = {2,2} ;
	Point F = {3,2} ;
	Point G = {3,3} ;
	Point H = {4,3} ;
	Point II = {5,3} ;
	Liste_Point* L = creer_liste_Point_vide();
	L= ajouter_element_liste_Point(L,A);
	L= ajouter_element_liste_Point(L,B);
	L= ajouter_element_liste_Point(L,C);
	L= ajouter_element_liste_Point(L,D);
	L= ajouter_element_liste_Point(L,E);
	L= ajouter_element_liste_Point(L,F);
	L= ajouter_element_liste_Point(L,G);
	L= ajouter_element_liste_Point(L,H);
	L= ajouter_element_liste_Point(L,II);

	fprintf(f2,"%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(f2,"%%%%BoundingBox: 0 0 6 6\n") ;
	fprintf (f2,"\n%0.f %0.f moveto \n",A.x, A.y);
	fprintf (f2,"%0.f %0.f lineto \n",B.x, B.y);
	fprintf (f2,"%0.f %0.f lineto \n",C.x, C.y);
	fprintf (f2,"%0.f %0.f lineto \n",D.x, D.y);
	fprintf (f2,"%0.f %0.f lineto \n",E.x, E.y);
	fprintf (f2,"%0.f %0.f lineto \n",F.x, F.y);
	fprintf (f2,"%0.f %0.f lineto \n",G.x, G.y);
	fprintf (f2,"%0.f %0.f lineto \n",H.x, H.y);
	fprintf (f2,"%0.f %0.f lineto \n",II.x, II.y);
	fprintf (f2,"\n%0.f %0.f moveto \n",A.x, A.y);
	Tableau_Point T = sequence_points_liste_vers_tableau(*L);
	int i;
	Bezier3 B3 =approx_bezier3(T,0,T.taille-1);
	double ti;
	for(i=0; i<=8; i++)
	{
    	ti = (double)i/(8.) ;
    	printf("Le point  i:%d en question : ",i);
    	afficherPoint(T.tab[i]);
    	printf("La distance du point %d de valeur ti : %0.2f, vaut : %0.2f\n",i,ti,distance_point_bezier3(T.tab[i],B3,ti));
        printf("Point de la projections : (%0.2f,%0.2f)\n",Calcul_Point_Bezier3(B3,ti).x,Calcul_Point_Bezier3(B3,ti).y );
    }
	fprintf(f2,"%0.f %0.f %0.f %0.f %0.f %0.f curveto \n",B3.B.x,B3.B.y,B3.C.x,B3.C.y,B3.D.x,B3.D.y);
    fprintf(f2,"\n0.05 setlinewidth\nstroke\nshowpage");
 */
    return 0 ;
}