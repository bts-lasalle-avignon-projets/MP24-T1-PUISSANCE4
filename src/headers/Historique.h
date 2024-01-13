// Historique.h

#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <string>
#include <vector>
#include <map>
#include <memory>

class Joueur;
class Partie;

class Historique
{
  private:
    std::vector<std::unique_ptr<Partie> > parties;
    std::map<Joueur*, int>                points;

  public:
    Historique();
    Historique(const Historique& historique);
    Historique(Historique&& historique) noexcept;
    ~Historique();
    Historique& operator=(const Historique& historique) noexcept;
    Historique& operator=(Historique&& historique) noexcept;
    void        sauvegarderPartie(Partie* partie);
    void        ajouterVictoire(Joueur* joueur);
    void        afficher();
};

#endif // HISTORIQUE_H
