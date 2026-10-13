/**
- main.cpp
- Programme principal de test pour CVoiture
- Matheo - BTS CIEL
- 05/10/2026
 */

#include <iostream>
#include "voiture.h"

int main() {
    // 1. Initialisation (Peugeot, 208, 100 ch, Essence)
    CVoiture maVoiture("Peugeot", "208", 100, "Essence");

    // 2. Affichage des informations
    maVoiture.afficherEtat();

    // 3. Demarrage
    maVoiture.demarrer();

    // 4. Acceleration de 50 km/h + affichage
    maVoiture.accelerer(50);
    maVoiture.afficherEtat();

    // 5. Ralentissement de 20 km/h + affichage
    maVoiture.ralentir(20);
    maVoiture.afficherEtat();

    // 6. Arret du véhicule
    maVoiture.ralentir(30); // ramene la vitesse a 0
    maVoiture.arreter();
    maVoiture.afficherEtat();

    // 7. Test du déplacement GPS (ex: +10 km en X et +5 km en Y)
    maVoiture.deplacer(10.0, 5.0);

    // 8. Rapport GPS et Kilométrage via les getters
    std::cout << "\n--- RAPPORT GPS ---" << std::endl;
    std::cout << "Position X : " << maVoiture.getPosX() << " km" << std::endl;
    std::cout << "Position Y : " << maVoiture.getPosY() << " km" << std::endl;
    std::cout << "Kilometrage total : " << maVoiture.getKilometrageTotal() << " km" << std::endl;

    return 0;
}