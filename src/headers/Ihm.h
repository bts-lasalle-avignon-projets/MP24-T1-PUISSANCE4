#ifndef IHM_H
#define IHM_H

#include <string>
#include <vector>

class Joueur;
class IHM
{
  private:
    static int nbLignesASupprimer;

  public:
    static Joueur*     saisirJoueur();
    static std::string saisieNomJoueur(const std::string& indicationTextuelle,
                                       bool               verifierDoublons);
    static bool        nomJoueurValide(const std::string& nomJoueur);
    static void        afficherMessageTour(const Joueur* joueur);
    static void        afficherVictoire(Joueur* joueur);
    static void        afficherPartieNulle();
    static void        afficherMenu();
    static std::string saisirCommandeDeJeu();
    static void        attendreRetourMenu();
    static void        afficherDynamiquement(const std::string& message);
    static void        effacerTout();
    static void        effacerLignes();
    static void        effacerLignes(int nombreDeLignes);
    static void        effacerSaisie();
    static void        compterNbLignes(const std::string& texte);
    static void        mettreZeroNbLignesASupprimer();
    static void        afficherTexte(const std::string& texte);
    static void        afficherErreur(const std::string& texte);
    static void        afficherRegles();
    static void        attendre(int millisecondes);
    static void        initialiserJeu();
};

#endif // IHM_H
