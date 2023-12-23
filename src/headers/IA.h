#ifndef IA_H
#define IA_H

#include "../headers/Joueur.h"
#include <iostream>
#include <vector>
#include <map>

class Plateau;

class IA : public Joueur
{
  public:
    IA();
    IA(Jeton jeton, const std::string& nom);
    IA(const IA& ia);
    IA(IA&& ia) noexcept;
    ~IA();
    IA&              operator=(const IA& ia) noexcept;
    IA&              operator=(IA&& ia) noexcept;
    std::vector<int> analyserCoupsVainqueurAdversaire(Plateau& plateau);
    std::vector<int> analyserSequence(Jeton jeton, int nbJetons, Plateau& plateau);
    std::vector<int> analyserCoups(Plateau& plateau);
    static int       calculerValeurHaute(std::map<int, int>& tailleSequenceParPositions);
    virtual int      jouerCoup(Plateau& plateau) override;
};

#endif // IA_H