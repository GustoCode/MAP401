#ifndef _BEZIER_
#define _BEZIER_

#include "geometrie_2d.h"


typedef struct Bezier2_{
    Point A ;
    Point B ;
    Point C ;
}Bezier2;

typedef struct Bezier3_{
    Point A ;
    Point B ;
    Point C ;
}Bezier3;

/* Calcul du point C(t) pour une valeur de t entre 0 et 1 */
Point Calcul_Point_Bezier(Bezier2 B, double t);





#endif