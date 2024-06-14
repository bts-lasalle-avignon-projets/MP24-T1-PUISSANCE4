#ifndef DIFFICULTE_H
#define DIFFICULTE_H

#include <string>

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
int         getIndice(Difficulte difficulte);

#endif // DIFFICULTE_H
