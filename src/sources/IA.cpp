#include "IA.h"
#include "Plateau.h"
#include "Partie.h"
#include "Parametres.h"
#include "Difficulte.h"

#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

IA::IA() : plateau(nullptr)
{
}

IA::IA(Jeton jeton, const string& nom) : Joueur(jeton, nom), plateau(nullptr)
{
}

IA::IA(const IA& ia) : Joueur(ia), plateau(ia.plateau)
{
}

IA::IA(IA&& ia) noexcept : Joueur(std::move(ia)), plateau(ia.plateau)
{
}

IA::~IA()
{
}

std::vector<int> IA::analyserCoupsVainqueurAdversaire()
{
    for(Joueur* joueur: *(this->plateau->getPartie()->getJoueurs()))
    {
        if(joueur->getJeton() != this->getJeton())
        {
            vector<int> coups = analyserSequence(joueur->getJeton(), NB_JETONS_ALIGNES);
            if(!coups.empty())
            {
                return coups;
            }
        }
    }

    vector<int> coups(0);
    return coups;
}

vector<int> IA::analyserSequence(Jeton jeton, int nbJetons)
{
    vector<int> coups;
    Plateau     plateauTemporaire(*plateau);

    for(int i = 0; i < plateauTemporaire.getNbColonnes(); i++)
    {
        if(plateauTemporaire.colonneEstPleine(i))
        {
            continue;
        }

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
    vector<int>   colonnes = analyserSequence(getJeton(), 1);
    map<int, int> tailleSequenceParPositions;

    for(int indiceColonne: colonnes)
    {
        int positionJeton = plateauTemporaire.placerJeton(indiceColonne + 1, getJeton());
        tailleSequenceParPositions[positionJeton] =
          plateauTemporaire.getNbJetonsAlignes(positionJeton, getJeton());
        plateauTemporaire.supprimerJeton(positionJeton);
    }

    int         maximum = calculerValeurHaute(tailleSequenceParPositions);
    vector<int> emplamentsMeilleursCoups;

    for(map<int, int>::iterator it = tailleSequenceParPositions.begin();
        it != tailleSequenceParPositions.end();
        ++it)
    {
        int indiceCase     = it->first;
        int nbPionsAlignee = it->second;

        if(nbPionsAlignee == maximum)
        {
            emplamentsMeilleursCoups.push_back(indiceCase);
        }
    }
    return emplamentsMeilleursCoups;
}

int IA::calculerValeurHaute(std::map<int, int>& tailleSequenceParPositions)
{
    int maximum = 0;
    for(map<int, int>::iterator it = tailleSequenceParPositions.begin();
        it != tailleSequenceParPositions.end();
        ++it)
    {
        int nbPionsAlignee = it->second;
        if(nbPionsAlignee > maximum)
        {
            maximum = nbPionsAlignee;
        }
    }
    return maximum;
}

int IA::jouerCoup(Plateau& plateau)
{
    this->plateau = &plateau;
    Plateau      plateauTemporaire(plateau);
    vector<int>  coupsAdverse = analyserCoupsVainqueurAdversaire();
    vector<int>  coups        = analyserCoups(plateauTemporaire);
    vector<int>* coupsFinal   = nullptr;

    if(!coupsAdverse.empty())
    {
        if(!coups.empty() && coups.at(0) == NB_JETONS_ALIGNES)
        {
            coupsFinal = &coups;
        }
        else /*if(necessiteUnBonCoup(Parametres::getDifficulte()))*/
        {
            coupsFinal = &coupsAdverse;
        }
    }
    else
    {
        coupsFinal = &coups;
    }

    if(coupsFinal == nullptr || coupsFinal->empty())
    {
        cerr << "Erreur: L'IA n'a pas pu placer de pion" << endl;
        exit(2);
    }

    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> distrib(0, coupsFinal->size() - 1);
    int                             indexAleatoire = distrib(gen);
    return coupsFinal->at(indexAleatoire) % this->plateau->getNbColonnes() + 1;
}
