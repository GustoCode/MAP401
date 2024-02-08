#include <stdio.h>
#include <math.h>
#include "geometrie_2d.h"


Vecteur creerVecteur(double x, double y)
{
    Vecteur u ;
    u.x= x;
    u.y= y;
    return u ;
}

Point creerPoint(double x, double y)
{
    Point a ;
    a.x= x;
    a.y= y;
    return a ;
}

double xPoint(Point a)
{
    return a.x ;
}

double yPoint(Point a)
{
    return a.y ;
}

double xVecteur(Vecteur u)
{
    return u.x ;
}

double yVecteur(Vecteur u)
{
    return u.y ;
}

Vecteur sommeVect(Vecteur u1, Vecteur u2)
{
    double x1,y1,x2,y2;
    x1 = xVecteur(u1);
    y1= yVecteur(u1);
    x2= xVecteur(u2);
    y2= yVecteur(u2);

    Vecteur res = creerVecteur(x1+x2,y1+y2);
    return res ;

}

Vecteur differenceVect(Vecteur u1, Vecteur u2)
{
    double x1,y1,x2,y2;
    x1 = xVecteur(u1);
    y1= yVecteur(u1);
    x2= xVecteur(u2);
    y2= yVecteur(u2);

    Vecteur res = creerVecteur(x1-x2,y1-y2);
    return res ;

}

Point sommePoints(Point a, Point b) 
{
    return sommeVect(a, b);
}

Vecteur vectPoints(Point a, Point b) 
{
    return differenceVect(b,a) ;
}

double norme(Vecteur u)
{
    double x = xVecteur(u);
    double y = yVecteur(u);
    return sqrt(x*x+y*y);
}

double produitScalaire(Vecteur u1, Vecteur u2)
{
    return u1.x*u2.x + u1.y*u2.y; 
}

double distance(Point a, Point b)
{
    return norme(vectPoints(a, b));
}

Vecteur multScalaire(Vecteur u, double lambda)
{
    Vecteur v;
    v = creerVecteur(u.x*lambda, u.y*lambda);
    return v;
}

void afficherPoint (Point a)
{
    printf("(%0.2f,%0.2f)\n",xPoint(a),yPoint(a)) ;
    return ;
}