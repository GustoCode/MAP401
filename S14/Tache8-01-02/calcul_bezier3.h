#ifndef _CALCUL_BEZIER3_
#define _CALCUL_BEZIER3_

#include "geometrie_2d.h"
#include "simplification_contours.h"
#include "sequence_point.h"
#include "bezier.h"


/* Le type bézier 3 est implémenté dans bezier.h */

typedef struct Cellule_Liste_Bezier3_
{
	Bezier3 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Bezier3_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Bezier3;

typedef struct Liste_Bezier3_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Bezier3 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Bezier3 *last;  /* pointeur sur le dernier element de la liste */
    struct Liste_Bezier3_ *suiv ; 
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Bezier3;

typedef struct Ensemble_Bezier3_ /* Liste chainée de contours */
{
    int nbr ; /* Le nombre de contrours */
    int courbe ; /* Nombre de courbes */
    Liste_Bezier3 *head ; /* pointeur vers le premier contours  */
    
} Ensemble_Bezier3 ; 

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Bezier3 *creer_element_liste_Bezier3(Bezier3 v);

/* creer une liste vide */
Liste_Bezier3 *creer_liste_Bezier3_vide() ;

/* creer un ensemble de contours vide */
Ensemble_Bezier3 *creer_ensemble_Bezier3_vide () ;

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Bezier3 *ajouter_element_liste_Bezier3(Liste_Bezier3 *L, Bezier3 b) ;

/* Ajouter à la tete d'un ensemble de contours une liste de point */
Ensemble_Bezier3 *ajouter_tete_Bezier3(Ensemble_Bezier3 *EB, Liste_Bezier3 *L);

Liste_Bezier3 *concatener_liste_Bezier3(Liste_Bezier3 *L1, Liste_Bezier3 *L2) ;

Point Calcul_Point_Bezier3(Bezier3 B, double t);


double distance_point_bezier3(Point P, Bezier3 B, double ti) ;

double gamma (int k, int n) ;

/* Somme des Poiunt de j+1 à j+n en appliquant gamma
-ordre = true on effectue gamma selon i
-sinon n-i cf poly */
Point Somme_Point_gamma(Tableau_Point T, int j1 , int j2, bool ordre );


Bezier3 approx_bezier3 (Tableau_Point T, int j1, int j2);

Liste_Bezier3 *simplification_douglas_peucker_b3(Tableau_Point T, int j1, int j2, double d);

Ensemble_Bezier3* simplification_b3_ensemble(Ensemble_Contours *EC, double d);

void ecrire_bezier3_fichier_EPS(Image I,Ensemble_Bezier3 *EB, FILE *f);


void ecrire_bezier3(Image I, Ensemble_Bezier3 *EB, FILE *f) ;


#endif