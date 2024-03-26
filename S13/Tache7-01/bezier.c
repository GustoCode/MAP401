#include "stdio.h"
#include "bezier.h"
#include "geometrie_2d.h"


Point Calcul_Point_Bezier(Bezier2 B, double t)
{
    Point res ;
    res.x = B.A.x*(1-t)*(1-t)+B.B.x*2*t*(1-t)+B.C.x*t*t ;
    res.y = B.A.y*(1-t)*(1-t)+B.B.y*2*t*(1-t)+B.C.y*t*t ;
    return res ;
}

