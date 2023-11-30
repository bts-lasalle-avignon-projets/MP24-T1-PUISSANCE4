#include "Joueur.h"
#include "Couleur.h"
#include <iostream>

using namespace std;

Joueur::Joueur(Couleur couleur, string nom) : couleur(couleur), nom(nom)
{
}

Joueur::~Joueur()
{
}

string Joueur::getNom() const
{
    return this->nom;
}

Couleur Joueur::getCouleur() const
{
    return this->couleur;
}
