#include "Joueur.h"
#include "Couleur.h"
#include <iostream>

using namespace std;

Joueur::Joueur(string couleur, string nom)
{
}

Joueur::~Joueur()
{
}

string Joueur::getNom() const
{
    return "";
}

Couleur Joueur::getCouleur() const
{
    return this->couleur;
}
