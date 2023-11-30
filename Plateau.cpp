#include "Plateau.h"
#include "Puissance.h"
#include "Joueur.h"
#include "Jeton.h"
#include "Ihm.h"
#include <list>
#include <iostream>

#define NOMBRE_CASE 4

using namespace std;

Plateau::Plateau(Puissance* partie, int lignes, int colonnes) :
    lignes(lignes), colonnes(colonnes), cases(lignes * colonnes), partie(partie)
{
}

void Plateau::afficherPlateau() const
{
    for(int i = 0; i < this->lignes; i++)
    {
        cout << "|";
        for(int j = 0; j < this->colonnes; j++)
        {
            Jeton jeton = this->cases.at(i * this->colonnes + j);
            if(jeton == Jeton(VIDE))
            {
                cout << " |";
            }
            else
            {
                cout << getSequence(jeton) << "|";
            }
        }
        cout << endl;
    }
}

void Plateau::afficherPartie() const
{
    this->afficherPlateau();
    IHM::afficherVictoire(this->getVainqueur());
}

Joueur* Plateau::getVainqueur() const
{
    for(int i = this->lignes - 1; i >= 0; i--)
    {
        for(int j = 0; j < this->colonnes; j++)
        {
            Jeton casePlateau = this->cases.at(i * this->colonnes + j);
            if(this->estUneSequence(i * this->colonnes + j, casePlateau))
            {
                return this->partie->recupererJoueurAyantJeton(casePlateau);
            }
        }
    }
    return nullptr;
}

bool Plateau::estUneSequence(int indiceCase, Jeton casePlateau) const
{
    if(casePlateau == Jeton(VIDE))
        return false;
    bool sequenceHorizontale     = testerSequence(indiceCase, casePlateau, 1);
    bool sequenceVerticale       = testerSequence(indiceCase, casePlateau, this->colonnes);
    bool sequenceDiagonaleGauche = testerSequence(indiceCase, casePlateau, this->colonnes - 1);
    bool sequenceDiagonaleDroite = testerSequence(indiceCase, casePlateau, this->colonnes + 1);
    return sequenceHorizontale || sequenceVerticale || sequenceDiagonaleGauche ||
           sequenceDiagonaleDroite;
}

bool Plateau::testerSequence(int indiceCase, Jeton casePlateau, int indiceCaseTeste) const
{
    for(int i = 0; i < NOMBRE_CASE; i++)
    {
        int prochainIndiceTest = indiceCase + i * indiceCaseTeste;
        if(prochainIndiceTest < 0 || prochainIndiceTest >= (int)this->cases.size())
        {
            return false;
        }
        if(this->cases.at(prochainIndiceTest) != casePlateau)
        {
            return false;
        }
    }
    return true;
}

int Plateau::getNbLignes() const
{
    return this->lignes;
}

int Plateau::getNbColonnes() const
{
    return this->colonnes;
}

vector<Jeton>* Plateau::getPlateau()
{
    return &cases;
}