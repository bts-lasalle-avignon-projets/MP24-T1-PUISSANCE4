#include "Plateau.h"
#include "Puissance.h"
#include "Joueur.h"
#include <list>
#include <iostream>

#define NOMBRE_CASE 4

using namespace std;

Plateau::Plateau(int lignes, int colonnes) :
    lignes(lignes), colonnes(colonnes), plateaux(lignes * colonnes), vainqueur(nullptr)
{
}

void Plateau::afficherPlateau() const
{
    for(int i = 0; i < this->lignes; i++)
    {
        cout << "|";
        for(int j = 0; j < this->colonnes; j++)
        {
            Joueur* joueur = this->plateaux.at(i * this->colonnes + j);
            if(joueur == nullptr)
            {
                cout << " |";
            }
            else
            {
                cout << getSequence(joueur->getCouleur()) << "|";
            }
        }
        cout << endl;
    }
}

void Plateau::afficherPartie() const
{
    this->afficherPlateau();
    // thomas c'est là qu'il faut afficher le gagnant
}

Joueur* Plateau::getVainqueur()
{
    for(int i = this->lignes - 1; i >= 0; i--)
    {
        for(int j = 0; j < this->colonnes; j++)
        {
            Joueur* case_ = this->plateaux.at(i * this->colonnes + j);
            if(this->estUneSequence(i * this->colonnes + j, case_))
            {
                return case_;
            }
        }
    }
    return nullptr;
}

bool Plateau::estUneSequence(int indiceCase, Joueur* case_) const
{
    if(case_ == nullptr)
        return false;
    bool sequenceHorizontale     = testerSequence(indiceCase, case_, 1);
    bool sequenceVerticale       = testerSequence(indiceCase, case_, this->colonnes);
    bool sequenceDiagonaleGauche = testerSequence(indiceCase, case_, this->colonnes - 1);
    bool sequenceDiagonaleDroite = testerSequence(indiceCase, case_, this->colonnes + 1);
    return sequenceHorizontale || sequenceVerticale || sequenceDiagonaleGauche ||
           sequenceDiagonaleDroite;
}

bool Plateau::testerSequence(int indiceCase, Joueur* case_, int indiceCaseTeste) const
{
    for(int i = 0; i < NOMBRE_CASE; i++)
    {
        int prochainIndiceTest = indiceCase + i * indiceCaseTeste;
        if(prochainIndiceTest < 0 || prochainIndiceTest >= (int)this->plateaux.size())
        {
            return false;
        }
        if(this->plateaux.at(prochainIndiceTest) != case_)
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

vector<Joueur*>* Plateau::getPlateau()
{
    return &plateaux;
}