#include "Difficulte.h"
#include <random>
#include <iostream>
#include <string>

using namespace std;

bool necessiteUnBonCoup(Difficulte difficulte)
{
    int nombreDeChance       = 0;
    int nombreDePossibilites = 0;
    switch(difficulte)
    {
        case FACILE:
            nombreDeChance       = 1;
            nombreDePossibilites = 3;
            break;
        case NORMAL:
            nombreDeChance       = 3;
            nombreDePossibilites = 5;
            break;
        case DIFFICILE:
            nombreDeChance       = 5;
            nombreDePossibilites = 6;
            break;
        case EPIQUE:
            return true;
    }
    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> distrib(0, nombreDePossibilites);
    int                             indiceAleatoire = distrib(gen);
    return indiceAleatoire <= nombreDeChance;
}

string getTexte(Difficulte difficulte)
{
    switch(difficulte)
    {
        case FACILE:
            return "Facile";
        case NORMAL:
            return "Normale";
        case DIFFICILE:
            return "Difficle";
        case EPIQUE:
            return "Epique";
    }
    return "";
}

Difficulte getDifficulteIndexe(int indice)
{
    switch(indice)
    {
        case 1:
            return Difficulte(FACILE);
        case 2:
            return Difficulte(NORMAL);
        case 3:
            return Difficulte(DIFFICILE);
        case 4:
            return Difficulte(EPIQUE);
    }
    return Difficulte(NORMAL);
}