#include "../headers/Jeton.h"
#include <iostream>

using namespace std;

string getSequence(Jeton couleur, const string& contenu)
{
    switch(couleur)
    {
        case ROUGE:
            return "\033[1;31m" + contenu + "\033[0m";
        case JAUNE:
            return "\033[1;33m" + contenu + "\033[0m";
        default:
            return "\033[0m" + contenu + "\033[0m";
    }
}

string getCouleur(Jeton jeton)
{
    switch(jeton)
    {
        case ROUGE:
            return "\033[1;31m";
        case JAUNE:
            return "\033[1;33m";
        default:
            return "\033[0m";
    }
}

Jeton getJetonDepuisIndice(int indice)
{
    switch(indice)
    {
        case 0:
            return Jeton(VIDE);
        case 1:
            return Jeton(ROUGE);
        case 2:
            return Jeton(JAUNE);
    }
    return JETON(VIDE);
}
