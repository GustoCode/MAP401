#include <stdio.h>
#include "calcul_bezier3.h"



/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Bezier3 *creer_element_liste_Bezier3(Bezier3 v)
{
    Cellule_Liste_Bezier3 *el;
	el = (Cellule_Liste_Bezier3 *)malloc(sizeof(Cellule_Liste_Bezier3));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;    
}

/* creer une liste Bezier3 vide */
Liste_Bezier3 *creer_liste_Bezier3_vide()
{
    Liste_Bezier3 *L = malloc(sizeof(Liste_Bezier3)) ;
    L->taille = 0 ;
    L->first =NULL ;
    L->last = NULL ;
    L->suiv = NULL ;
	return L;
}

/* creer un ensemble de contours vide */
Ensemble_Bezier3 *creer_ensemble_Bezier3_vide ()
{
    Ensemble_Bezier3 *EB;
    EB = malloc (sizeof(Ensemble_Bezier3));
    Liste_Point *tete = NULL;
    EB->nbr = 0 ;
    EB->courbe = 0;
    EB->head = tete ;
    return EB ;    
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Bezier3 *ajouter_element_liste_Bezier3(Liste_Bezier3 *L, Bezier3 b)
{
	Cellule_Liste_Bezier3 *el;
	
	el = creer_element_liste_Bezier3(b);
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
Ensemble_Bezier3 *ajouter_tete_Bezier3(Ensemble_Bezier3 *EB, Liste_Bezier3 *L)
{
    if (EB->nbr == 0) EB->head= L ;
    else
    {
        L->suiv = EB->head ;
        EB->head = L ;
    }
    EB->nbr ++ ;
    EB->courbe += L->taille ; 
    return EB ;
}

Liste_Bezier3 *concatener_liste_Bezier3(Liste_Bezier3 *L1, Liste_Bezier3 *L2)
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

Point Calcul_Point_Bezier3(Bezier3 B, double t)
{
    Point res ;
    res.x = B.A.x*(1.-t)*(1.-t)*(1.-t)+B.B.x*3.*t*(1.-t)*(1.-t)+3.*B.C.x*t*t*(1.-t)+B.D.x*t*t*t ;
    res.y = B.A.y*(1.-t)*(1.-t)*(1.-t)+B.B.y*3.*t*(1.-t)*(1.-t)+3.*B.C.y*t*t*(1.-t)+B.D.y*t*t*t ;
    return res ;
}

double distance_point_bezier3(Point P, Bezier3 B, double ti)
{
    Point projection = Calcul_Point_Bezier3(B,ti) ; /* Approximation d la projection, cf poly */
    double res= distance(P, projection) ;
    return res ;
}

double gamma (int k, int n)
{
    double res ;
    res = 6. *(double)k*(double)k*(double)k*(double)k ;
    res = res - 8.*(double)n*(double)k*(double)k*(double)k ;
    res = res + 6. *(double)k*(double)k ;
    res = res - 4.*(double)n*(double)k ;
    res = res + (double) n * (double) n *(double) n *(double) n ;
    res = res - (double) n *(double) n  ;
    return res ;
}

/* Somme des Poiunt de j+1 à j+n en appliquant gamma
-ordre = true on effectue gamma selon i
-sinon n-i cf poly */
Point Somme_Point_gamma(Tableau_Point T, int j1 , int j2, bool ordre )
{
    
    int i ;
    Point P ;
    Point res ={0,0} ;
    int n = j2-j1;
    for (i=1;i<=n-1;i++)
    {
        P = T.tab[i+j1];
        if (ordre)
        res = sommeVect(res, multScalaire(P,gamma(i,n)));
        else
        res = sommeVect(res, multScalaire(P,gamma(n-i,n)));
    }
    return res ;
}

Bezier3 approx_bezier3 (Tableau_Point T, int j1, int j2)
{
    int n = j2-j1 ;
    Bezier3 res;
    if (n==1 || n== 2)
    {
        Bezier2 tmp = approx_bezier2(T, j1,j2);
        res = Conversion_B2_B3(tmp);
    }
    else
    {
        double alpha, beta, lambda ;
        double N = (double)n ;
        alpha = ((-15)*N*N*N + 5*N*N+ 2*N + 4) / (3*(N+2)*(3*N*N+1)) ;
        beta = (10*N*N*N - 15*N*N + N + 2)/(3*(N+2)*(3*N*N+1)) ;
        lambda = (70*N)/(3*(N*N-4)*(N*N-1)*(3*N*N+1));
        Point C1, C2 ;
        res.A = T.tab[j1] ; //C0
        res.D= T.tab[j2] ; //C3
        C1 = multScalaire(T.tab[j1],alpha) ;
        C1 = sommeVect(C1, multScalaire(Somme_Point_gamma(T,j1,j2,true),lambda)) ;
        C1 = sommeVect(C1,multScalaire(T.tab[j2],beta)) ;
        res.B = C1 ;    //C1
        C2 = multScalaire(T.tab[j1],beta) ;
        C2 = sommeVect(C2, multScalaire(Somme_Point_gamma(T,j1,j2,false),lambda)) ;
        C2 = sommeVect(C2,multScalaire(T.tab[j2],alpha)) ;
        res.C = C2 ; //C2
    }
    return res ;
}

Liste_Bezier3 *simplification_douglas_peucker_b3(Tableau_Point T, int j1, int j2, double d)
{
    int n = j2 - j1 ;
    Bezier3 B = approx_bezier3(T,j1, j2) ;
    Liste_Bezier3 * LB ;
    double dmax = 0 ;
    double ti, dj ;
    int k = j1 ;
    int j, i ;
    for (j=j1+1; j<=j2 ; j++)
    {
        i = j - j1 ;
        ti = (double)i/((double)n) ;
        dj = distance_point_bezier3(T.tab[j],B,ti) ;
        if (dmax< dj)
        {
            dmax= dj ;   
            k= j;
        }
    }
    if (dmax<=d)
    {
        LB= creer_liste_Bezier3_vide() ;
        ajouter_element_liste_Bezier3(LB,B) ;
    }
    else
    {
        Liste_Bezier3 *L1 = simplification_douglas_peucker_b3(T,j1,k,d);
        Liste_Bezier3 *L2 = simplification_douglas_peucker_b3(T,k,j2,d);
        LB = concatener_liste_Bezier3(L1, L2);
    }
    return LB ;
}

Ensemble_Bezier3* simplification_b3_ensemble(Ensemble_Contours *EC, double d)
{
    int i, j;
    Ensemble_Bezier3 *EB = creer_ensemble_Bezier3_vide();
    Tableau_Point T ;
    Contour *C = EC->head ;
    for(i=0 ;i<EC->nbr; i++)
    {
        T = sequence_points_liste_vers_tableau(*C);
        ajouter_tete_Bezier3(EB, simplification_douglas_peucker_b3(T,0,T.taille-1, d) ) ;
        T = vider_tableau(T) ;
        /* Pour eviter des fuites mémoires inutiles on libère au fur et à mesure les cellules du tableau */
        C= C->suiv ;
    }
    return EB ;
}
void ecrire_bezier3_fichier_EPS(Image I,Ensemble_Bezier3 *EB, FILE *f)
{
    UINT L = largeur_image(I) ;
    UINT H = hauteur_image(I) ;
    /* Ecriture de l'entête du fichier */
    fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %d %d\n",L,H) ;

    Liste_Bezier3 *LB = EB->head ;
    Cellule_Liste_Bezier3 *cell;
    int i ;

    for (i=0; i<EB->nbr ; i++) /* Parcours des contours */
    {
        cell = LB->first ;
        Bezier3 B = cell->data;
        fprintf(f,"\n%0.2f %0.2f moveto \n",B.A.x,H- B.A.y );
        //cell = cell->suiv ;
        while (cell) /* Tant que cell est non nul */ 
        {
            B = cell->data ;
            fprintf(f,"%0.2f %0.2f %0.2f %0.2f %0.2f %0.2f curveto\n",B.B.x,H-B.B.y,B.C.x,H-B.C.y, B.D.x,H-B.D.y );
            cell = cell->suiv ;
        }
        LB = LB->suiv ;
    }
    fprintf(f,"\nfill\n\nshowpage") ; /* pour remplir */
   // fprintf(f,"\nstroke\n\nshowpage\n") ; /* pour faire les contours sans remplir */
    return ;
}

void ecrire_bezier3(Image I, Ensemble_Bezier3 *EB, FILE *f)
{
    ecrire_bezier3_fichier_EPS(I,EB,f); 
    printf("Nombre de contours : %d\nNombre de courbes de l'ensemble : %d\n",EB->nbr,EB->courbe);
    
}