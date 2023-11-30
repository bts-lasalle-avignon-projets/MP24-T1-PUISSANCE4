#ifndef JOUEUR
#define JOUEUR

#include "Couleur.h"
#include <iostream>

class Joueur
{
  private:
    Couleur     couleur;
    std::string nom;

  public:
    Joueur(Couleur couleur, std::string nom);
    ~Joueur();
    std::string getNom() const;
    Couleur     getCouleur() const;
};
#endif // JOUEUR