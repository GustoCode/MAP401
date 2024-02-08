#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"


int main (int argc, char ** argv)
{
    Image I, negatif ;

    I =lire_fichier_image(argv[1]);
    ecrire_image(I);
    printf("\n");
    negatif = negatif_image(I);
    ecrire_image(negatif);
}