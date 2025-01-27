#include "../headers/Historique.h"
#include <iostream>
#include <vector>
#include <map>

#include "../headers/Joueur.h"
#include "../headers/Puissance.h"
#include "../headers/Jeton.h"
#include "../headers/Ihm.h"
#include "../headers/JSON.h"
#include "../headers/Parametres.h"

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
    for(int i = 0; i < (int)parties.size(); i++)
    {
        delete parties[i];
    }
    parties.clear();
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

void Historique::savegarderPartie(Puissance* puissance, bool sauvegardeFichier)
{
    // A VERFIIER
    for(int i = 0; i < (int)puissance->getJoueurs().size(); i++)
    {
        Joueur* joueur = puissance->getJoueurs().at(i);
        puissance->getJoueurs().at(i) =
          new Joueur(joueur->getJeton(), joueur->getNom(), joueur->estUneIA());
    }
    // A VERFIIER
    parties.push_back(puissance);
    if(!sauvegardeFichier)
    {
        return;
    }
    JSON           json("src/historique.json");
    string         indice         = to_string((int)json.getCles("", false).size()) + ".";
    int            nbLignes       = puissance->getPlateau().getNbLignes();
    int            nbColonnes     = puissance->getPlateau().getNbColonnes();
    int            tailleSequence = puissance->getPlateau().getNbPionsAlignement();
    vector<string> pions;
    for(Jeton casePlateau: puissance->getPlateau().getCases())
    {
        pions.push_back(to_string(getIndiceJeton(casePlateau)));
    }
    for(int i = 0; i < (int)puissance->getJoueurs().size(); i++)
    {
        Joueur* joueur      = puissance->getJoueurs().at(i);
        int     indiceJeton = getIndiceJeton(joueur->getJeton());
        json.setInt(indice + "joueurs." + joueur->getNom(), indiceJeton);
    }
    json.setInt(indice + "nbLignes", nbLignes);
    json.setInt(indice + "nbColonnes", nbColonnes);
    json.setInt(indice + "tailleSequence", tailleSequence);
    json.setStringList(indice + "pions", pions);
    json.sauvegarder();
}

void Historique::ajouterVictoire(Joueur* joueur)
{
    if(joueur != nullptr)
    {
        points[joueur]++;
    }
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
    for(map<Joueur*, int>::iterator it = points.begin(); it != points.end(); ++it)
    {
        Joueur* joueur       = it->first;
        int     pointsJoueur = it->second;
        IHM::afficherTexte(getSequence(joueur->getJeton(), joueur->getNom()) + " : " +
                           to_string(pointsJoueur) + " point(s)\n");
    }
    for(Puissance* partie: parties)
    {
        partie->getPlateau().afficherPlateauFinDePartie();
        Joueur* vainqueur    = partie->getVainqueur();
        string  nomVainqueur = getSequence(vainqueur->getJeton(), vainqueur->getNom());
        IHM::afficherTexte("Vainqueur : " + nomVainqueur + "\n");
    }
}

void Historique::charger()
{
    JSON json("src/historique.json");
    for(string indicePartie: json.getCles("", false))
    {
        vector<Joueur*> joueurs    = *new vector<Joueur*>();
        int             nbColonnes = json.getInt(indicePartie + ".nbColonnes");
        int             nbLignes   = json.getInt(indicePartie + ".nbLignes");
        vector<Jeton>   pions;
        int             tailleSequence = json.getInt(indicePartie + ".tailleSequence");
        for(string nomJoueur: json.getCles(indicePartie + ".joueurs", true))
        {
            joueurs.push_back(
              new Joueur(getJetonDepuisIndice(json.getInt(indicePartie + ".joueurs." + nomJoueur)),
                         nomJoueur,
                         false));
        }
        for(string casePlateau: json.getStringList(indicePartie + ".pions"))
        {
            pions.push_back(getJetonDepuisIndice(stoi(casePlateau)));
        }
        Puissance* puissance = new Puissance(joueurs, nbLignes, nbColonnes, pions, tailleSequence);
        savegarderPartie(puissance, false);
    }
    JSON statistiques("src/statistiques.json");
    for(string nomJoueur: statistiques.getCles("", false))
    {
        int     nbPoints = statistiques.getInt(nomJoueur + ".points");
        Joueur* joueur   = Parametres::recupererJoueurParNom(nomJoueur);
        if(joueur != nullptr)
        {
            points[joueur] = nbPoints;
        }
    }
}