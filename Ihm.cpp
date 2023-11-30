// Ihm.cpp
#include "Ihm.h"
#include "Joueur.h"
#include <iostream>

std::string IHM::saisieNomJoueur(int numeroJoueur)
{
    std::string nom;
    std::cout << "Entrez le nom/pseudo du Joueur " << numeroJoueur << ": ";
    std::cin >> nom;
    return nom;
}

void IHM::afficherMessageTour(const Joueur& joueur)
{
    std::cout << "C'est au tour de " << joueur.getNom() << " de jouer !" << std::endl;
}

void IHM::afficherVictoire(Joueur* joueur)
{
    std::cout << joueur->getNom() << " remporte la partie !" << std::endl;
}