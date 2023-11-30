#ifndef COULEUR
#define COULEUR

#include <iostream>

enum Couleur
{
    ROUGE, JAUNE
};

std::string getSequence(Couleur couleur);

#endif // COULEUR