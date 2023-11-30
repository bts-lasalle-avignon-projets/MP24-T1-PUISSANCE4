#include "Couleur.h"

using namespace std;

string getSequence(Couleur couleur)
{
    switch(couleur)
    {
        case ROUGE:
            return "\033[1;31m\u25CF\033[0m"; // Rouge
        case JAUNE:
            return "\033[1;33m\u25CF\033[0m"; // Jaune
        default:
            return "\033[0m\u25CF\033[0m"; // Réinitialisation de la couleur (par défaut)
    }
}
