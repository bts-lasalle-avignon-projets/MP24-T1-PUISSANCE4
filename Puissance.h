#define PUISSANCE
#ifdef PUISSANCE

#include <vector>
#include <iostream>
#include "Plateau.h"

using namespace std;

class Puissance
{
  private:
    int             indiceJoueurActuel;
    vector<Joueur>* listeJoueurs;
    Plateau         plateau;

  public:
    Puissance(vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes);
    ~Puissance();

    void demarrerPartie();
    void jouerTour();
    bool partieEstTerminee();
};

#endif