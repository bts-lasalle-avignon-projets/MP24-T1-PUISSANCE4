#include "Joueur.h"
#include "Puissance.h"
#include "Ihm.h"
#include "Plateau.h"
#include "Historique.h"
#include "IA.h"
#include "Parametres.h"

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    vector<Joueur> listeJoueurs  = IHM::saisirJoueurs();
    bool           continueLeJeu = true;
    Historique     historique(listeJoueurs);

    while(continueLeJeu)
    {
        IHM::effacerTout();
        IHM::afficherBanniere();
        IHM::afficherMenu();
        string commande = IHM::saisirCommandeDeJeu();
        IHM::effacerSaisie();
        IHM::effacerLignes();
        if(commande == "1")
        {
            IHM::effacerTout();
            Puissance puissance = *new Puissance(&listeJoueurs);
            puissance.demarrerPartie();
            historique.savegarderPartie(puissance);
            historique.ajouterVictoire(puissance.getVainqueur());
            IHM::attendreRetourMenu();
        }

        else if(commande == "2")
        {
            historique.afficher();
            IHM::attendreRetourMenu();
        }

        else if(commande == "3")
        {
            Parametres::afficher();
        }

        else if(commande == "4")
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
