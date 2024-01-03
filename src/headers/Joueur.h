#ifndef JOUEUR
#define JOUEUR

#include "Jeton.h"
#include <string>

class IA;
class Plateau;

class Joueur
{
  private:
    Jeton       couleur;
    std::string nom;
    IA*         ia;

  public:
    Joueur();
    Joueur(Jeton couleur, const std::string& nom, IA* ia);
    Joueur(const Joueur& joueur);
    Joueur(Joueur&& joueur) noexcept;
    ~Joueur();
    Joueur&     operator=(const Joueur& joueur) noexcept;
    Joueur&     operator=(Joueur&& joueur) noexcept;
    bool        operator<(const Joueur& joueur) const;
    std::string getNom() const;
    Jeton       getJeton() const;
    int         jouerCoup(Plateau& plateau);
    bool        estUneIA();
    IA*         getObjetIA();
};

#endif // JOUEUR_H
