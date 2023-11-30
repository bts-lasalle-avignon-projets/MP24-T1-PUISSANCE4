#ifndef IHM_H
#define IHM_H

#include <string>

class Joueur;
class IHM
{
  public:
    static std::string saisieNomJoueur(int numeroJoueur);
    static void        afficherMessageTour(const Joueur& joueur);
    static void        afficherVictoire(Joueur* joueur);
};

#endif // IHM_H
