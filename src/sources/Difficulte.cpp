#include "Difficulte.h"

#include <random>

using namespace std;

constexpr int nombreDeChanceFacile       = 1;
constexpr int nombreDePossibilitesFacile = 3;

constexpr int nombreDeChanceNormal       = 3;
constexpr int nombreDePossibilitesNormal = 5;

constexpr int nombreDeChanceDifficile       = 5;
constexpr int nombreDePossibilitesDifficile = 6;

bool necessiteUnBonCoup(Difficulte difficulte)
{
    int nombreDeChance       = 0;
    int nombreDePossibilites = 0;

    switch(difficulte)
    {
        case FACILE:
            nombreDeChance       = nombreDeChanceFacile;
            nombreDePossibilites = nombreDePossibilitesFacile;
            break;
        case NORMAL:
            nombreDeChance       = nombreDeChanceNormal;
            nombreDePossibilites = nombreDePossibilitesNormal;
            break;
        case DIFFICILE:
            nombreDeChance       = nombreDeChanceDifficile;
            nombreDePossibilites = nombreDePossibilitesDifficile;
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

int getIndice(Difficulte difficulte)
{
    switch(difficulte)
    {
        case FACILE:
            return 1;
        case NORMAL:
            return 2;
        case DIFFICILE:
            return 3;
        case EPIQUE:
            return 4;
    }
    return 0;
}