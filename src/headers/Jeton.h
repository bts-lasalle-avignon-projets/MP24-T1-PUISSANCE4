#ifndef JETON
#define JETON

#include <string>

enum Jeton
{
    VIDE,
    ROUGE,
    JAUNE
};

std::string getSequence(Jeton couleur, const std::string& contenu);
std::string getCouleur(Jeton jeton);
Jeton       getJetonDepuisIndice(int indice);

#endif // JETON_H
