#ifndef PUISSANCE_H
#define PUISSANCE_H

#include "Plateau.h"
#include "Jeton.h"

#include <string>
#include <vector>

#define INDICE_JOUEUR_NON_DEFINI -1

class Puissance
{
  private:
    int                  indiceJoueurActuel;
    std::vector<Joueur>* listeJoueurs;
    Plateau              plateau;

  public:
    Puissance(std::vector<Joueur>* listeJoueurs = nullptr);
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
