#include "Puissance.h"
#include "Plateau.h"
#include "Joueur.h"
#include "Couleur.h"
#include <vector>
#include <iostream>

using namespace std;

Puissance::Puissance(vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes) :
    indiceJoueurActuel(-1), listeJoueurs(listeJoueurs), plateau(nbLignes, nbColonnes)
{
}

Puissance::~Puissance()
{
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
    int indice;
    cin >> indice;
    for(int i = this->plateau.getNbLignes() - 1; i >= 0; i--)
    {
        if(this->plateau.getPlateau()->at(i * this->plateau.getNbColonnes() + indice) == nullptr)
        {
            this->plateau.getPlateau()->at(i * this->plateau.getNbColonnes() + indice) =
              &(listeJoueurs->at(prochainIndice));
            break;
        }
    }
}

bool Puissance::partieEstTerminee()
{
    return this->plateau.getVainqueur() != nullptr;
}