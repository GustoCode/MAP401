#ifndef GEOMETRIE_2D
#define GEOMETRIE_2D

typedef struct Point_2D {
    double x;
    double y;
} Point;

typedef Point Vecteur;

/*
typedef struct Vecteur_2D {
    double x;
    double y;
} Vecteur;
*/

/* Renvoie un vecteur de coordonnées x y*/
Vecteur creerVecteur(double x, double y);

/* Renvoie un point de coordonnées x y*/
Point creerPoint(double x, double y);

double xPoint(Point a);

double yPoint(Point a);

double xVecteur(Vecteur u);

double yVecteur(Vecteur u);

/*Somme de deux vecteurs */
Vecteur sommeVect(Vecteur u1, Vecteur u2);

/*Difference de deux vecteurs u1-u2 */
Vecteur differenceVect(Vecteur u1, Vecteur u2);

/* Renvoie un vecteur allant du point a au point b*/
Vecteur vectPoints(Point a, Point b);

/* Renvoie la norme de u */
double norme(Vecteur u);

/* Renvoie le produit scalaire de u1 par u2 */
double produitScalaire(Vecteur u1, Vecteur u2);

/* Renvoie la distance entre a et b */
double distance(Point a, Point b);

/* Multiplie un vecteur par un reel lambda*/
Vecteur multScalaire(Vecteur u, double lambda);


#endif /* GEOMETRIE_2D */