#ifndef HUMAIN_H
#define HUMAIN_H

#include "Joueur.h"
#include <string>

class Plateau;

class Humain : public Joueur
{
  private:
  public:
    Humain();
    Humain(Jeton couleur, const std::string& nom);
    Humain(const Humain& humain);
    Humain(Humain&& humain) noexcept;
    virtual ~Humain();

    virtual int jouerCoup(Plateau& plateau);
};

#endif // HUMAIN_H
