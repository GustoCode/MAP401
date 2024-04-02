#ifndef _BEZIER_
#define _BEZIER_

#include "geometrie_2d.h"
#include "simplification_contours.h"
#include "sequence_point.h"


typedef struct Bezier2_{
    Point A ;
    Point B ;
    Point C ;
}Bezier2;

typedef struct Bezier3_{
    Point A ;
    Point B ;
    Point C ;
    Point D ;
}Bezier3;

/* Calcul du point C(t) pour une valeur de t entre 0 et 1 */
Point Calcul_Point_Bezier(Bezier2 B, double t);

/* Conversion d'une courbe de bezier de degré 2 en courbe de de bezier de degré 3 */
Bezier3 Conversion_B2_B3(Bezier2 B2);


Point Somme_Point_Contours (Tableau_Point T, int i, int j) ;

Bezier2 approx_bezier2 (Tableau_Point T, int i, int j) ;




#endif