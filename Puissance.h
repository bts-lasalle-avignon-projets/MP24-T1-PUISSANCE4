#ifndef PUISSANCE
#define PUISSANCE

#include <vector>
#include <iostream>
#include "Plateau.h"

#include "Jeton.h"
class Puissance
{
  private:
    int                  indiceJoueurActuel;
    std::vector<Joueur>* listeJoueurs;
    Plateau              plateau;

  public:
    Puissance();
    Puissance(std::vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes);
    Puissance(const Puissance& puissance);
    Puissance(Puissance&& puissance) noexcept;
    ~Puissance();
    Puissance& operator=(const Puissance& puissance) noexcept;
    Puissance& operator=(Puissance&& puissance) noexcept;

    void    demarrerPartie();
    void    jouerTour();
    bool    partieEstTerminee();
    Joueur* recupererJoueurAyantJeton(Jeton jeton);
    Joueur* getVainqueur() const;
};

#endif