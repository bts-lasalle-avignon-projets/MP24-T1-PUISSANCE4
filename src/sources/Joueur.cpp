#include "../headers/Joueur.h"
#include "../headers/Jeton.h"
#include "../headers/IA.h"
#include "../headers/Plateau.h"
#include "../headers/Ihm.h"
#include <iostream>

using namespace std;

Joueur::Joueur() : couleur(JETON(VIDE)), nom(""), ia(false)
{
}

Joueur::Joueur(Jeton couleur, const string& nom, bool ia) : couleur(couleur), nom(nom), ia(ia)
{
}

Joueur::Joueur(const Joueur& joueur) : couleur(joueur.couleur), nom(joueur.nom), ia(joueur.ia)
{
}

Joueur::Joueur(Joueur&& joueur) noexcept :
    couleur(joueur.couleur),
    nom(std::move(joueur.nom)),
    ia(joueur.ia)
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
        this->ia      = joueur.ia;
    }
    return *this;
}

Joueur& Joueur::operator=(Joueur&& joueur) noexcept
{
    this->couleur = joueur.couleur;
    this->nom     = joueur.nom;
    this->ia      = joueur.ia;
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

void Joueur::setJeton(Jeton jeton)
{
    this->couleur = jeton;
}

bool Joueur::operator<(const Joueur& joueur) const
{
    return this->nom < joueur.nom;
}

int Joueur::jouerCoup(Plateau& plateau)
{
    return 0;
}

bool Joueur::estUneIA() const
{
    return this->ia;
}