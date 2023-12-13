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
    static void        afficherMenu();
    static std::string saisirCommandeDeJeu();
    static void        attendreRetourMenu();
    static void        effacerLignes(int nombreDeLignes);
    static void        afficherDynamiquement(const std::string& message);
    static void        afficherRegles();
};

#endif // IHM_H
