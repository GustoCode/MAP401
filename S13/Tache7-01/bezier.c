#include "stdio.h"
#include "bezier.h"
#include "geometrie_2d.h"
#include "sequence_point.h"
#include "simplification_contours.h"


/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Bezier2 *creer_element_liste_bezier2(Bezier2 v)
{
    Cellule_Liste_Bezier2 *el;
	el = (Cellule_Liste_Bezier2 *)malloc(sizeof(Cellule_Liste_Bezier2));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;    
}

/* creer une liste bezier2 vide */
Liste_Bezier2 *creer_liste_bezier2_vide()
{
    Liste_Bezier2 *L = malloc(sizeof(Liste_Bezier2)) ;
    L->taille = 0 ;
    L->first =NULL ;
    L->last = NULL ;
    L->suiv = NULL ;
	return L;
}

/* creer un ensemble de contours vide */
Ensemble_Bezier2 *creer_ensemble_bezier2_vide ()
{
    Ensemble_Bezier2 *EB;
    EB = malloc (sizeof(Ensemble_Bezier2));
    Liste_Point *tete = NULL;
    EB->nbr = 0 ;
    EB->courbe = 0;
    EB->head = tete ;
    return EB ;    
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Bezier2 *ajouter_element_liste_Bezier2(Liste_Bezier2 *L, Bezier2 b)
{
	Cellule_Liste_Bezier2 *el;
	
	el = creer_element_liste_Bezier2(b);
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

/* Ajouter à la tete d'un ensemble de contours une liste de point */
Ensemble_Bezier2 ajouter_tete_bezier2(Ensemble_Bezier2 EB, Liste_Bezier2 *L)
{
    if (EB.nbr == 0) EB.head= L ;
    else
    {
        L->suiv = EB.head ;
        EB.head = L ;
    }
    EB.nbr ++ ;
    EB.courbe += L->taille ; 
    return EB ;
}

Liste_Bezier2 *concatener_liste_bezier2(Liste_Bezier2 *L1, Liste_Bezier2 *L2)
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

Point Calcul_Point_Bezier(Bezier2 B, double t)
{
    Point res ;
    res.x = B.A.x*(1-t)*(1-t)+B.B.x*2*t*(1-t)+B.C.x*t*t ;
    res.y = B.A.y*(1-t)*(1-t)+B.B.y*2*t*(1-t)+B.C.y*t*t ;
    return res ;
}

Bezier3 Conversion_B2_B3(Bezier2 B2)
{
    Bezier3 res ;
    res.A = B2.A ;
    res.D = B2.C ;
    res.B = multScalaire(sommeVect(B2.A,multScalaire(B2.B,2)),1/3);
    /* Les opérations sur les vecteurs fonctionnent sur les points se sont des types synonymes */
    res.C = multScalaire(sommeVect(B2.C,multScalaire(B2.B,2)),1/3);
    return res ;
}

/* à modifier */ /* Je suis pas sur qu'il faille encore le modifier */
Point Somme_Point_Contours(Tableau_Point T, int j1 , int j2)
{
    int i ;
    Point P ;
    Point res ;
    int n = j2-j1;
    for (i=j1+1;i<j1+n;i++)
    {
        P = T.tab[i];
        res = sommeVect(res, P);
    }
    return res ;
}

Bezier2 approx_bezier2 (Tableau_Point T, int j1, int j2)
{
    double alpha, beta ;
    int n = j2-j1 ;
    alpha = 3*((double)n)/((double)(n)*(double)(n)-1) ;
    beta = 1 - (2* (double)n)/2*((double)n + 1) ;
    Bezier2 res ;

    res.A = T.tab[j1] ;
    res.C= T.tab[j2] ;
    if (n==1)
    {res.B=multScalaire(sommeVect(T.tab[j1],T.tab[j2]),0.5);
    return res ;
    }
    else
    {
    res.B = sommeVect(multScalaire(Somme_Point_Contours(T,j1,j2),alpha), multScalaire(sommeVect(T.tab[j1],T.tab[j2]),beta)) ;
    return res ;
    }
}

double distance_point_bezier2(Point P, Bezier2 B, double ti)
{
    Point projection = Calcul_Point_Bezier(B,ti) ; /* Approximation de la projection, cf poly */
    double res= distance(P, projection) ;
    return res ;
}

Liste_Bezier2 *simplification_douglas_peucker_b2(Tableau_Point T, int j1, int j2, double d)
{
    int n = j2 - j1 ;
    Bezier2 B = approx_bezier2(T,j1, j2) ;
    Liste_Bezier2 * LB ;
    double dmax = 0 ;
    double ti, dj ;
    int k = j1 ;
    int j, i ;
    for (j=j1+1; j<j2 ; j++)
    {
        i = j - j1 ;
        ti = (double)i/((double)n) ;
        dj = distance_point_bezier2(T.tab[j],B,ti) ;
        if (dmax< dj)
        {
            dmax= dj ;
            k= j;
        }
    }
    if (dmax<=dj)
    {
        LB= creer_liste_bezier2_vide() ;
        ajouter_element_liste_Bezier2(LB,B) ;
    }
    else
    {
        Liste_Bezier2 *L1 = simplification_douglas_peucker_b2(T,j1,k,d);
        Liste_Bezier2 *L2 = simplification_douglas_peucker_b2(T,k,j2,d);
        LB = concatener_liste_bezier2(L1, L2);
    }
    return LB ;
}

Ensemble_Bezier2 *simplification_b2_ensemble (Ensemble_Contours *EC, double d)
{
    int i, j;
    Ensemble_Bezier2 *EB = creer_ensemble_bezier2_vide();
    Tableau_Point T ;
    Contour *C = EC->head ;
    for(i=0 ;i<EC->nbr; i++)
    {
        T = sequence_points_liste_vers_tableau(*C);
        ajouter_tete_bezier2(*EB, simplification_douglas_peucker_b2(T,0,T.taille-1, d) ) ;
        T = vider_tableau(T) ;
        /* Pour eviter des fuites mémoires inutiles on libère au fur et à mesure les cellules du tableau */
        C= C->suiv ;
    }
    return EB ;
}

void ecrire_bezier2_fichier_EPS(Image I,Ensemble_Bezier2 *EB, FILE *f)
{
    UINT L = largeur_image(I) ;
    UINT H = hauteur_image(I) ;
    /* Ecriture de l'entête du fichier */
    fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %d %d\n",L,H) ;

    Liste_Bezier2 *LB = EB->head ;
    Cellule_Liste_Bezier2 *cell;
    int i ;

    for (i=1; i<EB->nbr ; i++) /* Parcours des contours */
    {
        cell = LB->first ;
        Bezier3 B3 = Conversion_B2_B3(cell->data);
        fprintf(f,"\n%0.2f %0.2f moveto \n",B3.A.x, B3.A.y );
        //cell = cell->suiv ;
        while (cell) /* Tant que cell est non nul */ 
        {
            B3 = Conversion_B2_B3(cell->data);
            fprintf(f,"%.02f %0.2f %.02f %0.2f %.02f %0.2f curveto\n",B3.B.x, B3.B.y,B3.C.x, B3.C.y, B3.D.x, B3.D.y );
            cell = cell->suiv ;
        }
        LB = LB->suiv ;
    }
    fprintf(f,"\nfill\n\nshowpage") ; /* pour remplir */
   // fprintf(f,"\nstroke\n\nshowpage\n") ; /* pour faire les contours sans remplir */
    return ;
}

void ecrire_bezier2(Image I, Ensemble_Bezier2 *EB, FILE *f)
{
    ecrire_contour_fichier_EPS(I,EB,f); 
    printf("Nombre de contours : %d\nNombre de courbes de l'ensemble : %d\n",EB->nbr,EB->courbe);
    
}