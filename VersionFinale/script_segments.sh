#!/bin/bash

# Liste des images
images=("fichierPBM/Asterix3.pbm" "fichierPBM/lettre-L-cursive.pbm" "fichierPBM/ColombesDeLaPaix.pbm")

# Liste des valeurs de d
ds=(0 0.5 1 2 4 8 16)

# Pour chaque image
for img in "${images[@]}"
do
    # Extraire le nom de l'image sans l'extension
    img_name=$(basename "$img" .pbm)
    
    # Pour chaque valeur de d
    for d in "${ds[@]}"
    do
        # Créer le nom du fichier de sortie
        output="fichierEPS/${img_name}_seg_${d}.eps"
        
        # Lancer le programme avec les arguments correspondants
        ./test_simplification_seg "$img" "$output" "$d"
        
        echo "Traitement de $img avec d=$d terminé. Fichier de sortie : $output"
    done
done
