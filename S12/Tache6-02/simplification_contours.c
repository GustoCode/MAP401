#include <stdio.h>
#include "geometrie_2d.h"
#include "sequence_point.h"
#include "calcul_contours.h"
#include "simplification_contours.h"



Liste_Segment *creer_liste_Segment_vide()
{
    Liste_Segment *LS = malloc(sizeof(Liste_Point)) ;
    LS->taille = 0 ;
    LS->first =NULL ;
    LS->last = NULL ;
	return LS;
}

Cellule_Liste_Segment *creer_element_liste_segment(Segment S)
{
	Cellule_Liste_Segment *el;
	el = (Cellule_Liste_Segment *)malloc(sizeof(Cellule_Liste_Segment));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = S;
	el->suiv = NULL;
	return el;
}

Liste_Segment *ajouter_element_liste_Segment(Liste_Segment *LS, Segment S)
{
	Cellule_Liste_Segment *el;
	
	el = creer_element_liste_segment(S);
	if (LS->taille == 0)
	{
		/* premier element de la liste */
		LS->first = LS->last = el;
	}
	else
	{
		LS->last->suiv = el;
		LS->last = el;
	}
	LS->taille++;
	return LS;
}


/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee
L'élément suivant concaténation des deux listes conservé est celui de L1  */
Liste_Segment *concatener_liste_Segment(Liste_Segment *L1, Liste_Segment *L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1->taille == 0) return L2; 
	if (L2->taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1->last->suiv = L2->first; /* lien entre L1.last et L2.first */
	L1->last = L2->last;        /* le dernier element de L1 est celui de L2 */
	L1->taille += L2->taille;   /* nouvelle taille pour L1 */
	return L1;
}

void simplification_douglas_peucker(Liste_Point *L, double d)
{
    Tableau_Pointeurs_Liste_Point TPLP ;
    TPLP.taille = L->taille ;
    TPLP.pointeurs = (Cellule_Liste_Point **)malloc(TPLP.taille * sizeof(Cellule_Liste_Point *));
    //Cellule_Liste_Point **pointeurs = TPLP.pointeurs ;
    TPLP.pointeurs[0]=L->first ;
    TPLP.pointeurs[L->taille-1] = L->last ;
    
    Liste_Segment *res = simplification_douglas_peucker_rec(L,0,(L->taille)-1, d,TPLP) ; /* Appelle de la simplification récursive sur le premier et le dernier élement de la liste */
    free(TPLP.pointeurs);
    Conversion_Liste_Segment_Liste_Point(res,L) ;
    return ;
}


Liste_Segment *simplification_douglas_peucker_rec(Liste_Point *L, int j1, int j2, double d,  Tableau_Pointeurs_Liste_Point TPLP)
{
    /* Mhh peut être que finalement rester sur une liste chainée ça reste plus interessant 
    Ok on fera un tableau de pointeurs*/
    Point val_j1 = TPLP.pointeurs[j1]->data ; /* Valeur de point J1 */
    Point val_j2 = TPLP.pointeurs[j2]->data ; /* Valeur de point J2 */
    Cellule_Liste_Point * jp = TPLP.pointeurs[j1] ; /* Pointeur de j1+1 */

    Segment S = creerSegment(val_j1,val_j2);
    double dmax = 0 ;
    int k = j1 ;
    int j ;
    double dj;
    Liste_Segment *LS ;
    for (j=j1+1 ; j<=j2 ;j++) /* On aurait pu parcourir les pointeurs directement mais pour plus de clareté on parcours les indices */
    {
        Point valj = jp->data ;
        dj = distancePointSegment(valj,S);
        if (dmax<dj)
        {
            dmax= dj ;
            k=j;
            TPLP.pointeurs[k]=jp ; /* On enregistre dans le tableau la valeur du pointeur à l'indice k */
        }
        if(j1!=j2) jp=jp->suiv; /* Il faut compprendre la valeur jp "j pointeur" comme le pointeur de l'indice j */
    }
    if (dmax<=d) 
    {
        LS = creer_liste_Segment_vide () ;
        ajouter_element_liste_Segment(LS,S);

    }// affecter à L un tableau contenant le segment S. 
    else
    {
        Liste_Segment *L1 = simplification_douglas_peucker_rec(L,j1,k,d,TPLP) ;
        Liste_Segment *L2 = simplification_douglas_peucker_rec(L,k,j2,d,TPLP) ;
        LS = concatener_liste_Segment(L1,L2);
    }
    return LS ;
}

void Conversion_Liste_Segment_Liste_Point(Liste_Segment *LS, Liste_Point *LP) 
{
    /* On vide la liste de points de ses éléments. */
    Cellule_Liste_Point *el=LP->first;	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	LP->first = LP->last = NULL; LP->taille = 0;
    int i;
    Cellule_Liste_Segment *cls = LS->first ;
    Segment S ;
    for (i=0; i<LS->taille; i++)
    {
        S = cls->data ;
        ajouter_element_liste_Point(LP,S.A); /* On ajoute le premier élément de chaque segment */
        cls = cls->suiv;
    }
    ajouter_element_liste_Point(LP,LS->last->data.B); /* On ajoute le dernier Point  */
    return ;

}