#ifndef JETON
#define JETON

#include <iostream>

enum Jeton
{
    VIDE,
    ROUGE,
    JAUNE
};

std::string getSequence(Jeton couleur);

#endif // JETON