#include "Historique.h"
#include "Joueur.h"
#include "Partie.h"
#include "Jeton.h"
#include "Ihm.h"

using namespace std;

Historique::Historique() : parties({}), points({})
{
}

Historique::Historique(const Historique& historique) :
    parties(historique.parties), points(historique.points)
{
}

Historique::Historique(Historique&& historique) noexcept :
    parties(std::move(historique.parties)),
    points(std::move(historique.points))
{
}

Historique::~Historique()
{
    for(vector<Partie*>::iterator it = parties.begin(); it != parties.end(); ++it)
    {
        delete *it;
    }
}

Historique& Historique::operator=(const Historique& historique) noexcept
{
    if(this != &historique)
    {
        parties = historique.parties;
        points  = historique.points;
    }
    return *this;
}

Historique& Historique::operator=(Historique&& historique) noexcept
{
    if(this != &historique)
    {
        parties = historique.parties;
        points  = historique.points;
    }
    return *this;
}

void Historique::sauvegarderPartie(Partie* partie)
{
    parties.push_back(partie);
}

void Historique::ajouterVictoire(Joueur* joueur)
{
    points[joueur]++;
}

void Historique::afficher()
{
    if((int)parties.size() == 0)
    {
        IHM::afficherTexte("Historique vide.\n");
        return;
    }

    IHM::afficherTexte("Nombre de parties jouée(s) : " + to_string(parties.size()) + "\n");

    for(vector<Partie*>::iterator it = parties.begin(); it != parties.end(); ++it)
    {
        Partie* partie = *it;
        Joueur* joueur = partie->getVainqueur();
        if(joueur != nullptr)
        {
            IHM::afficherTexte("Partie n°" + to_string(it - parties.begin() + 1) + " : " +
                               getSequence(joueur->getJeton(), joueur->getNom()) + " vainqueur\n");
        }
    }

    IHM::afficherTexte("Points par joueurs : \n");

    for(map<Joueur*, int>::iterator it = points.begin(); it != points.end(); ++it)
    {
        Joueur* joueur       = it->first;
        int     pointsJoueur = it->second;
        IHM::afficherTexte(getSequence(joueur->getJeton(), joueur->getNom()) + " : " +
                           to_string(pointsJoueur) + " point(s)\n");
    }
}
