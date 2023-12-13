#include "Jeton.h"
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
