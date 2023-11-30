#ifndef PLATEAU
#define PLATEAU

#include <vector>
#include <iostream>
#include "Joueur.h"

class Puisssance;

class Plateau
{
  private:
    int                  lignes;
    int                  colonnes;
    std::vector<Joueur*> plateaux;
    Joueur*              vainqueur;

  public:
    Plateau(int lignes, int colonnes);
    void afficherPlateau() const;
    // string           saisieNom();
    void                  afficherPartie() const;
    Joueur*               getVainqueur();
    int                   getNbLignes() const;
    int                   getNbColonnes() const;
    std::vector<Joueur*>* getPlateau();
    bool                  estUneSequence(int indiceCase, Joueur* case_) const;
    bool                  testerSequence(int indiceCase, Joueur* case_, int indiceCaseTeste) const;
};
#endif // PLATEAU