/**
- voiture.h
- Declaration de la classe CVoiture
- Matheo - BTS CIEL
- 05/10/2026
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

    double posX;             // Position horizontale
    double posY;             // Position verticale
    double kilometrageTotal;

public:
    // Constructeur
    CVoiture(const std::string& marque, const std::string& modele, int puissance, const std::string& motorisation);

    // Methodes d'action existantes
    void demarrer();
    void arreter();
    void accelerer(int valeur);
    void ralentir(int valeur);

    // Déplacement et Affichage GPS
    void deplacer(double deltaX, double deltaY);
    void afficherPosition() const;

    double getPosX() const;
    double getPosY() const;
    double getKilometrageTotal() const;

    // Methode d'affichage globale
    void afficherEtat() const;
};

#endif // VOITURE_H
