#include "Partie.h"
#include "Joueur.h"
#include "Ihm.h"
#include "IA.h"

using namespace std;

Partie::Partie(std::vector<Joueur>* listeJoueurs /*= nullptr*/) :
    indiceJoueurActuel(Jeton::VIDE), listeJoueurs(listeJoueurs), plateau(this)
{
}

Partie::Partie(vector<Joueur>* listeJoueurs, int nbLignes, int nbColonnes) :
    indiceJoueurActuel(Jeton::VIDE), listeJoueurs(listeJoueurs), plateau(this, nbLignes, nbColonnes)
{
}

Partie::Partie(const Partie& partie) :
    indiceJoueurActuel(partie.indiceJoueurActuel), listeJoueurs(partie.listeJoueurs),
    plateau(this, partie.plateau.getNbLignes(), partie.plateau.getNbColonnes())
{
}

Partie::Partie(Partie&& partie) noexcept :
    indiceJoueurActuel(partie.indiceJoueurActuel),
    listeJoueurs(partie.listeJoueurs),
    plateau(this, partie.plateau.getNbLignes(), partie.plateau.getNbColonnes())
{
}

Partie::~Partie()
{
}

Partie& Partie::operator=(const Partie& partie) noexcept
{
    if(&partie != this)
    {
        this->listeJoueurs       = partie.listeJoueurs;
        this->indiceJoueurActuel = partie.indiceJoueurActuel;
        this->plateau            = partie.plateau;
    }
    return *this;
}

Partie& Partie::operator=(Partie&& partie) noexcept
{
    this->listeJoueurs       = partie.listeJoueurs;
    this->indiceJoueurActuel = partie.indiceJoueurActuel;
    this->plateau            = partie.plateau;
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
    Jeton indiceJoueurSuivant = Jeton((this->indiceJoueurActuel + 1) % Jeton::NB_JETONS);
    indiceJoueurActuel        = indiceJoueurSuivant;
    Joueur joueurSuivant      = listeJoueurs->at(indiceJoueurSuivant);
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