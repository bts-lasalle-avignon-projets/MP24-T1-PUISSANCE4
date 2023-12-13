#include <iostream>
#include "Joueur.h"
#include "Puissance.h"
#include "Ihm.h"
#include "Plateau.h"
#include "Historique.h"

constexpr int nbLignes   = 6;
constexpr int nbColonnes = 7;

using namespace std;

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

int main()
{
    Joueur         joueur1(Jeton(ROUGE), IHM::saisieNomJoueur(1));
    Joueur         joueur2(Jeton(JAUNE), IHM::saisieNomJoueur(2));
    vector<Joueur> listeJoueurs  = { joueur1, joueur2 };
    bool           continueLeJeu = true;
    Historique     historique(listeJoueurs);

    IHM::effacerLignes(3);

    while(continueLeJeu)
    {
        std::system("clear");
        IHM::afficherMenu();
        string commande = IHM::saisirCommandeDeJeu();
        IHM::effacerLignes(5);
        if(commande == "play" || commande == "p")
        {
            Puissance* puissance = new Puissance(&listeJoueurs, nbLignes, nbColonnes);
            puissance->demarrerPartie();
            historique.savegarderPartie(puissance);
            historique.ajouterVictoire(puissance->getVainqueur());
            IHM::attendreRetourMenu();
        }
        else if(commande == "history" || commande == "h")
        {
            historique.afficher();
            IHM::attendreRetourMenu();
        }
    }
    return 0;
}
