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
    static std::string saisirNomJoueur(int numeroJoueur);
    static int         saisirCoup();
    static bool        estNomJoueurValide(const std::string& nomJoueur);
    static void        afficherMessageTour(const Joueur& joueur);
    static void        afficherVictoire(Joueur* joueur);
    static void        afficherMenu();
    static void        afficherBanniere();
    static std::string saisirCommandeDeJeu();
    static int         saisirChoixParametre();
    static void        attendreRetourMenu();
    static void        afficherDynamiquement(const std::string& message);
    static void        effacerTout();
    static void        effacerLignes();
    static void        effacerLignes(int nombreDeLignes);
    static void        effacerSaisie();
    static void        compterNbLignes(const std::string& texte);
    static void        mettreZeroNbLignesASupprimer();
    static void        afficherTexte(const std::string& texte);
    static void        afficherRegles();
    static void        afficherParametres();
    static void        saisirJoueurs(std::vector<Joueur*>& listeJoueurs, int nbJoueurs);
};

#endif // IHM_H
