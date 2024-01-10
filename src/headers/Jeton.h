#ifndef JETON_H
#define JETON_H

#include <string>

constexpr int NB_JETONS_ALIGNES = 4;

enum Jeton
{
    VIDE = -1,
    ROUGE,
    JAUNE,
    NB_JETONS
};

std::string getSequence(Jeton couleur, const std::string& contenu);
std::string getCouleur(Jeton jeton);

#endif // JETON_H
