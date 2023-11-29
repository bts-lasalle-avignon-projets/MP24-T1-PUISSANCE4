#pragma once
#define PLATEAU

#ifdef PLATEAU
#include <vector>
#include <iostream>
#include "Joueur.h"

using namespace std;
class Puisssance;

class Plateau
{
  private:
    int             lignes;
    int             colonnes;
    vector<Joueur*> plateaux;
    Joueur*         vainqueur;

  public:
    Plateau(int lignes, int colonnes);
    void             afficherPlateau() const;
    void             afficherPartie() const;
    Joueur*          getVainqueur();
    int              getNbLignes() const;
    int              getNbColonnes() const;
    vector<Joueur*>* getPlateau();
    bool             estUneSequence(int indiceCase, Joueur* case_) const;
    bool             testerSequence(int indiceCase, Joueur* case_, int indiceCaseTeste) const;
};
#endif // PLATEAU