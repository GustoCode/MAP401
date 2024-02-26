#!/bin/bash

# Chemin vers le répertoire contenant les fichiers .pbm
repertoire_pbm="./fichierPBM"

# Chemin vers le répertoire où les fichiers .eps seront générés
repertoire_eps="./fichierContours"

# Parcours des fichiers .pbm dans le répertoire spécifié
for fichier_pbm in "$repertoire_pbm"/*.pbm; do
    # Vérification si un fichier .pbm existe
    if [ -e "$fichier_pbm" ]; then
        # Extraction du nom de fichier sans extension et construction du chemin du fichier .eps
        nom_fichier=$(basename "$fichier_pbm" .pbm)
        fichier_eps="$repertoire_eps/$nom_fichier.contours"

        echo "Conversion de $fichier_pbm en $fichier_eps"
        # Exécution de ./test_contours avec les fichiers .pbm et .eps correspondants
        ./test_contours "$fichier_pbm" "$fichier_eps"

    fi
done

echo "Terminé."
