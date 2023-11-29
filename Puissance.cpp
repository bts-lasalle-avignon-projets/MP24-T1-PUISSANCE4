#include "Puissance.h"
#include "Plateau.h"
#include "Joueur.h"
#include <vector>
#include <iostream>

using namespace std;

Puissance::Puissance(vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes): plateau(nbLignes, nbColonnes)
{
}

Puissance::~Puissance()
{
}

void Puissance::demarrerPartie()
{
}
void Puissance::jouerTour()
{
}

bool Puissance::partieEstTerminee()
{
    return false;
}