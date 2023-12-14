#include "Joueur.h"
#include "Jeton.h"
#include "IA.h"
#include "Plateau.h"
#include "Ihm.h"
#include <iostream>

using namespace std;

Joueur::Joueur() : couleur(JETON(VIDE)), nom(""), ia(nullptr)
{
}

Joueur::Joueur(Jeton couleur, const string& nom, IA* ia) : couleur(couleur), nom(nom), ia(ia)
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

bool Joueur::operator<(const Joueur& joueur) const
{
    return this->nom < joueur.nom;
}

int Joueur::jouerCoup(Plateau& plateau)
{
    if(estUneIA())
    {
        return getObjetIA()->jouerCoup() % plateau.getNbColonnes() + 1;
    }
    int indice = 0;
    while(indice < 1 || indice > plateau.getNbColonnes() || plateau.colonneEstPleine(indice - 1))
    {
        cin >> indice;
        IHM::effacerSaisie();
    }
    return indice;
}

bool Joueur::estUneIA()
{
    return this->ia != nullptr;
}

IA* Joueur::getObjetIA()
{
    return this->ia;
}