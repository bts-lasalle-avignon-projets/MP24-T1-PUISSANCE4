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
    Historique();
    Historique(std::vector<Joueur>& listeJoueurs);
    Historique(const Historique& historique);
    Historique(Historique&& historique) noexcept;
    ~Historique();
    Historique& operator=(const Historique& historique) noexcept;
    Historique& operator=(Historique&& historique) noexcept;
    void        savegarderPartie(Puissance* puissance, bool sauvegardeFichier);
    void        ajouterVictoire(Joueur* joueur);
    void        afficher();
    void        charger();
};

#endif // HISTORIQUE