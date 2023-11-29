#include "Plateau.h"
#include "Puissance.h"
#include "Joueur.h"
#include <list>
#include <iostream>

#define NOMBRE_CASE 4

using namespace std;

Plateau::Plateau(int lignes, int colonnes) :
    lignes(lignes), colonnes(colonnes), plateaux(lignes * colonnes), vainqueur(nullptr)
{
}

void Plateau::afficherPlateau() const
{
}

void Plateau::afficherPartie() const
{
    this->afficherPlateau();
    //thomas c'est là qu'il faut afficher le gagnant
}

Joueur* Plateau::getVainqueur()
{
    return nullptr;
}

bool Plateau::estUneSequence(int indiceCase, Joueur* case_) const
{
    return false;
}

bool Plateau::testerSequence(int indiceCase, Joueur* case_, int indiceCaseTeste) const
{
    return false;
}

int Plateau::getNbLignes() const
{
    return 0;
}

int Plateau::getNbColonnes() const
{
    return 0;
}

vector<Joueur*>* Plateau::getPlateau()
{
    return nullptr;
}