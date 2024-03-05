
#ifndef _CALCUL_CONTOURS_H
#define _CALCUL_CONTOURS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"
#include "geometrie_2d.h"
#include "sequence_point.h"



typedef enum {NORD=0,OUEST=1,SUD=2,EST=3} Orientation;
typedef enum {GAUCHE=0,DROITE=1,} Cote;


/* Donne le point apres avoir avancé d'une case suivant l'orientation */
Point avancer (Point p, Orientation O) ; 

/* donne l'orientation tournée de 90° dans le sens trigo de l'orientation donnée en argument */
Orientation tourner90 (Orientation o) ;

/* donne l'orientation tournée de 270° dans le sens trigo de l'orientation donnée en argument */
Orientation tourner270 (Orientation o) ;

/* Retourne le pixel devant le robot selon son orientation passé en argument et le coté passé en argument */
Pixel getPixelCote(Image I, Point p, Orientation o, Cote c) ;

/* Donne le calcul de la novelle orientation*/
Orientation nouvelle_orientation(Image I, Point position, Orientation o) ;

/* écrit sur la sortie standart la position du robot */
void memoriser_position(Point p, Liste_Point *L) ;

/* Initialise l'image masque */
Image init_masque(Image M, Image I) ;

/* Cherche naivement le premier pixel candidat pour les contours d'une image  */
Point trouver_pixel_depart (Image I, Image M) ;

/* Calcul du contour de l'image */
Ensemble_Contours * contours_image (Image I) ;

/* ecriture du fichier de contours */
void ecrire_contour_fichier (Ensemble_Contours *ES, FILE *f) ;

/* ecritude du fichier de contours au format EPS */
void ecrire_contour_fichier_EPS(Image I,Ensemble_Contours *ES, FILE *f);

/* ecriture des contours 
Si EPS = true écriture des contours au format .eps
Si EPS= false écriture des contours au format .contours 
La fonction écrit aussi sur la console le nombre total de contours et le nombre de segments*/
void ecrire_contour(Image I, Ensemble_Contours *ES, FILE *f, bool EPS);


#endif 
