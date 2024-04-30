#!/bin/bash

# Liste des images
images=("fichierPBM/Asterix3.pbm" "fichierPBM/lettre-L-cursive.pbm" "fichierPBM/ColombesDeLaPaix.pbm")

# Liste des valeurs de d
ds=(0 1)

# Pour chaque image
for img in "${images[@]}"
do
    # Extraire le nom de l'image sans l'extension
    img_name=$(basename "$img" .pbm)
    
    # Pour chaque valeur de d
    for d in "${ds[@]}"
    do
        if [ "$d" -eq 1 ] ;then 
            # Créer le nom du fichier de sortie
            output="fichierEPS/${img_name}.eps"
        else
            output="fichierContours/${img_name}.contours"
        fi
        # Lancer le programme avec les arguments correspondants
        ./test_contours "$img" "$output" "$d"
        
        echo "Traitement de $img avec EPS=$d terminé. Fichier de sortie : $output "
        echo
    done
done
