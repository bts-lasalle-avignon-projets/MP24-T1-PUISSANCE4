#include "Historique.h"
#include <iostream>
#include <vector>
#include <map>
#include "Joueur.h"
#include "Puissance.h"
#include "Jeton.h"

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
        cout << "Historique vide." << endl;
        return;
    }
    cout << "Nombre de parties jouée(s) : " << parties.size() << endl;
    cout << "Points par joueurs : " << endl;
    for(map<Joueur, int>::iterator it = points.begin(); it != points.end(); ++it)
    {
        Joueur joueur       = it->first;
        int    pointsJoueur = it->second;
        cout << getSequence(joueur.getJeton(), joueur.getNom()) << " : " << pointsJoueur
             << " point(s)" << endl;
    }
}