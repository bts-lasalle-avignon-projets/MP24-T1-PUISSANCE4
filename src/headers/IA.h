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
    IA(Jeton jeton, std::string nom);
    ~IA();
    std::vector<int> analyserCoupsVainqueurAdversaire();
    std::vector<int> analyserSequence(Jeton jeton, int nbJetons);
    std::vector<int> analyserCoups(Plateau& plateauTemporaire);
    int              calculerValeurHaute(std::map<int, int>& tailleSequenceParPositions);
    int              jouerCoup();
    void             setPlateau(Plateau* plateau);
};

#endif // IA_H