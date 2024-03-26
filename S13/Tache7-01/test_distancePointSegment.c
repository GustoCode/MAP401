#include <stdio.h>
#include "geometrie_2d.h"

int main() 
{
    printf("Point P \nVeuillez entrer la valeur x : ");
    double x, y ;
    scanf ("%lf", &x) ;
    printf ("Veuillez entrer la valeur y : ");
    scanf ("%lf", &y) ;
    Point P = creerPoint(x,y);
    printf("Segment S :\nPoint A:\nVeulliez entrer la veleur x: ");
    scanf ("%lf", &x) ;
    printf ("Veuillez entrer la valeur y : ");
    scanf ("%lf", &y) ;
    Point A = creerPoint(x,y);
    printf("Point B\nVeuillez entrer la valeur x: ");
    scanf ("%lf", &x) ;
    printf ("Veuillez entrer la valeur y : ");
    scanf ("%lf", &y) ;
    Point B = creerPoint(x,y);
    Segment S = creerSegment(A,B) ;
    printf("\nCalcul du la distance dP du point P au segment S\n") ;
    double dP = distancePointSegment(P,S) ;
    printf("dP = %0.2f\n", dP) ;

    return 0;
}