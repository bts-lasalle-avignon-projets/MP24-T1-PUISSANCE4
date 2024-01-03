#include "Puissance.h"
#include "Joueur.h"
#include "Ihm.h"
#include "IA.h"

using namespace std;

Puissance::Puissance(std::vector<Joueur>* listeJoueurs /*= nullptr*/) :
    indiceJoueurActuel(INDICE_JOUEUR_NON_DEFINI), listeJoueurs(listeJoueurs), plateau(this)
{
}

Puissance::Puissance(vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes) :
    indiceJoueurActuel(INDICE_JOUEUR_NON_DEFINI), listeJoueurs(listeJoueurs),
    plateau(this, nbLignes, nbColonnes)
{
}

Puissance::Puissance(const Puissance& puissance) :
    indiceJoueurActuel(puissance.indiceJoueurActuel), listeJoueurs(puissance.listeJoueurs),
    plateau(this, puissance.plateau.getNbLignes(), puissance.plateau.getNbColonnes())
{
}

Puissance::Puissance(Puissance&& puissance) noexcept :
    indiceJoueurActuel(puissance.indiceJoueurActuel),
    listeJoueurs(puissance.listeJoueurs),
    plateau(this, puissance.plateau.getNbLignes(), puissance.plateau.getNbColonnes())
{
}

Puissance::~Puissance()
{
}

Puissance& Puissance::operator=(const Puissance& puissance) noexcept
{
    if(&puissance != this)
    {
        this->listeJoueurs       = puissance.listeJoueurs;
        this->indiceJoueurActuel = puissance.indiceJoueurActuel;
        this->plateau            = puissance.plateau;
    }
    return *this;
}

Puissance& Puissance::operator=(Puissance&& puissance) noexcept
{
    this->listeJoueurs       = puissance.listeJoueurs;
    this->indiceJoueurActuel = puissance.indiceJoueurActuel;
    this->plateau            = puissance.plateau;
    return *this;
}

void Puissance::demarrerPartie()
{
    for(Joueur joueur: *listeJoueurs)
    {
        if(joueur.estUneIA())
        {
            joueur.getObjetIA()->setPlateau(&plateau);
        }
    }

    int indiceJouee = -1;
    while(!this->partieEstTerminee())
    {
        this->plateau.afficherPlateau(indiceJouee);
        indiceJouee = this->jouerTour();
    }

    this->plateau.afficherPartie();
}

int Puissance::jouerTour()
{
    size_t prochainIndice = (this->indiceJoueurActuel + 1) % this->listeJoueurs->size();
    indiceJoueurActuel    = prochainIndice;
    Joueur joueurSuivant  = listeJoueurs->at(prochainIndice);
    IHM::afficherMessageTour(joueurSuivant);
    int indiceColonne = joueurSuivant.jouerCoup(plateau);
    return this->plateau.placerJeton(indiceColonne, joueurSuivant.getJeton());
}

bool Puissance::partieEstTerminee()
{
    return this->plateau.getVainqueur() != nullptr;
}

Joueur* Puissance::recupererJoueurAyantJeton(Jeton jeton)
{
    for(int i = 0; i < (int)this->listeJoueurs->size(); i++)
    {
        Joueur* joueur = &(listeJoueurs->at(i));
        if(joueur->getJeton() == jeton)
        {
            return joueur;
        }
    }
    return nullptr;
}

Joueur* Puissance::getVainqueur() const
{
    return this->plateau.getVainqueur();
}

std::vector<Joueur>* Puissance::getJoueurs() const
{
    return this->listeJoueurs;
}