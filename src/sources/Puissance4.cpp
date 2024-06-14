#include "Puissance4.h"
#include "Joueur.h"
#include "Partie.h"
#include "Ihm.h"

#include <memory>

using namespace std;

constexpr int nbJoueursParDefaut = 2;

Puissance4::Puissance4()
{
}

Puissance4::~Puissance4()
{
    for(auto it = listeJoueurs.begin(); it != listeJoueurs.end(); ++it)
    {
        std::unique_ptr<Joueur> joueurPtr(*it);
    }
}
void Puissance4::demarrer()
{
    IHM::effacerTout();
    IHM::afficherBanniere();

    IHM::saisirJoueurs(listeJoueurs, nbJoueursParDefaut);

    bool continueLeJeu = true;
    while(continueLeJeu)
    {
        string commande = saisirCommande();

        if(commande == "1")
        {
            jouerNouvellePartie();
        }
        else if(commande == "2")
        {
            afficherHistorique();
        }

        else if(commande == "3")
        {
            parametrer();
        }
        else if(commande == "4")
        {
            afficherLesRegles();
        }
        else if(commande == "0")
        {
            IHM::effacerTout();
            continueLeJeu = false;
        }
    }
}

void Puissance4::jouerNouvellePartie()
{
    IHM::effacerTout();
    std::unique_ptr<Partie> partie(new Partie(&listeJoueurs));
    historique.sauvegarderPartie(partie.get());
    partie->demarrer();
    historique.ajouterVictoire(partie->getVainqueur());
    IHM::attendreRetourMenu();
}

void Puissance4::afficherHistorique()
{
    historique.afficher();
    IHM::attendreRetourMenu();
}

void Puissance4::parametrer()
{
    IHM::afficherParametres();
}

void Puissance4::afficherLesRegles()
{
    IHM::effacerTout();
    IHM::afficherRegles();
    IHM::attendreRetourMenu();
}

string Puissance4::saisirCommande()
{
    IHM::effacerTout();
    IHM::afficherBanniere();
    IHM::afficherMenu();
    string commande = IHM::saisirCommandeDeJeu();
    IHM::effacerLignes();
    return commande;
}