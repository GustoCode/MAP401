#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"
#include "geometrie_2d.h"
#include "calcul_contours.h"
#include "sequence_point.h"


Point avancer (Point p, Orientation o)
{
    switch (o)
    {
    case NORD:
        p.y -- ; 
        /* L'axe y est retourné c'est pour cela que l'on diminue de 1 la position y dans ce cas */
        break;
    case OUEST:
        p.x -- ;
        break;
    case SUD:
        p.y ++ ;
        break;
    case EST:
        p.x ++ ;
        break;
    }
    return p ;
}

Orientation tourner90 (Orientation o)
{
    switch (o)
    {
    case NORD:
        o = OUEST ;
        break;
    case OUEST:
        o = SUD ;
        break;
    case SUD:
        o = EST ;
        break;
    case EST:
        o = NORD ;
        break;
    }
    return o ;

}
Orientation tourner270 (Orientation o)
{
    switch (o)
    {
    case NORD:
        o = EST ;
        break;
    case OUEST:
        o = NORD ;
        break;
    case SUD:
        o = OUEST ;
        break;
    case EST:
        o = SUD ;
        break;
    }
    return o ;

}

Pixel getPixelCote(Image I, Point p, Orientation o,Cote c)
{
    switch (o)
    {
    case NORD:
        if(c==DROITE) return get_pixel_image(I,p.x + 1 , p.y ) ;
        else if (c== GAUCHE) return get_pixel_image(I,p.x , p.y ) ;
        break;
    case OUEST:
        if(c==DROITE) return get_pixel_image(I,p.x , p.y ) ;
        else if (c== GAUCHE) return get_pixel_image(I,p.x , p.y+1) ;
        break;
    case SUD:
        if(c==DROITE) return get_pixel_image(I,p.x , p.y+1) ;
        else if (c== GAUCHE) return get_pixel_image(I,p.x+1 , p.y+1) ;
        break;
    case EST:
        if(c==DROITE) return get_pixel_image(I,p.x + 1, p.y+1) ;
        else if (c== GAUCHE) return get_pixel_image(I,p.x+1 , p.y) ;
        break;
    }
}


Orientation nouvelle_orientation(Image I, Point position, Orientation o)
{
    Pixel pG,pD ;

    pG = getPixelCote(I,position,o,GAUCHE); 
    /* if(pG==NOIR) printf("Pixel Gauche Noir\n");
    else printf("Pixel Gauche Blanc\n"); */
    pD = getPixelCote(I,position,o,DROITE);
   /*  if(pD==NOIR) printf("Pixel Droit Noir\n");
    else printf("Pixel Droit Blanc\n");   */
    if (pG == NOIR)
    {

        o = tourner90(o) ;
    }
    else if (pD == BLANC)
    {
        o=tourner270(o) ;

    }
    return o ;
}

void memoriser_position(Point p, Liste_Point *L) 
{
   // printf("(%0.2f,%0.2f)\n",p.x,p.y) ;
    *L=ajouter_element_liste_Point(*L,p);
}


Point trouver_pixel_depart (Image I) 
{
    UINT L = largeur_image(I) ;
    UINT H = hauteur_image(I) ;
    Pixel curr, voisin;
    int x ;
    int y ;
    Point res ;
    for (y=1; y<(H+1); y++)
    {
        for (x=1; x<(L+1); x++)
        {
            curr = get_pixel_image(I,x,y);
            if (curr == NOIR) 
            {
                voisin = get_pixel_image(I,x,y-1) ;
                if (voisin == BLANC) 
                {
                    res.x = x ;
                    res.y = y ;
                    printf("Pixel de départ:(%d,%d)\n",x,y) ;
                    return res ;
                }
            }
        }
    }
    printf("Image vide, pixel de départ par défaut (0,0)");
    x=0,y=0 ;
    res.x = x, res.y = y ;
    return res ;
}

Contour contours_image (Image I ) 
{
    Point positionPixelDepart = trouver_pixel_depart(I) ;
    int x= positionPixelDepart.x , y=positionPixelDepart.y ;
    int x0 =x-1 ,y0 = y-1 ;
    printf("Position de départ:(%d,%d)\n",x0,y0) ;
    Point position ;
    position.x = x0 ;
    position.y = y0 ;
    Orientation o = EST ;
    int boucle = 1;
    Liste_Point L = creer_liste_Point_vide() ;
    while (boucle)
    {
        memoriser_position(position, &L) ;
        position = avancer(position, o) ;
        o = nouvelle_orientation(I, position, o) ;
        if (position.x == x0 && position.y == y0 && o== EST) boucle = 0 ;
    }
    memoriser_position(position, &L) ;
    printf("Nombre de segments : %d \n",L.taille-1);

    return L ;
}

void ecrire_contour_fichier(Contour C, FILE *f)
{
    fprintf(f,"1\n\n");
    fprintf(f,"%d\n",C.taille-1) ;

    while(C.taille != 0 )
    { 
        fprintf(f,"%.02f %0.2f\n",(C.first)->data.x,(C.first)->data.y) ;
        C = supprimer_premier_element_liste_Point(C) ; 
    }
    return ;
}

void ecrire_contour_fichier_EPS(Image I,Contour C, FILE *f)
{
    UINT L = largeur_image(I) ;
    UINT H = hauteur_image(I) ;
    /* Ecriture de l'entête du fichier */
    fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %d %d\n\n", L, H) ;

    //Premier contour
    fprintf(f,"%.02f %0.2f moveto ",(C.first)->data.x,H-(C.first)->data.y) ; /* Déplacement vers le premier point */
    C = supprimer_premier_element_liste_Point(C) ;
    while(C.taille != 0 )
    { 
        /* On ajuste la coordonée de l'axe vertical puisque l'axe est dans l'autre sens*/
        fprintf(f,"%.02f %0.2f lineto\n",(C.first)->data.x,H-(C.first)->data.y) ; 
        C = supprimer_premier_element_liste_Point(C) ; 
    }
    fprintf(f,"\nstroke\n\nshowpage") ;
    return ;
}
