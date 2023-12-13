#include "IA.h"
#include "Joueur.h"
#include "Plateau.h"
#include "Puissance.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>

using namespace std;

IA::IA(Jeton jeton, string nom) : Joueur(jeton, nom, this), partie(nullptr)
{
}

IA::~IA()
{
}

std::vector<int> IA::analyserCoupsVainqueurAdversaire()
{
}

vector<int> IA::analyserSequence(Jeton jeton, int nbJetons)
{
    vector<int> coups;
    Plateau     plateauTemporaire(*partie);
    for(int i = 0; i < plateauTemporaire.getNbColonnes(); i++)
    {
        int positionJeton = plateauTemporaire.placerJeton(i + 1, jeton);
        if(plateauTemporaire.getNbJetonsAlignes(positionJeton, jeton) >= nbJetons)
        {
            coups.push_back(i);
        }
        plateauTemporaire.supprimerJeton(positionJeton);
    }
    return coups;
}

std::vector<int> IA::analyserCoups(Plateau& plateauTemporaire)
{
    return analyserSequence(getJeton(), 1);
}

int IA::calculerValeurHaute(map<int, int>& tailleSequenceParPositions)
{
}

int IA::jouerCoup()
{
    Plateau     plateauTemporaire(*partie);
    vector<int> coups = analyserCoups(plateauTemporaire);

    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> distrib(0, coups.size() - 1);
    int                             indexAleatoire = distrib(gen);
    return coups.at(indexAleatoire);
}

void IA::setPlateau(Plateau* plateau)
{
    this->partie = plateau;
}
