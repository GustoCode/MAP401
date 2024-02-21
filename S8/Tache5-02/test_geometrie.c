#include <stdio.h>
#include "geometrie_2d.h"

int main() 
{
    double x1=3.0; 
    double y1=4.0;

    double x2=1.0;
    double y2= 5.0;

    Point a = creerPoint(x1, y1);
    Point b = creerPoint(x2, y2);

    Vecteur u1 = creerVecteur(x1,y1);
    printf("La norme du vecteur (%0.2f,%0.2f) vaut %0.2f\n",x1,y1,norme(u1));

    Vecteur u2 = vectPoints(a, b);
    printf("Le vecteur allant de a=(%0.2f,%0.2f) à b=(%.2f,%.2f) est le vecteur u_2=(%.2f, %.2f)\n",x1, y1, x2, y2, u2.x, u2.y);    

    double d = distance(a, b);
    printf("La distance entre a et b est %.2f\n", d);
    d = norme(u2);
    printf("La norme de u_2 est %.2f (Normalement la meme que la distance entre a et b)\n", d);

    Vecteur u3 = sommeVect(u1,u2);

    printf("La somme de u1=(%0.2f,%0.2f) à u2=(%0.2f,%0.2f) vaut (%0.2f,%0.2f)\n",u1.x,u1.y,u2.x,u2.y,u3.x,u3.y) ;
    u3 = differenceVect(u1,u2);
    printf("et la difference vaut (%0.2f,%0.2f)\n ", u3.x,u3.y);

    Vecteur u4 = multScalaire(u2, 2.0);
    printf("u2*2 = (%.2f, %.2f)\n", u4.x, u4.y); 

    double prod = produitScalaire(u1, u3);
    printf("Le produit scalaire de u1= (%0.2f,%0.2f) et u3= (%0.2f,%0.2f) vaut %0.2f\n",u1.x, u1.y, u3.x, u3.y, prod);
    
    return 0;
}