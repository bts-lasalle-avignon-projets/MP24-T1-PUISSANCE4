#include "Partie.h"
#include "Joueur.h"
#include "Ihm.h"
#include "IA.h"

using namespace std;

Partie::Partie(std::vector<Joueur>* listeJoueurs /*= nullptr*/) :
    indiceJoueurActuel(INDICE_JOUEUR_NON_DEFINI), listeJoueurs(listeJoueurs), plateau(this)
{
}

Partie::Partie(vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes) :
    indiceJoueurActuel(INDICE_JOUEUR_NON_DEFINI), listeJoueurs(listeJoueurs),
    plateau(this, nbLignes, nbColonnes)
{
}

Partie::Partie(const Partie& puissance) :
    indiceJoueurActuel(puissance.indiceJoueurActuel), listeJoueurs(puissance.listeJoueurs),
    plateau(this, puissance.plateau.getNbLignes(), puissance.plateau.getNbColonnes())
{
}

Partie::Partie(Partie&& puissance) noexcept :
    indiceJoueurActuel(puissance.indiceJoueurActuel),
    listeJoueurs(puissance.listeJoueurs),
    plateau(this, puissance.plateau.getNbLignes(), puissance.plateau.getNbColonnes())
{
}

Partie::~Partie()
{
}

Partie& Partie::operator=(const Partie& puissance) noexcept
{
    if(&puissance != this)
    {
        this->listeJoueurs       = puissance.listeJoueurs;
        this->indiceJoueurActuel = puissance.indiceJoueurActuel;
        this->plateau            = puissance.plateau;
    }
    return *this;
}

Partie& Partie::operator=(Partie&& puissance) noexcept
{
    this->listeJoueurs       = puissance.listeJoueurs;
    this->indiceJoueurActuel = puissance.indiceJoueurActuel;
    this->plateau            = puissance.plateau;
    return *this;
}

void Partie::demarrer()
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

int Partie::jouerTour()
{
    size_t prochainIndice = (this->indiceJoueurActuel + 1) % this->listeJoueurs->size();
    indiceJoueurActuel    = prochainIndice;
    Joueur joueurSuivant  = listeJoueurs->at(prochainIndice);
    IHM::afficherMessageTour(joueurSuivant);
    int indiceColonne = joueurSuivant.jouerCoup(plateau);
    return this->plateau.placerJeton(indiceColonne, joueurSuivant.getJeton());
}

bool Partie::partieEstTerminee()
{
    return this->plateau.getVainqueur() != nullptr;
}

Joueur* Partie::recupererJoueurAyantJeton(Jeton jeton)
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

Joueur* Partie::getVainqueur() const
{
    return this->plateau.getVainqueur();
}

std::vector<Joueur>* Partie::getJoueurs() const
{
    return this->listeJoueurs;
}