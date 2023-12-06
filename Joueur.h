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
    Joueur();
    Joueur(Jeton couleur, const std::string& nom);
    Joueur(const Joueur& joueur);
    Joueur(Joueur&& joueur) noexcept;
    ~Joueur();
    Joueur&     operator=(const Joueur& joueur) noexcept;
    Joueur&     operator=(Joueur&& joueur) noexcept;
    std::string getNom() const;
    Jeton       getJeton() const;
};
#endif // JOUEUR