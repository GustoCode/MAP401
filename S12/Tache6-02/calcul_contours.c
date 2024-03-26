#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"
#include "geometrie_2d.h"
#include "calcul_contours.h"
#include "sequence_point.h"
#include "simplification_contours.h"


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
    L=ajouter_element_liste_Point(L,p);
}

Image init_masque(Image M, Image I) 
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
                if (voisin == BLANC ) 
                {
                    res.x = x ;
                    res.y = y ;
                    set_pixel_image(M,x,y,NOIR);
                }
            }
        }
    }
    return M ;
}

Point trouver_pixel_depart (Image I, Image M) 
{
    UINT L = largeur_image(I) ;
    UINT H = hauteur_image(I) ;
    Pixel curr, voisin, masque;
    int x ;
    int y ;
    Point res ;
    for (y=1; y<(H+1); y++)
    {
        for (x=1; x<(L+1); x++)
        {
            curr = get_pixel_image(I,x,y);
            masque = get_pixel_image(M,x,y);
            if (curr == NOIR) 
            {
                voisin = get_pixel_image(I,x,y-1) ; // voisin Pixel Nord
                if (voisin == BLANC && masque == NOIR) /* On vérifie également si le pixel du masque est blanc */
                {
                    res.x = x ;
                    res.y = y ;
                    //printf("Pixel de départ:(%d,%d)\n",x,y) ;
                    return res ;
                }
            }
        }
    }
    res.x = x, res.y = y ;
    return res ;
}

Point recherche_pixel_noir (Image I)
{
    UINT L = largeur_image(I) ;
    UINT H = hauteur_image(I) ;
    Pixel curr ;
    int x ;
    int y ;
    for (y=1; y<(H+1); y++)
    {
        for (x=1; x<(L+1); x++)
        {
            curr = get_pixel_image(I,x,y);
            if (curr == NOIR) return creerPoint(x,y); 
        }
    }
    x--;
    y--;
    return creerPoint(x,y) ;
    /* Si seul le pixel en bas à droite de l'image est noir, son 
    contour ne sera pas detecté */
}

Ensemble_Contours* contours_image (Image I) 
{
    Ensemble_Contours *ES= creer_ensemble_contours_vide();

    Image M = creer_image(largeur_image(I), hauteur_image(I)) ;
    M = init_masque(M,I) ;
    Point rech = recherche_pixel_noir (M) ; //Pixel de recherche

    while (rech.x != largeur_image(M) || rech.y != hauteur_image(M))
    {
        Point positionPixelDepart = trouver_pixel_depart(I,M) ;
        int x= positionPixelDepart.x , y=positionPixelDepart.y ;
        int x0 =x-1 ,y0 = y-1 ;
        //printf("Position de départ:(%d,%d)\n",x0,y0) ;
        Point position ; //Position du Robot
        Orientation o = EST ;
        position.x = x0 ;
        position.y = y0 ;
        int boucle = 1;
        Liste_Point *L = creer_liste_Point_vide() ;
        while (boucle) 
        {
            memoriser_position(position, L) ;
            if(o==EST) set_pixel_image (M,(int)position.x+1,(int)position.y+1,BLANC) ; /* On retire le pixel SE du roboy de l'image masque*/
            position = avancer(position, o) ;
            o = nouvelle_orientation(I, position, o) ;
            if (position.x == x0 && position.y == y0 && o== EST) boucle = 0 ;
        }
        memoriser_position(position, L) ;
        set_pixel_image (M,(int)position.x,(int)position.y,BLANC);
        //printf("Nombre de segments : %d \n",L->taille-1);
        *ES = ajouter_tete_contours(*ES, L) ;
        //printf("Nombre de contours : %d\n\n", ES->nbr) ;
        rech = recherche_pixel_noir(M) ;
        
    }   
    return ES ;
}





void ecrire_contour_fichier(Ensemble_Contours *ES, FILE *f)
{
    int i;
    Contour *C = ES->head ;
    fprintf(f,"%d\n\n",ES->nbr);
    Cellule_Liste_Point *cell = C->first ;
    for (i=0; i<ES->nbr ;i++)
    {
        fprintf(f,"\n%d\n",C->taille-1) ;
        fprintf(f,"%d\n",i);


        while(cell) /* tant que le pointeur de cellule != NULL */
        { 
            fprintf(f,"%.02f %0.2f\n",cell->data.x,cell->data.y) ;
            cell = cell->suiv ;
        }
        C = C->suiv ;
        cell = C->first ;
        
    }
    return ;
}

void ecrire_contour_fichier_EPS(Image I,Ensemble_Contours *ES, FILE *f)
{
    UINT L = largeur_image(I) ;
    UINT H = hauteur_image(I) ;
    /* Ecriture de l'entête du fichier */
    fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %d %d\n",L,H) ;

    Contour *C = ES->head ;
    Cellule_Liste_Point *cell ;
    int i ;

    for (i=0; i<ES->nbr ; i++) /* Parcours des contours */
    {
        cell = C->first ;
        fprintf(f,"\n%0.2f %0.2f moveto \n",cell->data.x, H-cell->data.y );
        cell = cell->suiv ;
        while (cell) /* Tant que cell est non nul */ 
        {
            fprintf(f,"%.02f %0.2f lineto\n",cell->data.x, H-cell->data.y );
            cell = cell->suiv ;
        }
        C = C->suiv ;
        cell = C->first ;
    }
    fprintf(f,"\nfill\n\nshowpage") ; /* pour remplir */
   // fprintf(f,"\nstroke\n\nshowpage\n") ; /* pour faire les contours sans remplir */
    return ;
}

void ecrire_contour(Image I, Ensemble_Contours *ES, FILE *f, bool EPS)
{
    if(EPS) ecrire_contour_fichier_EPS(I,ES,f); 
    else ecrire_contour_fichier(ES,f) ;
    printf("Nombre de contours : %d\nNombre de segment de l'ensemble : %d\n",ES->nbr,ES->segment);
    
}



