#include "../headers/Puissance.h"
#include "../headers/Plateau.h"
#include "../headers/Joueur.h"
#include "../headers/Jeton.h"
#include "../headers/Ihm.h"
#include "../headers/IA.h"
#include <vector>
#include <iostream>

using namespace std;

Puissance::Puissance() : indiceJoueurActuel(-1), listeJoueurs(nullptr), plateau(nullptr, 0, 0, 0)
{
}

Puissance::Puissance(vector<Joueur>* listeJoueurs,
                     int             nbLignes,
                     int             nbColonnes,
                     int             nbPionsAlignement) :
    indiceJoueurActuel(-1),
    listeJoueurs(listeJoueurs), plateau(this, nbLignes, nbColonnes, nbPionsAlignement)
{
}

Puissance::Puissance(vector<Joueur>* listeJoueurs,
                     int             nbLignes,
                     int             nbColonnes,
                     vector<Jeton>   cases,
                     int             nbPionsAlignement) :
    indiceJoueurActuel(-1),
    listeJoueurs(listeJoueurs), plateau(this, nbLignes, nbColonnes, cases, nbPionsAlignement)
{
}

Puissance::Puissance(const Puissance& puissance) :
    indiceJoueurActuel(puissance.indiceJoueurActuel), listeJoueurs(puissance.listeJoueurs),
    plateau(this,
            puissance.plateau.getNbLignes(),
            puissance.plateau.getNbColonnes(),
            puissance.plateau.getNbPionsAlignement())
{
}

Puissance::Puissance(Puissance&& puissance) noexcept :
    indiceJoueurActuel(puissance.indiceJoueurActuel),
    listeJoueurs(puissance.listeJoueurs),
    plateau(this,
            puissance.plateau.getNbLignes(),
            puissance.plateau.getNbColonnes(),
            puissance.plateau.getNbPionsAlignement())
{
}

Puissance::~Puissance()
{
}

Puissance& Puissance::operator=(const Puissance& puissance) noexcept
{
    if(&puissance != this)
    {
        this->listeJoueurs       = puissance.listeJoueurs;
        this->indiceJoueurActuel = puissance.indiceJoueurActuel;
        this->plateau            = puissance.plateau;
    }
    return *this;
}

Puissance& Puissance::operator=(Puissance&& puissance) noexcept
{
    this->listeJoueurs       = puissance.listeJoueurs;
    this->indiceJoueurActuel = puissance.indiceJoueurActuel;
    this->plateau            = puissance.plateau;
    return *this;
}

void Puissance::demarrerPartie()
{
    for(Joueur joueur: *listeJoueurs)
    {
        if(joueur.estUneIA())
        {
            joueur.getObjetIA()->setPlateau(&plateau);
        }
    }
    int   indiceJouee = -1;
    Jeton jetonJoueur = Jeton(VIDE);
    while(!this->partieEstTerminee())
    {
        this->plateau.jouerAnimationPionPlacee(indiceJouee, jetonJoueur);
        indiceJoueurActuel   = this->indiceJoueurActuel + 1 == (int)this->listeJoueurs->size()
                                 ? 0
                                 : this->indiceJoueurActuel + 1;
        Joueur joueurSuivant = listeJoueurs->at(indiceJoueurActuel);
        jetonJoueur          = joueurSuivant.getJeton();
        indiceJouee          = this->jouerTour(joueurSuivant);
    }

    this->plateau.afficherPartie();
}
int Puissance::jouerTour(Joueur& joueurSuivant)
{
    IHM::afficherMessageTour(joueurSuivant);
    int indiceColonne = joueurSuivant.jouerCoup(plateau);
    return this->plateau.placerJeton(indiceColonne, joueurSuivant.getJeton());
}

bool Puissance::partieEstTerminee()
{
    return this->plateau.getVainqueur() != nullptr || plateau.estPlein();
}

Joueur* Puissance::recupererJoueurAyantJeton(Jeton jeton)
{
    for(int i = 0; i < (int)this->listeJoueurs->size(); i++)
    {
        Joueur* joueur = &(listeJoueurs->at(i));
        if(joueur->getJeton() == jeton)
        {
            return joueur;
        }
    }
    return nullptr;
}

Joueur* Puissance::getVainqueur() const
{
    return this->plateau.getVainqueur();
}

std::vector<Joueur>* Puissance::getJoueurs() const
{
    return this->listeJoueurs;
}
Plateau Puissance::getPlateau() const
{
    return this->plateau;
}