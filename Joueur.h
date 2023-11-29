#pragma once
#define JOUEUR
#ifdef JOUEUR

#include <iostream>

using namespace std;

class Joueur
{
  private:
    string couleur;
    string nom;

  public:
    Joueur(string couleur, string nom);
    ~Joueur();
    string getNom() const;
    string getCouleur() const;
};
#endif // JOUEUR