#ifndef PLATEAU_H
#define PLATEAU_H

#include "Jeton.h"

#include <string>
#include <vector>

class Joueur;
class Partie;

class Plateau
{
  private:
    int                lignes;
    int                colonnes;
    std::vector<Jeton> cases;
    Partie*            partie;

  public:
    Plateau(Partie* partie = nullptr);
    Plateau(Partie* partie, int lignes, int colonnes);
    Plateau(const Plateau& plateau);
    Plateau(Plateau&& plateau) noexcept;
    ~Plateau();
    Plateau&            operator=(const Plateau& plateau) noexcept;
    Plateau&            operator=(Plateau&& plateau) noexcept;
    void                afficherPlateau(int positionNouveauPion) const;
    void                afficherPlateauFinDePartie() const;
    void                afficherNumerosDeColonnes() const;
    void                afficherPartie() const;
    Joueur*             getVainqueur() const;
    int                 getNbLignes() const;
    int                 getNbColonnes() const;
    std::vector<Jeton>* getPlateau();
    bool                estUneSequence(int indiceCase, Jeton casePlateau) const;
    bool             estUneSequence(int indiceCase, Jeton casePlateau, int nbJetonsAaligner) const;
    int              testerSequence(int indiceCase, Jeton casePlateau, int indiceCaseTeste) const;
    std::vector<int> getPositionDeSequenceVainqueur() const;
    std::vector<int> getPositions(int indiceCase, Jeton casePlateau, int indiceCaseTeste) const;
    int              placerJeton(int colonneSelectionnee, Jeton jeton);
    Partie*          getPartie();
    void             supprimerJeton(int indiceJeton);
    int              getNbJetonsAlignes(int positionJeton, Jeton jeton);
    int              getTailleSequenceVainqueur();
    int              getTailleSequence(int indiceCase, Jeton casePlateau);
    bool sequenceEstDansSonAxe(std::vector<int> indicesSequence, bool alignementHorizontal) const;
    bool estPlein() const;
    bool colonneEstPleine(int colonne) const;
};

#endif // PLATEAU_H
