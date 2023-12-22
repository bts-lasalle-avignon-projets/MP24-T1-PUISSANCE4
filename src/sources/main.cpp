#include "../headers/Ihm.h"
#include "../headers/Parametres.h"
#include "../headers/JSON.h"

using namespace std;

int main()
{
    /*JSON json("src/historique.json");
    json.sauvegarder();*/
    Parametres::chargerParametres();
    IHM::initialiserJeu();
    return 0;
}
