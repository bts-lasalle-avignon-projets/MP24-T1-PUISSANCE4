#include "../headers/Joueur.h"
#include "../headers/Puissance.h"
#include "../headers/Ihm.h"
#include "../headers/Plateau.h"
#include "../headers/Historique.h"
#include "../headers/IA.h"
#include "../headers/Parametres.h"

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

constexpr int nbLignes   = 6;
constexpr int nbColonnes = 7;

using namespace std;

int main()
{
    vector<Joueur> listeJoueurs  = IHM::saisieJoueurs();
    bool           continueLeJeu = true;
    Historique     historique(listeJoueurs);

    while(continueLeJeu)
    {
        IHM::effacerTout();
        IHM::afficherMenu();
        string commande = IHM::saisirCommandeDeJeu();
        IHM::effacerSaisie();
        IHM::effacerLignes();
        if(commande == "j")
        {
            IHM::effacerTout();
            Puissance puissance = *new Puissance(&listeJoueurs, nbLignes, nbColonnes);
            puissance.demarrerPartie();
            historique.savegarderPartie(puissance);
            historique.ajouterVictoire(puissance.getVainqueur());
            IHM::attendreRetourMenu();
        }

        else if(commande == "h")
        {
            historique.afficher();
            IHM::attendreRetourMenu();
        }

        else if(commande == "p")
        {
            Parametres::afficher();
        }

        else if(commande == "r")
        {
            IHM::effacerTout();
            IHM::afficherRegles();
            IHM::attendreRetourMenu();
        }

        else if(commande == "0")
        {
            IHM::effacerTout();
            continueLeJeu = false;
        }
    }
    return 0;
}
