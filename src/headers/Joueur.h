#ifndef JOUEUR
#define JOUEUR

#include "../headers/Jeton.h"
#include <iostream>

// class IA;
class Plateau;

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
    virtual ~Joueur();
    Joueur&     operator=(const Joueur& joueur) noexcept;
    Joueur&     operator=(Joueur&& joueur) noexcept;
    bool        operator<(const Joueur& joueur) const;
    std::string getNom() const;
    Jeton       getJeton() const;
    virtual int jouerCoup(Plateau& plateau);
};
#endif // JOUEUR