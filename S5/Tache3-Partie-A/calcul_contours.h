
#ifndef _CALCUL_CONTOURS_H
#define _CALCUL_CONTOURS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"
#include "geometrie_2d.h"



typedef enum {NORD=0,OUEST=1,SUD=2,EST=3} Orientation;

/* Donne le point apres avoir avancé d'une case suivant l'orientation */
Point avancer (Point p, Orientation O) ; 

/* donne l'orientation tournée de 90° dans le sens trigo de l'orientation donnée en argument */
Orientation tourner90 (Orientation o) ;

/* donne l'orientation tournée de 270° dans le sens trigo de l'orientation donnée en argument */
Orientation tourner270 (Orientation o) ;

/* Donne le calcul de la novelle orientation*/
Orientation nouvelle_orientation(Image I, Point position, Orientation o) ;

/* écrit sur la sortie standart la position du robot */
void memoriser_position(Point P) ;

/* Cherche naivement le premier pixel candidat pour les contours d'une image  */
Point trouver_pixel_depart (Image I) ;

/* Calcul du contour de l'image */
void contours_image (Image I ) ;


#endif 
