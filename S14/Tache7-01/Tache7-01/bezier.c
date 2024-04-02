#include "stdio.h"
#include "bezier.h"
#include "geometrie_2d.h"
#include "sequence_point.h"
#include "simplification_contours.h"

Point Calcul_Point_Bezier(Bezier2 B, double t)
{
    Point res ;
    res.x = B.A.x*(1-t)*(1-t)+B.B.x*2*t*(1-t)+B.C.x*t*t ;
    res.y = B.A.y*(1-t)*(1-t)+B.B.y*2*t*(1-t)+B.C.y*t*t ;
    return res ;
}

Bezier3 Conversion_B2_B3(Bezier2 B2)
{
    Bezier3 res ;
    res.A = B2.A ;
    res.D = B2.C ;
    res.B = multScalaire(sommeVect(B2.A,multScalaire(B2.B,2)),1/3);
    /* Les opérations sur les vecteurs fonctionnent sur les points se sont des types synonymes */
    res.C = multScalaire(sommeVect(B2.C,multScalaire(B2.B,2)),1/3);
    return res ;
}

/* à modifier */
Point Somme_Point_Contours(Tableau_Point T, int j1 , int j2)
{
    int i ;
    Point P ;
    Point res ;
    int n = j2-j1;
    for (i=j1+1;i<j1+n;i++)
    {
        P = T.tab[i];
        res = sommeVect(res, P);
    }
    return res ;
}

Bezier2 approx_bezier2 (Tableau_Point T, int j1, int j2)
{
    double alpha, beta ;
    int n = j2-j1 ;
    alpha = 3*((double)n)/((double)(n)*(double)(n)-1) ;
    beta = 1 - (2* (double)n)/2*((double)n + 1) ;
    Bezier2 res ;


    res.A = T.tab[j1] ;
    res.C= T.tab[j2] ;
    if (n==1)
    {res.B=multScalaire(sommeVect(T.tab[j1],T.tab[j2]),0.5);
    return res ;
    }
    else
    {
    res.B = sommeVect(multScalaire(Somme_Point_Contours(T,j1,j2),alpha), multScalaire(sommeVect(T.tab[j1],T.tab[j2]),beta)) ;
    return res ;
    }
}

/* Immplementer maintenant douglas Peukler pour bezier */
/* Liste chainée de courbe de bézier ????? */