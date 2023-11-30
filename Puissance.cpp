#include "Puissance.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Jeton.h"
#include "Ihm.h"
#include <vector>
#include <iostream>

using namespace std;

Puissance::Puissance() : indiceJoueurActuel(-1), listeJoueurs(nullptr), plateau(nullptr, 0, 0)
{
}

Puissance::Puissance(vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes) :
    indiceJoueurActuel(-1), listeJoueurs(listeJoueurs), plateau(this, nbLignes, nbColonnes)
{
}

Puissance::Puissance(const Puissance& puissance) :
    indiceJoueurActuel(puissance.indiceJoueurActuel), listeJoueurs(puissance.listeJoueurs),
    plateau(this, puissance.plateau.getNbLignes(), puissance.plateau.getNbColonnes())
{
}

Puissance::Puissance(Puissance&& puissance) noexcept :
    indiceJoueurActuel(puissance.indiceJoueurActuel),
    listeJoueurs(puissance.listeJoueurs),
    plateau(this, puissance.plateau.getNbLignes(), puissance.plateau.getNbColonnes())
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
    while(!this->partieEstTerminee())
    {
        this->plateau.afficherPlateau();
        this->jouerTour();
    }

    this->plateau.afficherPartie();
}
void Puissance::jouerTour()
{
    int prochainIndice = this->indiceJoueurActuel + 1 == (int)this->listeJoueurs->size()
                           ? 0
                           : this->indiceJoueurActuel + 1;

    indiceJoueurActuel = prochainIndice;
    IHM::afficherMessageTour(listeJoueurs->at(prochainIndice));

    int indice = 0;
    cin >> indice;

    for(int i = this->plateau.getNbLignes() - 1; i >= 0; i--)
    {
        if(this->plateau.getPlateau()->at(i * this->plateau.getNbColonnes() + indice - 1) ==
           Jeton(VIDE))
        {
            this->plateau.getPlateau()->at(i * this->plateau.getNbColonnes() + indice - 1) =
              listeJoueurs->at(prochainIndice).getJeton();
            break;
        }
    }
}

bool Puissance::partieEstTerminee()
{
    return this->plateau.getVainqueur() != nullptr;
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