#ifndef JOUEUR_H
#define JOUEUR_H

#include "Jeton.h"
#include <string>

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
    Joueur&             operator=(const Joueur& joueur) noexcept;
    Joueur&             operator=(Joueur&& joueur) noexcept;
    bool                operator<(const Joueur& joueur) const;
    virtual std::string getNom() const;
    virtual Jeton       getJeton() const;
    virtual int         jouerCoup(Plateau& plateau) = 0;
};

#endif // JOUEUR_H
