/**
 * voiture.cpp
 * Definition des methodes de la classe CVoiture
 * Matheo - BTS CIEL
 * 05/10/2026
 */

#include "voiture.h"
#include <iostream>

// Constructeur
CVoiture::CVoiture(const std::string& marque, const std::string& modele, int puissance, const std::string& motorisation)
    : marque(marque), modele(modele), puissance(puissance), motorisation(motorisation), vitesse(0), moteurDemarre(false) {}

void CVoiture::demarrer() {
    if (!moteurDemarre) {
        moteurDemarre = true;
        std::cout << "Le moteur demarre." << std::endl;
    } else {
        std::cout << "Le moteur est deja demarre." << std::endl;
    }
}

void CVoiture::arreter() {
    if (vitesse == 0) {
        moteurDemarre = false;
        std::cout << "Le moteur s'arrete." << std::endl;
    } else {
        std::cout << "Impossible d'arreter le moteur en roulant !" << std::endl;
    }
}

void CVoiture::accelerer(int valeur) {
    if (moteurDemarre) {
        vitesse += valeur;
        std::cout << "Acceleration de " << valeur << " km/h." << std::endl;
    } else {
        std::cout << "Impossible d'accelerer, le moteur est eteint." << std::endl;
    }
}

void CVoiture::ralentir(int valeur) {
    if (vitesse >= valeur) {
        vitesse -= valeur;
    } else {
        vitesse = 0;
    }
    std::cout << "Ralentissement de " << valeur << " km/h." << std::endl;
}

void CVoiture::afficherEtat() const {
    std::cout << "\n=================================" << std::endl;
    std::cout << "Vehicule : " << marque << " " << modele << std::endl;
    std::cout << "Puissance : " << puissance << " ch | Motorisation : " << motorisation << std::endl;
    std::cout << "Moteur : " << (moteurDemarre ? "Allume" : "Eteint") << std::endl;
    std::cout << "Vitesse : " << vitesse << " km/h" << std::endl;
    std::cout << "=================================\n" << std::endl;
}
