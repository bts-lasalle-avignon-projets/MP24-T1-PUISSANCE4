#include "Joueur.h"
#include "Jeton.h"
#include <iostream>

using namespace std;

Joueur::Joueur() : couleur(JETON(VIDE)), nom("")
{
}

Joueur::Joueur(Jeton couleur, const string& nom) : couleur(couleur), nom(nom)
{
}

Joueur::Joueur(const Joueur& joueur) : couleur(joueur.couleur), nom(joueur.nom)
{
}

Joueur::Joueur(Joueur&& joueur) noexcept : couleur(joueur.couleur), nom(std::move(joueur.nom))
{
}

Joueur::~Joueur()
{
}

Joueur& Joueur::operator=(const Joueur& joueur) noexcept
{
    if(&joueur != this)
    {
        this->couleur = joueur.couleur;
        this->nom     = joueur.nom;
    }
    return *this;
}

Joueur& Joueur::operator=(Joueur&& joueur) noexcept
{
    this->couleur = joueur.couleur;
    this->nom     = joueur.nom;
    return *this;
}

string Joueur::getNom() const
{
    return this->nom;
}

Jeton Joueur::getJeton() const
{
    return this->couleur;
}
