#!/bin/bash

# Liste des images
images=("fichierPBM/image_poly_tache6.pbm" "fichierPBM/elephant-gotlib.pbm" "fichierPBM/goudyini-A.pbm" "fichierPBM/JoaquimHock-LesArbres.pbm" "fichierPBM/cheval.pbm" "fichierPBM/papillon2.pbm" )

# Liste des valeurs de d
ds=(1 2)

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
