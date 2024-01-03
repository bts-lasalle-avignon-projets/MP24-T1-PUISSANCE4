#include "Puissance4.h"
#include "Joueur.h"
#include "Partie.h"
#include "Ihm.h"
#include "Plateau.h"
#include "Historique.h"
#include "IA.h"
#include "Parametres.h"

using namespace std;

constexpr int nbJoueursParDefaut = 2;

Puissance4::Puissance4()
{
}

Puissance4::~Puissance4()
{
}

void Puissance4::demarrer()
{
    IHM::effacerTout();
    IHM::afficherBanniere();

    vector<Joueur> listeJoueurs = IHM::saisirJoueurs(nbJoueursParDefaut);
    Historique     historique(listeJoueurs);

    bool continueLeJeu = true;
    while(continueLeJeu)
    {
        IHM::effacerTout();
        IHM::afficherBanniere();
        IHM::afficherMenu();
        string commande = IHM::saisirCommandeDeJeu();
        IHM::effacerLignes();

        if(commande == "1")
        {
            IHM::effacerTout();
            Partie partie(&listeJoueurs);
            partie.demarrer();
            historique.savegarderPartie(partie);
            historique.ajouterVictoire(partie.getVainqueur());
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
}
