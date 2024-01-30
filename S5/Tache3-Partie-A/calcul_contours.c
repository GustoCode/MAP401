#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"
#include "geometrie_2d.h"
#include "calcul_contours.h"


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
        if(c==DROITE) return get_pixel_image(I,p.x + 1 , p.y - 1) ;
        else if (c== GAUCHE) return get_pixel_image(I,p.x , p.y - 1) ;
        break;
    case OUEST:
        if(c==DROITE) return get_pixel_image(I,p.x , p.y - 1) ;
        else if (c== GAUCHE) return get_pixel_image(I,p.x , p.y) ;
        break;
    case SUD:
        if(c==DROITE) return get_pixel_image(I,p.x , p.y) ;
        else if (c== GAUCHE) return get_pixel_image(I,p.x+1 , p.y) ;
        break;
    case EST:
        if(c==DROITE) return get_pixel_image(I,p.x + 1, p.y) ;
        else if (c== GAUCHE) return get_pixel_image(I,p.x+1 , p.y - 1) ;
        break;
    }
}


Orientation nouvelle_orientation(Image I, Point position, Orientation o)
{
    Pixel pG,pD ;

    pG = getPixelCote(I,position,o,GAUCHE); 
    pG = getPixelCote(I,position,o,DROITE);  
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

void memoriser_position(Point p) 
{
    printf("(%0.2f,%0.2f)\n",p.x,p.y) ;
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
                voisin = get_pixel_image(I,x+1,y);
                if (voisin == BLANC) ;
                {
                    res.x = x ;
                    res.y = y ;
                    printf("Pixel de départ:(%d,%d)\n",x,y) ;
                    return res ;
                }
            }
        }
    }
}

void contours_image (Image I ) 
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
    while (boucle)
    {
        memoriser_position(position) ;
        position = avancer(position, o) ;
        o = nouvelle_orientation(I, position, o) ;
        if (position.x == x0 && position.y == y0 && o== EST) boucle = 0 ;
    }
    memoriser_position(position);
    //return position ;
}


