#ifndef HISTORIQUE
#define HISTORIQUE

#include <iostream>
#include <vector>
#include <map>

class Joueur;
class Puissance;

class Historique
{
  private:
    std::vector<Puissance*> parties;
    std::map<Joueur, int>   points;

  public:
    Historique(std::vector<Joueur>& listeJoueurs);
    ~Historique();
    void savegarderPartie(Puissance* puissance);
    void ajouterVictoire(Joueur* joueur);
    void afficher();
};

#endif // HISTORIQUE