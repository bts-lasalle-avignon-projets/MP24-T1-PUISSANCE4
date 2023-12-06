#include "Jeton.h"

using namespace std;

string getSequence(Jeton couleur)
{
    switch(couleur)
    {
        case ROUGE:
            return "\033[1;31m\u25CF\033[0m";
        case JAUNE:
            return "\033[1;33m\u25CF\033[0m";
        default:
            return "\033[0m\u25CF\033[0m";
    }
}
