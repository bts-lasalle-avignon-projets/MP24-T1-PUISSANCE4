#ifndef PUISSANCE4_H
#define PUISSANCE4_H

#include "Historique.h"

class Joueur;

class Puissance4
{
  private:
    std::vector<Joueur*> listeJoueurs;
    Historique           historique;

    void               jouerNouvellePartie();
    void               afficherHistorique();
    static void        parametrer();
    static void        afficherLesRegles();
    static std::string saisirCommande();

  public:
    Puissance4();
    ~Puissance4();
    Puissance4(const Puissance4& other)                = delete;
    Puissance4& operator=(const Puissance4& other)     = delete;
    Puissance4(Puissance4&& other) noexcept            = delete;
    Puissance4& operator=(Puissance4&& other) noexcept = delete;
    void        demarrer();
};

#endif // PUISSANCE4_H
