#pragma once
#define JOUEUR
#ifdef JOUEUR

#include "Couleur.h"
#include <iostream>

using namespace std;

class Joueur
{
  private:
    Couleur couleur;
    string  nom;

  public:
    Joueur(string couleur, string nom);
    ~Joueur();
    string  getNom() const;
    Couleur getCouleur() const;
};
#endif // JOUEUR