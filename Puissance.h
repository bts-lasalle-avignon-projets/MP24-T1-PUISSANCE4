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
    Puissance(std::vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes);
    ~Puissance();

    void    demarrerPartie();
    void    jouerTour();
    bool    partieEstTerminee();
    Joueur* recupererJoueurAyantJeton(Jeton jeton);
};

#endif