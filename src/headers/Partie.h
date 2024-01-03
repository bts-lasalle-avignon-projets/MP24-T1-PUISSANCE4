#ifndef PARTIE_H
#define PARTIE_H

#include "Plateau.h"
#include "Jeton.h"

#include <string>
#include <vector>

class Partie
{
  private:
    Jeton                 indiceJoueurActuel;
    std::vector<Joueur*>* listeJoueurs;
    Plateau               plateau;

  public:
    Partie(std::vector<Joueur*>* listeJoueurs = nullptr);
    Partie(std::vector<Joueur*>* listeJoueurs, int nbLignes, int nbColonnes);
    Partie(const Partie& partie);
    Partie(Partie&& partie) noexcept;
    ~Partie();
    Partie& operator=(const Partie& partie) noexcept;
    Partie& operator=(Partie&& partie) noexcept;

    void                  demarrer();
    int                   jouerTour();
    bool                  partieEstTerminee();
    Joueur*               recupererJoueurAyantJeton(Jeton jeton);
    Joueur*               getVainqueur() const;
    std::vector<Joueur*>* getJoueurs() const;
};

#endif // PARTIE_H
