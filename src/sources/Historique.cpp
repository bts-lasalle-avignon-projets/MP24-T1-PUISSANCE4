// Historique.cpp

#include "Historique.h"
#include "Joueur.h"
#include "Partie.h"
#include "Jeton.h"
#include "Ihm.h"

using namespace std;

Historique::Historique() : points({})
{
}

Historique::Historique(const Historique& historique) : points(historique.points)
{
    for(const auto& partie: historique.parties)
    {
        parties.push_back(std::make_unique<Partie>(*partie));
    }
}

Historique::Historique(Historique&& historique) noexcept :
    parties(move(historique.parties)),
    points(move(historique.points))
{
    historique.parties.clear();
}

Historique::~Historique()
{
}

Historique& Historique::operator=(const Historique& historique) noexcept
{
    if(this != &historique)
    {
        parties.clear();

        for(const auto& partie: historique.parties)
        {
            parties.push_back(std::make_unique<Partie>(*partie));
        }

        points = historique.points;
    }
    return *this;
}

Historique& Historique::operator=(Historique&& historique) noexcept
{
    if(this != &historique)
    {
        parties = move(historique.parties);
        points  = move(historique.points);
        historique.parties.clear();
    }
    return *this;
}

void Historique::sauvegarderPartie(Partie* partie)
{
    parties.push_back(std::make_unique<Partie>(*partie));
}

void Historique::ajouterVictoire(Joueur* joueur)
{
    points[joueur]++;
}

void Historique::afficher()
{
    if(parties.empty())
    {
        IHM::afficherTexte("Historique vide.\n");
        return;
    }

    IHM::afficherTexte("Nombre de parties jouée(s) : " + to_string(parties.size()) + "\n");

    int numPartie = 1;
    for(const auto& partie: parties)
    {
        Joueur* joueur = partie->getVainqueur();
        if(joueur != nullptr)
        {
            IHM::afficherTexte("Partie n°" + to_string(numPartie) + " : " +
                               getSequence(joueur->getJeton(), joueur->getNom()) + " vainqueur\n");
        }
        ++numPartie;
    }

    IHM::afficherTexte("Points par joueurs : \n");

    for(const auto& entry: points)
    {
        Joueur* joueur       = entry.first;
        int     pointsJoueur = entry.second;
        if(joueur != nullptr)
        {
            IHM::afficherTexte(getSequence(joueur->getJeton(), joueur->getNom()) + " : " +
                               to_string(pointsJoueur) + " point(s)\n");
        }
    }
}
