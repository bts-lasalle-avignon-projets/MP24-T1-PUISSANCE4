#ifndef IA_H
#define IA_H

#include "../headers/Joueur.h"
#include <iostream>
#include <vector>
#include <map>

class Plateau;

class IA : public Joueur
{
  private:
    Plateau* partie;

  public:
    IA();
    IA(Jeton jeton, const std::string& nom);
    IA(const IA& ia);
    IA(IA&& ia) noexcept;
    ~IA();
    IA&              operator=(const IA& ia) noexcept;
    IA&              operator=(IA&& ia) noexcept;
    std::vector<int> analyserCoupsVainqueurAdversaire();
    std::vector<int> analyserSequence(Jeton jeton, int nbJetons);
    std::vector<int> analyserCoups(Plateau& plateauTemporaire);
    static int       calculerValeurHaute(std::map<int, int>& tailleSequenceParPositions);
    int              jouerCoup();
    void             setPlateau(Plateau* plateau);
};

#endif // IA_H