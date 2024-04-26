#ifndef _BEZIER_
#define _BEZIER_

#include "geometrie_2d.h"
#include "simplification_contours.h"
#include "sequence_point.h"


typedef struct Bezier2_{
    Point A ;
    Point B ;
    Point C ;
}Bezier2;

typedef struct Bezier3_{
    Point A ;
    Point B ;
    Point C ;
    Point D ;
}Bezier3;

typedef struct Cellule_Liste_Bezier2_
{
	Bezier2 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Bezier2_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Bezier2;

typedef struct Liste_Bezier2_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Bezier2 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Bezier2 *last;  /* pointeur sur le dernier element de la liste */
    struct Liste_Bezier2_ *suiv ; 
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Bezier2;

typedef struct Ensemble_Bezier2_ /* Liste chainée de contours */
{
    int nbr ; /* Le nombre de contrours */
    int courbe ; /* Nombre de courbes */
    Liste_Bezier2 *head ; /* pointeur vers le premier contours  */
    
} Ensemble_Bezier2 ; 

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Bezier2 *creer_element_liste_bezier2(Bezier2 v);

/* creer une liste vide */
Liste_Bezier2 *creer_liste_bezier2_vide() ;

/* creer un ensemble de contours vide */
Ensemble_Bezier2 *creer_ensemble_bezier2_vide () ;

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Bezier2 *ajouter_element_liste_Bezier2(Liste_Bezier2 *L, Bezier2 b) ;

/* Ajouter à la tete d'un ensemble de contours une liste de point */
Ensemble_Bezier2 *ajouter_tete_bezier2(Ensemble_Bezier2 *EB, Liste_Bezier2 *L);

Liste_Bezier2 *concatener_liste_bezier2(Liste_Bezier2 *L1, Liste_Bezier2 *L2) ;

/* Calcul du point C(t) pour une valeur de t entre 0 et 1 */
Point Calcul_Point_Bezier(Bezier2 B, double t);

/* Conversion d'une courbe de bezier de degré 2 en courbe de de bezier de degré 3 */
Bezier3 Conversion_B2_B3(Bezier2 B2);


Point Somme_Point_Contours (Tableau_Point T, int i, int j) ;

Bezier2 approx_bezier2 (Tableau_Point T, int i, int j) ;

double distance_point_bezier2(Point P, Bezier2 B, double ti);

Liste_Bezier2 *simplification_douglas_peucker_b2(Tableau_Point T, int j1, int j2, double d) ;

/* Simplification par courbe de bezier sur l'ensemble des contours */
Ensemble_Bezier2 *simplification_b2_ensemble (Ensemble_Contours *EC, double d) ;

void ecrire_bezier2_fichier_EPS(Image I,Ensemble_Bezier2 *EB, FILE *f) ;




#endif