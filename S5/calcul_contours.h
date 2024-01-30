#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"
#include "geometrie_2d.h"



typedef enum {NORD=0,OUEST=1,SUD=2,EST=3} Orientation;

/* Donne le point apres avoir avancé d'une case suivant l'orientation */
Point avancer (Point p, Orientation O) ; 

Orientation nouvelle_orientation(Void) ;

void memoriser_position(Point P) ;

Point trouver_pixel_depart (Image I) ;




