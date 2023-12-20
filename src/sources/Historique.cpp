#include <iostream>
#include <vector>
#include <map>

#include "../headers/Historique.h"
#include "../headers/Joueur.h"
#include "../headers/Puissance.h"
#include "../headers/Jeton.h"
#include "../headers/Ihm.h"

using namespace std;

Historique::Historique() : parties({}), points({})
{
}

Historique::Historique(vector<Joueur>& listeJoueurs) : parties({}), points({})
{
    for(int i = 0; i < (int)listeJoueurs.size(); i++)
    {
        Joueur joueur  = listeJoueurs[i];
        points[joueur] = 0;
    }
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

void Historique::savegarderPartie(Puissance& puissance)
{
    parties.push_back(puissance);
}

void Historique::ajouterVictoire(Joueur* joueur)
{
    points[*joueur]++;
}

void Historique::afficher()
{
    if((int)parties.size() == 0)
    {
        IHM::afficherTexte("Historique vide.\n");
        return;
    }

    IHM::afficherTexte("Nombre de parties jouée(s) : " + to_string(parties.size()) + "\n");
    IHM::afficherTexte("Points par joueurs : \n");

    for(map<Joueur, int>::iterator it = points.begin(); it != points.end(); ++it)
    {
        Joueur joueur       = it->first;
        int    pointsJoueur = it->second;
        IHM::afficherTexte(getSequence(joueur.getJeton(), joueur.getNom()) + " : " +
                           to_string(pointsJoueur) + " point(s)\n");
    }
}