#ifndef PARTIE_H
#define PARTIE_H

#include "Plateau.h"
#include "Jeton.h"

#include <string>
#include <vector>

#define INDICE_JOUEUR_NON_DEFINI -1

class Partie
{
  private:
    int                  indiceJoueurActuel;
    std::vector<Joueur>* listeJoueurs;
    Plateau              plateau;

  public:
    Partie(std::vector<Joueur>* listeJoueurs = nullptr);
    Partie(std::vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes);
    Partie(const Partie& puissance);
    Partie(Partie&& puissance) noexcept;
    ~Partie();
    Partie& operator=(const Partie& puissance) noexcept;
    Partie& operator=(Partie&& puissance) noexcept;

    void                 demarrer();
    int                  jouerTour();
    bool                 partieEstTerminee();
    Joueur*              recupererJoueurAyantJeton(Jeton jeton);
    Joueur*              getVainqueur() const;
    std::vector<Joueur>* getJoueurs() const;
};

#endif // PARTIE_H
