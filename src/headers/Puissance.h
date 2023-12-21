#ifndef PUISSANCE
#define PUISSANCE

#include <vector>
#include <iostream>

#include "../headers/Plateau.h"
#include "../headers/Jeton.h"
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

    void                 demarrerPartie();
    int                  jouerTour();
    bool                 partieEstTerminee();
    Joueur*              recupererJoueurAyantJeton(Jeton jeton);
    Joueur*              getVainqueur() const;
    std::vector<Joueur>* getJoueurs() const;
};

#endif // PUISSANCE_H
