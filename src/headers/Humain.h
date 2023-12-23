#ifndef HUMAIN_H
#define HUMAIN_H

#include "../headers/Jeton.h"
#include "../headers/Joueur.h"
#include <iostream>

class Plateau;

class Humain : public Joueur
{
  public:
    Humain();
    Humain(Jeton couleur, const std::string& nom);
    Humain(const Humain& humain);
    Humain(Humain&& humain) noexcept;
    ~Humain();
    Humain&     operator=(const Humain& humain) noexcept;
    Humain&     operator=(Humain&& humain) noexcept;
    virtual int jouerCoup(Plateau& plateau) override;
};
#endif // HUMAIN_H