#ifndef PARAMETRES_H
#define PARAMETRES_H

#include "../headers/Difficulte.h"

#include <iostream>
#include <vector>

class Joueur;

class Parametres
{
  private:
    static Difficulte          difficulte;
    static bool                animations;
    static int                 nbLignes;
    static int                 nbColonnes;
    static int                 nbPionsAlignement;
    static std::vector<Joueur> joueurs;
    static std::string         version;

  public:
    static void        setDifficulte(Difficulte difficulte);
    static Difficulte  getDifficulte();
    static void        afficher();
    static bool        attendreCommande();
    static int         editerParametre(const std::string&              selection,
                                       const std::vector<std::string>& elements,
                                       bool                            affichageDynamique);
    static void        afficherParametre(const std::string&              selection,
                                         const std::vector<std::string>& elements,
                                         bool                            dynamique);
    static bool        possedeAnimation();
    static int         getNbLignes();
    static void        setNbLignes(int nbLignes);
    static int         getNbColonnes();
    static void        setNbColonnes(int nbColonnes);
    static int         getNbPionsAlignement();
    static void        setNbPionsAlignement(int nbPionsAlignement);
    static void        chargerParametres();
    static std::string getVersion();
    static void        sauvegarder();
};

#endif // PARAMETRES_H