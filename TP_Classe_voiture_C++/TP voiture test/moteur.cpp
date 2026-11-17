/**
 * @file moteur.cpp
 * @brief Definition des methodes de la classe CVoiture
 * @author Matheo - BTS CIEL
 * @date 17/11/2026
 */

#include "voiture.h"

CVoiture::CVoiture(const std::string& marque, const std::string& modele, int puissance, const std::string& motorisation, int tempmoteur)
    : marque(marque), modele(modele), puissance(puissance), motorisation(motorisation), tempmoteur(moteur), vitesse(0), moteurDemarre(false) {}

void CVoiture::demarrer() {
    if (!moteurDemarre) {
        moteurDemarre = true;
        std::cout << "Le moteur demarre." << std::endl;
    } else {
        std::cout << "temperature du moteur demarre" << std::endl;
    }
}
