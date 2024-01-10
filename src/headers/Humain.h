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

    int     jouerCoup(Plateau& plateau) override;
    Humain& operator=(const Humain& humain);
    Humain& operator=(Humain&& humain) noexcept;
};

#endif // HUMAIN_H
