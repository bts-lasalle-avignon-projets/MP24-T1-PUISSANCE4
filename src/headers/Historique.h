#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <string>
#include <vector>
#include <map>

class Joueur;
class Partie;

class Historique
{
  private:
    std::vector<Partie>   parties;
    std::map<Joueur, int> points;

  public:
    Historique();
    Historique(std::vector<Joueur>& listeJoueurs);
    Historique(const Historique& historique);
    Historique(Historique&& historique) noexcept;
    ~Historique();
    Historique& operator=(const Historique& historique) noexcept;
    Historique& operator=(Historique&& historique) noexcept;
    void        savegarderPartie(Partie& puissance);
    void        ajouterVictoire(Joueur* joueur);
    void        afficher();
};

#endif // HISTORIQUE_H
