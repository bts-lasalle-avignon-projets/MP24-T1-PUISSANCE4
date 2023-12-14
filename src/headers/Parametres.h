#ifndef PARAMETRES_H
#define PARAMETRES_H

#include "../headers/Difficulte.h"

#include <iostream>
#include <vector>

class Parametres
{
  private:
    static Difficulte difficulte;
    static bool       animations;

  public:
    static void       setDifficulte(Difficulte difficulte);
    static Difficulte getDifficulte();
    static void       afficher();
    static bool       attendreCommande();
    static int        editerParametre(std::string                     selection,
                                      const std::vector<std::string>& elements,
                                      bool                            affichageDynamique);
    static void       afficherParametre(std::string                     selection,
                                        const std::vector<std::string>& elements,
                                        bool                            dynamique);
    static bool       possedeAnimation();
};

#endif // PARAMETRES_H