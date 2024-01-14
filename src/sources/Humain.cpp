#include "Humain.h"
#include "Jeton.h"
#include "Plateau.h"
#include "Ihm.h"

using namespace std;

Humain::Humain()
{
}

Humain::Humain(Jeton couleur, const string& nom) : Joueur(couleur, nom)
{
}

Humain::Humain(const Humain& humain) : Joueur(humain)
{
}

Humain::Humain(Humain&& humain) noexcept : Joueur(std::move(humain))
{
}

Humain::~Humain()
{
}

Humain& Humain::operator=(const Humain& humain)
{
    if(this != &humain)
    {
        Joueur::operator=(humain);
    }
    return *this;
}

Humain& Humain::operator=(Humain&& humain) noexcept
{
    if(this != &humain)
    {
        Joueur::operator=(std::move(humain));
    }
    return *this;
}

int Humain::jouerCoup(Plateau& plateau)
{
    int indice = 0;
    while(indice < 1 || indice > plateau.getNbColonnes() || plateau.colonneEstPleine(indice - 1))
    {
        indice = IHM::saisirCoup();
    }
    return indice;
}
