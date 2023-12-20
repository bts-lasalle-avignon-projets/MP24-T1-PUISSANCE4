#ifndef DIFFICULTE_H
#define DIFFICULTE_H

#include <iostream>

enum Difficulte
{
    FACILE,
    NORMAL,
    DIFFICILE,
    EPIQUE
};

bool        necessiteUnBonCoup(Difficulte difficulte);
std::string getTexte(Difficulte difficulte);
Difficulte  getDifficulteIndexe(int indice);

#endif // DIFFICULTE_H
