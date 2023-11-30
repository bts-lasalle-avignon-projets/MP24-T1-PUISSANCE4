#ifndef PLATEAU
#define PLATEAU

#include <vector>
#include <iostream>

#include "Jeton.h"

class Joueur;
class Puissance;

class Plateau
{
  private:
    int                lignes;
    int                colonnes;
    std::vector<Jeton> cases;
    Puissance*         partie;

  public:
    Plateau(Puissance* partie, int lignes, int colonnes);
    void                afficherPlateau() const;
    void                afficherPartie() const;
    Joueur*             getVainqueur();
    int                 getNbLignes() const;
    int                 getNbColonnes() const;
    std::vector<Jeton>* getPlateau();
    bool                estUneSequence(int indiceCase, Jeton casePlateau) const;
    bool testerSequence(int indiceCase, Jeton casePlateau, int indiceCaseTeste) const;
};
#endif // PLATEAU