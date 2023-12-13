#include <iostream>
#include "Joueur.h"
#include "Puissance.h"
#include "Ihm.h"
#include "Plateau.h"

constexpr int nbLignes   = 6;
constexpr int nbColonnes = 7;

using namespace std;

int main()
{
    bool continueLeJeu = true;

    while(continueLeJeu)
    {
        std::system("clear");

        IHM::afficherMenu();

        string commande = IHM::saisirCommandeDeJeu();
        IHM::effacerLignes(5);

        if(commande == "Jouer" || commande == "j")
        {
            Joueur         joueur1(Jeton(ROUGE), IHM::saisieNomJoueur(1));
            Joueur         joueur2(Jeton(JAUNE), IHM::saisieNomJoueur(2));
            vector<Joueur> listeJoueurs = { joueur1, joueur2 };
            Puissance      puissance(&listeJoueurs, nbLignes, nbColonnes);
            puissance.demarrerPartie();
            IHM::attendreRetourMenu();
        }
        else if(commande == "Règles" || commande == "r")
        {
            IHM::afficherRegles();
            IHM::attendreRetourMenu();
        }
        else if(commande == "Quitter" || commande == "q")
        {
            continueLeJeu = false;
        }
    }

    return 0;
}
