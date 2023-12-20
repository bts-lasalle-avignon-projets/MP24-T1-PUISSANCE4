#include "../headers/Plateau.h"
#include "../headers/Puissance.h"
#include "../headers/Joueur.h"
#include "../headers/Jeton.h"
#include "../headers/Ihm.h"
#include <vector>
#include <iostream>
#include <algorithm>
constexpr int nbCases = 4;

using namespace std;

Plateau::Plateau() : lignes(0), colonnes(0), cases(0), partie(nullptr)
{
}

Plateau::Plateau(Puissance* partie, int lignes, int colonnes) :
    lignes(lignes), colonnes(colonnes), cases(lignes * colonnes), partie(partie)
{
}

Plateau::Plateau(const Plateau& plateau) :
    lignes(plateau.getNbLignes()), colonnes(plateau.getNbColonnes()),
    cases(plateau.getNbLignes() * plateau.getNbColonnes()), partie(plateau.partie)
{
    for(int i = 0; i < (int)cases.size(); i++)
    {
        cases[i] = plateau.cases[i];
    }
}

Plateau::Plateau(Plateau&& plateau) noexcept :
    lignes(plateau.getNbLignes()),
    colonnes(plateau.getNbColonnes()),
    cases(plateau.getNbLignes() * plateau.getNbColonnes()),
    partie(plateau.partie)
{
    for(int i = 0; i < (int)cases.size(); i++)
    {
        cases[i] = plateau.cases[i];
    }
}

Plateau::~Plateau()
{
}

Plateau& Plateau::operator=(const Plateau& plateau) noexcept
{
    if(&plateau != this)
    {
        this->lignes   = plateau.lignes;
        this->colonnes = plateau.colonnes;
        this->cases    = plateau.cases;
        this->partie   = plateau.partie;
    }
    return *this;
}

Plateau& Plateau::operator=(Plateau&& plateau) noexcept
{
    this->lignes   = plateau.lignes;
    this->colonnes = plateau.colonnes;
    this->cases    = plateau.cases;
    this->partie   = plateau.partie;
    return *this;
}

int Plateau::placerJeton(int colonneSelectionnee, Jeton jeton)
{
    int indiceTableauJouee = 0;
    for(int i = this->lignes - 1; i >= 0; i--)
    {
        indiceTableauJouee = i * this->colonnes + colonneSelectionnee - 1;
        if(this->cases.at(indiceTableauJouee) == Jeton(VIDE))
        {
            this->cases.at(indiceTableauJouee) = jeton;
            break;
        }
    }
    return indiceTableauJouee;
}

void Plateau::afficherPlateau(int positionNouveauPion) const
{
    IHM::effacerLignes();
    this->afficherNumerosDeColonnes();
    for(int i = 0; i < this->lignes; i++)
    {
        IHM::afficherTexte("\033[4m|");
        for(int j = 0; j < this->colonnes; j++)
        {
            Jeton jeton = this->cases.at(i * this->colonnes + j);
            if(jeton == Jeton(VIDE))
            {
                IHM::afficherTexte(" |");
            }
            else if(positionNouveauPion == i * this->colonnes + j)
            {
                IHM::afficherTexte(getSequence(jeton, "\u25C7") + "|");
            }
            else
            {
                IHM::afficherTexte(getSequence(jeton, "\u25CF") + "|");
            }
        }
        IHM::afficherTexte("\033[0m\n");
    }
}

void Plateau::afficherPlateauFinDePartie() const
{
    IHM::effacerLignes();
    vector<int> positionSequence = this->getPositionDeSequenceVainqueur();
    this->afficherNumerosDeColonnes();
    for(int i = 0; i < this->lignes; i++)
    {
        IHM::afficherTexte("\033[4m|");
        for(int j = 0; j < this->colonnes; j++)
        {
            Jeton jeton = this->cases.at(i * this->colonnes + j);
            if(jeton == Jeton(VIDE))
            {
                IHM::afficherTexte(" |");
            }
            else
            {
                string forme = "\u25CF";
                for(int position: positionSequence)
                {
                    if(position == i * this->colonnes + j)
                    {
                        forme = "\u25C7";
                        break;
                    }
                }
                IHM::afficherTexte(getSequence(jeton, forme) + "|");
            }
        }
        IHM::afficherTexte("\033[0m\n");
    }
}

vector<int> Plateau::getPositionDeSequenceVainqueur() const
{
    vector<int> positions(nbCases);
    bool        estTrouvee = false;
    for(int i = this->lignes - 1; i >= 0 && !estTrouvee; i--)
    {
        for(int j = 0; j < this->colonnes && !estTrouvee; j++)
        {
            Jeton casePlateau = this->cases.at(i * this->colonnes + j);
            int   indiceCase  = i * this->colonnes + j;
            if(casePlateau != Jeton(VIDE) &&
               this->estUneSequence(i * this->colonnes + j, casePlateau))
            {
                if(testerSequence(indiceCase, casePlateau, 1) == nbCases)
                {
                    positions = getPositions(indiceCase, casePlateau, 1);
                }
                else if(testerSequence(indiceCase, casePlateau, this->colonnes) == nbCases)
                {
                    positions = getPositions(indiceCase, casePlateau, this->colonnes);
                }
                else if(testerSequence(indiceCase, casePlateau, this->colonnes + 1) == nbCases)
                {
                    positions = getPositions(indiceCase, casePlateau, this->colonnes + 1);
                }
                else if(testerSequence(indiceCase, casePlateau, this->colonnes - 1) == nbCases)
                {
                    positions = getPositions(indiceCase, casePlateau, this->colonnes - 1);
                }
                else
                {
                    break;
                }
                estTrouvee = true;
            }
        }
    }
    return positions;
}

vector<int> Plateau::getPositions(int indiceCase, Jeton casePlateau, int indiceCaseTeste) const
{
    vector<int> positions;
    for(int i = 0; i < nbCases; i++)
    {
        int prochainIndiceTest = indiceCase + i * indiceCaseTeste;
        if(cases.at(prochainIndiceTest) == casePlateau)
        {
            positions.push_back(prochainIndiceTest);
        }
    }
    return positions;
}

void Plateau::afficherNumerosDeColonnes() const
{
    IHM::afficherTexte("\033[4m|");
    for(int i = 0; i < this->colonnes; i++)
    {
        IHM::afficherTexte(to_string(i + 1) + "|");
    }
    IHM::afficherTexte("\033[0m\n");
}

void Plateau::afficherPartie() const
{
    afficherPlateauFinDePartie();
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
    return estUneSequence(indiceCase, casePlateau, nbCases);
}

bool Plateau::estUneSequence(int indiceCase, Jeton casePlateau, int nbJetonsAaligner) const
{
    if(casePlateau == Jeton(VIDE))
    {
        return false;
    }

    bool sequenceHorizontale = testerSequence(indiceCase, casePlateau, 1) == nbJetonsAaligner;
    bool sequenceVerticale =
      testerSequence(indiceCase, casePlateau, this->colonnes) == nbJetonsAaligner;
    bool sequenceDiagonaleGauche =
      testerSequence(indiceCase, casePlateau, this->colonnes + 1) == nbJetonsAaligner;
    bool sequenceDiagonaleDroite =
      testerSequence(indiceCase, casePlateau, this->colonnes - 1) == nbJetonsAaligner;

    return sequenceHorizontale || sequenceVerticale || sequenceDiagonaleGauche ||
           sequenceDiagonaleDroite;
}

int Plateau::testerSequence(int indiceCase, Jeton casePlateau, int indiceCaseTeste) const
{
    bool        alignementHorizontal = indiceCaseTeste == 1 || indiceCaseTeste == -1;
    int         nbAlignement         = 0;
    vector<int> positionsCasesDeSequence;
    for(int i = 0; i < nbCases; i++)
    {
        int prochainIndiceTest = indiceCase + i * indiceCaseTeste;
        positionsCasesDeSequence.push_back(prochainIndiceTest);
        if(prochainIndiceTest < 0 || prochainIndiceTest >= (int)this->cases.size() ||
           this->cases.at(prochainIndiceTest) != casePlateau ||
           !sequenceEstDansSonAxe(positionsCasesDeSequence, alignementHorizontal))
        {
            break;
        }

        nbAlignement++;
    }
    return nbAlignement;
}

bool Plateau::sequenceEstDansSonAxe(vector<int> indicesSequence, bool alignementHorizontal) const
{
    int indiceLigneTeste =
      (indicesSequence.at(0) - (indicesSequence.at(0) % this->colonnes)) / this->colonnes;
    for(int indiceCase: indicesSequence)
    {
        int indiceLigneCase = (indiceCase - (indiceCase % this->colonnes)) / this->colonnes;
        if(indiceLigneCase != indiceLigneTeste)
        {
            return false;
        }
        if(!alignementHorizontal)
        {
            indiceLigneTeste++;
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

Puissance* Plateau::getPartie()
{
    return this->partie;
}

void Plateau::supprimerJeton(int indiceJeton)
{
    this->cases.at(indiceJeton) = Jeton(VIDE);
}

int Plateau::getNbJetonsAlignes(int positionJeton, Jeton jeton)
{
    int nombreJetonComptes = 0;
    for(int i = this->lignes - 1; i >= 0; i--)
    {
        for(int j = 0; j < this->colonnes; j++)
        {
            int   indiceCase  = i * this->colonnes + j;
            Jeton casePlateau = this->cases.at(indiceCase);
            if(jeton == casePlateau && this->estUneSequence(indiceCase, casePlateau, 1))
            {
                int nbJetonsHorizontale     = testerSequence(indiceCase, jeton, 1);
                int nbJetonsVerticale       = testerSequence(indiceCase, jeton, this->colonnes);
                int nbJetonsDiagonaleGauche = testerSequence(indiceCase, jeton, this->colonnes + 1);
                int nbJetonsDiagonaleDroite = testerSequence(indiceCase, jeton, this->colonnes - 1);

                int maximum = std::max({ nbJetonsHorizontale,
                                         nbJetonsVerticale,
                                         nbJetonsDiagonaleGauche,
                                         nbJetonsDiagonaleDroite });
                if(maximum > nombreJetonComptes)
                {
                    nombreJetonComptes = maximum;
                }
            }
        }
    }
    return nombreJetonComptes;
}

bool Plateau::estPlein() const
{
    for(int i = 0; i < this->colonnes; i++)
    {
        if(!colonneEstPleine(i))
        {
            return false;
        }
    }
    return true;
}

bool Plateau::colonneEstPleine(int colonne) const
{
    return cases.at(colonne) != JETON(VIDE);
}
