#include "Joueur.h"
#include "Jeton.h"
#include <iostream>

using namespace std;

Joueur::Joueur(Jeton couleur, string nom) : couleur(couleur), nom(nom)
{
}

Joueur::~Joueur()
{
}

string Joueur::getNom() const
{
    return this->nom;
}

Jeton Joueur::getJeton() const
{
    return this->couleur;
}
