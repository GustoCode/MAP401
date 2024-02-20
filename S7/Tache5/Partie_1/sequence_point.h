 
#ifndef _SEQUENCE_POINT_H
#define _SEQUENCE_POINT_H


#include<stdio.h>  
#include<stdlib.h>
#include "geometrie_2d.h" 

typedef struct Cellule_Liste_Point_
{
	Point data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
    struct Liste_Point_ *suiv ;        /* Pointeur vers le contours suivant */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

typedef struct Ensemble_Contours /* Liste chainée de contours */
{
    int nbr ; /* Le nombre de contrours */
    int segment ; /* Nombre de segements */
    Contour *head ; /* pointeur vers le premier contours  */
    
} Ensemble_Contours ;   


/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v);

/* creer une liste vide */
Liste_Point *creer_liste_Point_vide() ;

/* creer un ensemble de contours vide */
Ensemble_Contours *creer_ensemble_contours_vide () ;

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point *ajouter_element_liste_Point(Liste_Point *L, Point e) ;

/* Ajouter à la tete d'un ensemble de contours une liste de point */
Ensemble_Contours ajouter_tete_contours(Ensemble_Contours ES, Liste_Point *L) ;

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L) ;


/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2) ;


/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L) ;

void ecrire_contour(Liste_Point L) ;



#endif