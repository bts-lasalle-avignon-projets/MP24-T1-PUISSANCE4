#ifndef JOUEUR
#define JOUEUR

#include "Jeton.h"
#include <iostream>

class Joueur
{
  private:
    Jeton       couleur;
    std::string nom;

  public:
    Joueur(Jeton couleur, std::string nom);
    ~Joueur();
    std::string getNom() const;
    Jeton       getJeton() const;
};
#endif // JOUEUR