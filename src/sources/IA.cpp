#include "../headers/IA.h"
#include "../headers/Joueur.h"
#include "../headers/Plateau.h"
#include "../headers/Puissance.h"
#include "../headers/Parametres.h"
#include "../headers/Difficulte.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>

using namespace std;

IA::IA()
{
}

IA::IA(Jeton jeton, const string& nom) : Joueur(jeton, nom, true)
{
}

IA::IA(const IA& ia) : Joueur(ia)
{
}

IA::IA(IA&& ia) noexcept : Joueur(std::move(ia))
{
}

IA::~IA()
{
}

IA& IA::operator=(const IA& ia) noexcept
{
    return *this;
}

IA& IA::operator=(IA&& ia) noexcept
{
    return *this;
}

std::vector<int> IA::analyserCoupsVainqueurAdversaire(Plateau& plateau)
{
    for(Joueur* joueur: plateau.getPartie()->getJoueurs())
    {
        if(joueur->getJeton() != this->getJeton())
        {
            vector<int> coups =
              analyserSequence(joueur->getJeton(), plateau.getNbPionsAlignement(), plateau);
            if(!coups.empty())
            {
                return coups;
            }
        }
    }
    vector<int> coups(0);
    return coups;
}

vector<int> IA::analyserSequence(Jeton jeton, int nbJetons, Plateau& plateau)
{
    vector<int> coups;
    Plateau     plateauTemporaire(plateau);
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

std::vector<int> IA::analyserCoups(Plateau& plateau)
{
    vector<int>   colonnes = analyserSequence(getJeton(), 1, plateau);
    Plateau       plateauTemporaire(plateau);
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

int IA::calculerValeurHaute(map<int, int>& tailleSequenceParPositions)
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
    vector<int>  coupsAdverse = analyserCoupsVainqueurAdversaire(plateau);
    vector<int>  coups        = analyserCoups(plateau);
    vector<int>* coupsFinal   = nullptr;

    if(!coupsAdverse.empty())
    {
        if(!coups.empty() && coups.at(0) == plateau.getNbPionsAlignement())
        {
            coupsFinal = &coups;
        }
        else if(necessiteUnBonCoup(Parametres::getDifficulte()))
        {
            coupsFinal = &coupsAdverse;
        }
        else
        {
            coupsFinal = &coups;
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
    return coupsFinal->at(indexAleatoire) % plateau.getNbColonnes() + 1;
}