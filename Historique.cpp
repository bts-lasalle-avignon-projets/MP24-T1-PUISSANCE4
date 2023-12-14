#include "Historique.h"
#include <iostream>
#include <vector>
#include <map>

#include "Joueur.h"
#include "Puissance.h"
#include "Jeton.h"
#include "Ihm.h"

using namespace std;

Historique::Historique(vector<Joueur>& listeJoueurs) : parties(), points()
{
    for(int i = 0; i < (int)listeJoueurs.size(); i++)
    {
        Joueur joueur  = listeJoueurs[i];
        points[joueur] = 0;
    }
}

Historique::~Historique()
{
    for(Puissance* puissance: parties)
    {
        delete puissance;
    }
}

void Historique::savegarderPartie(Puissance* puissance)
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