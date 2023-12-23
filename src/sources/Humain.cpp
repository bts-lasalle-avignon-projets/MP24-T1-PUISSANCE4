#include "../headers/humain.h"
#include "../headers/Jeton.h"
#include "../headers/IA.h"
#include "../headers/Plateau.h"
#include "../headers/Ihm.h"
#include <iostream>

using namespace std;

Humain::Humain()
{
    std::cout << "\033[1;44m" << __PRETTY_FUNCTION__ << "\033[0m" << std::endl;
}

Humain::Humain(Jeton couleur, const string& nom) : Joueur(couleur, nom)
{
    std::cout << "\033[1;44m" << __PRETTY_FUNCTION__ << "\033[0m" << std::endl;
}

Humain::Humain(const Humain& humain) : Joueur(humain.getJeton(), humain.getNom())
{
    std::cout << "\033[1;44m" << __PRETTY_FUNCTION__ << "\033[0m" << std::endl;
}

Humain::Humain(Humain&& humain) noexcept : Joueur(humain.getJeton(), humain.getNom())
{
    std::cout << "\033[1;44m" << __PRETTY_FUNCTION__ << "\033[0m" << std::endl;
}

Humain::~Humain()
{
    std::cout << "\033[1;44m" << __PRETTY_FUNCTION__ << "\033[0m" << std::endl;
}

Humain& Humain::operator=(const Humain& humain) noexcept
{
    return *this;
}

Humain& Humain::operator=(Humain&& humain) noexcept
{
    return *this;
}

int Humain::jouerCoup(Plateau& plateau)
{
    int indice = 0;
    while(indice < 1 || indice > plateau.getNbColonnes() || plateau.colonneEstPleine(indice - 1))
    {
        cin >> indice;
        IHM::effacerSaisie();
    }
    return indice;
}