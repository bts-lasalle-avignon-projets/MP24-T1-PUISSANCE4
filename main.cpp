#include <iostream>
#include "Joueur.h"
#include "Puissance.h"
#include "Plateau.h"

using namespace std;

int main()
{
    Joueur         joueur1(Jeton(ROUGE), "Joueur1");
    Joueur         joueur2(Jeton(JAUNE), "Joueur2");
    vector<Joueur> listeJoueurs = { joueur1, joueur2 };
    Puissance      puissance(&listeJoueurs, 6, 7);
    puissance.demarrerPartie();
    return 0;
}
