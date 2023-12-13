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
std::string getCouleur(Jeton jeton);

#endif // JETON
