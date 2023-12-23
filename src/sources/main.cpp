#include "../headers/Ihm.h"
#include "../headers/Parametres.h"

using namespace std;

int main()
{
    Parametres::chargerParametres();
    IHM::initialiserJeu();

    Parametres::sortie();
    return 0;
}
