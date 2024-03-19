#include<stdio.h>  
#include<stdlib.h>
#include "sequence_point.h"
#include "geometrie_2d.h" 



/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}
/* creer une liste vide */
Liste_Point *creer_liste_Point_vide()
{
    Liste_Point *L = malloc(sizeof(Liste_Point)) ;
    L->taille = 0 ;
    L->first =NULL ;
    L->last = NULL ;
    L->suiv = NULL ;
	return L;
}

Ensemble_Contours* creer_ensemble_contours_vide ()
{
    Ensemble_Contours *EC;
    EC = malloc (sizeof(Ensemble_Contours));
    Liste_Point *tete = creer_liste_Point_vide() ;
    EC->nbr = 0 ;
    EC->segment = 0;
    EC->head = tete ;
    return EC ;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point *ajouter_element_liste_Point(Liste_Point *L, Point e)
{
	Cellule_Liste_Point *el;
	
	el = creer_element_liste_Point(e);
	if (L->taille == 0)
	{
		/* premier element de la liste */
		L->first = L->last = el;
	}
	else
	{
		L->last->suiv = el;
		L->last = el;
	}
	L->taille++;
	return L;
}

Ensemble_Contours ajouter_tete_contours(Ensemble_Contours ES, Liste_Point *L)//ne pas ajouter une liste vide
{
    L->suiv = ES.head ;
    ES.head = L ;
    ES.nbr ++ ;
    ES.segment += L->taille -1 ; 
    return ES ;
}

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point *supprimer_liste_Point(Liste_Point *L)
{
	Cellule_Liste_Point *el=L->first;
	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L->first = L->last = NULL; L->taille = 0;
    L->suiv = NULL ;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee
L'élément suivant concaténation des deux listes conservé est celui de L1  */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L)
{
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_Point *e1=L.first;  /* pointeur vers le premier element  */ 
	Cellule_Liste_Point *e2=e1->suiv; /* pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}


/* plus nécessaire à supprimer plus tard */
void vider_liste_remplir_par_tableau(Liste_Point *L, Tableau_Point T) 
{
 	/* On vide la liste de ses éléments. */
    Cellule_Liste_Point *el=L->first;	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L->first = L->last = NULL; L->taille = 0;
    int i ;
    /* On la rempli des élements du tableau*/
    for (i=0; i<T.taille; i++) ajouter_element_liste_Point(L,T.tab[i]);
    

}

