/**
 * @file main.cpp
 * @brief Programme principal de test pour CVoiture
 * @author Matheo - BTS CIEL
 * @date 17/11/2026
 */

#include "voiture.h"

int main() {
    // 1. Initialisation (Peugeot, 208, 100 ch, Essence, Tempmoteur)
    CVoiture maVoiture("Peugeot", "208", 100, "Essence", "Tempmoteur");

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

    // 7. temperature du moteur
    maVoiture.tempmoteur();
    maVoiture.afficherEtat();

    return 0;
}