/**
 * voiture.h
 * Declaration de la classe CVoiture
 * Matheo - BTS CIEL
 * 05/10/2026
 */

#ifndef VOITURE_H
#define VOITURE_H

#include <string>

class CVoiture {
private:
    std::string marque;
    std::string modele;
    int puissance;           // Puissance en ch
    std::string motorisation;// Essence, Diesel, Electrique, etc.
    int vitesse;             // Vitesse actuelle en km/h
    bool moteurDemarre;      // Etat du moteur

public:
    // Constructeur remplacant la methode init
    CVoiture(const std::string& marque, const std::string& modele, int puissance, const std::string& motorisation);

    // Methodes d'action
    void demarrer();
    void arreter();
    void accelerer(int valeur);
    void ralentir(int valeur);

    // Methode d'affichage
    void afficherEtat() const;
};

#endif // VOITURE_H
