#ifndef PUISSANCE4_H
#define PUISSANCE4_H

#include "Historique.h"

class Joueur;

class Puissance4
{
  private:
    std::vector<Joueur*> listeJoueurs;
    Historique           historique;

    void        jouerNouvellePartie();
    void        afficherHistorique();
    void        parametrer();
    void        afficherLesRegles();
    std::string saisirCommande();

  public:
    Puissance4();
    ~Puissance4();

    void demarrer();
};

#endif // PUISSANCE4_H
