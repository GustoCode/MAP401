#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"
#include "calcul_contours.h"


int main (int argc, char ** argv)
{
    Image I;
    I =lire_fichier_image(argv[1]);
    contours_image(I);
    printf("\n");
}