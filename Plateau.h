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
    Plateau();
    Plateau(Puissance* partie, int lignes, int colonnes);
    Plateau(const Plateau& plateau);
    Plateau(Plateau&& plateau) noexcept;
    ~Plateau();
    Plateau&            operator=(const Plateau& plateau) noexcept;
    Plateau&            operator=(Plateau&& plateau) noexcept;
    void                afficherPlateau() const;
    void                afficherNumerosDeColonnes() const;
    void                afficherPartie() const;
    Joueur*             getVainqueur() const;
    int                 getNbLignes() const;
    int                 getNbColonnes() const;
    std::vector<Jeton>* getPlateau();
    bool                estUneSequence(int indiceCase, Jeton casePlateau) const;
    bool       testerSequence(int indiceCase, Jeton casePlateau, int indiceCaseTeste) const;
    int        placerJeton(int colonneSelectionnee, Jeton jeton);
    Puissance* getPartie();
    void       supprimerJeton(int indiceJeton);
    int        getNbJetonsAlignes(int positionJeton, Jeton jeton);
};
#endif // PLATEAU