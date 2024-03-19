#ifndef _SIMPLIFICATION_CONTOURS_H
#define _SIMPLIFICATION_CONTOURS_H

#include <stdio.h>
#include "geometrie_2d.h"
#include "calcul_contours.h"
#include "sequence_point.h"



typedef struct {
    Cellule_Liste_Point **pointeurs;
    int taille;
} Tableau_Pointeurs_Liste_Point;


typedef struct Cellule_Liste_Segment_
{
	Segment data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Segment_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Segment;

typedef struct Liste_Segment_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Segment *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Segment *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Segment;

Liste_Segment *creer_liste_Segment_vide() ;

Cellule_Liste_Segment *creer_element_liste_segment(Segment S) ;

Liste_Segment *ajouter_element_liste_Segment(Liste_Segment *LS, Segment S) ;

Liste_Segment *concatener_liste_Segment(Liste_Segment *L1, Liste_Segment *L2) ;



void simplification_douglas_peucker(Liste_Point *L, double d) ;

/* 
Simplification du contour C compris entres les indices j1 et j2
bon pas maintenant ...

 */
Liste_Segment *simplification_douglas_peucker_rec(Liste_Point *L, int j1, int j2, double d,  Tableau_Pointeurs_Liste_Point TPLP);


void Conversion_Liste_Segment_Liste_Point(Liste_Segment *LS, Liste_Point *LP) ;



#endif
