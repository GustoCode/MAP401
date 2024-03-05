#include <stdio.h>
#include "geometrie_2d.h"
#include "sequence_point.h"
#include "calcul_contours.h"
#include "simplification_contours.h"


void simplification_douglas_peucker(Tableau_Point C, int j1, int j2, double d)
{
    Segment S = creerSegment(C.tab[j1],C.tab[j2]);
    double dmax = 0 ;
    int k = j1 ;
    int j ;
    double dj;
    for (j=j+1 ; j<=j2 ;j++)
    {
        dj = distancePointSegment(C.tab[j],S);
        if (dmax<dj)
        {
            dmax= dj ;
            k=j;
        }
    }
    if (dmax<=d) ;// affecter à L un tableau contenant le segment S. 
    else
    {
    
    }
}