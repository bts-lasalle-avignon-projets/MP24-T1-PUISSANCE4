#include "../headers/Parametres.h"
#include "../headers/Difficulte.h"
#include "../headers/Ihm.h"
#include "../headers/JSON.h"
#include "../headers/Joueur.h"
#include "../headers/IA.h"
#include "../headers/Humain.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int definitionNbLignes          = 6;
constexpr int definitionNbColonnes        = 7;
constexpr int definitionNbPionsAlignement = 4;

constexpr int nbJoueursRequis = 2;

Difficulte      Parametres::difficulte        = Difficulte(NORMAL);
bool            Parametres::animations        = true;
int             Parametres::nbLignes          = definitionNbLignes;
int             Parametres::nbColonnes        = definitionNbColonnes;
int             Parametres::nbPionsAlignement = definitionNbPionsAlignement;
string          Parametres::version           = "Version inconnue";
vector<Joueur*> Parametres::joueursExistant;
vector<Joueur*> Parametres::joueursChoisis;

void Parametres::setDifficulte(Difficulte difficulte)
{
    Parametres::difficulte = difficulte;
}

Difficulte Parametres::getDifficulte()
{
    return difficulte;
}

void Parametres::afficher()
{
    bool continueEdition = true;
    while(continueEdition)
    {
        IHM::effacerLignes();
        IHM::afficherTexte("Difficultée : \033[1;34m" + getTexte(getDifficulte()) +
                           "\033[0m (Tapez '\033[1;31mdifficulte\033[0m')\n");
        string texteAnimation = "Activé";
        if(!animations)
        {
            texteAnimation = "Désactivé";
        }
        IHM::afficherTexte("Animations : \033[1;34m" + texteAnimation +
                           "\033[0m (Tapez '\033[1;31manimation\033[0m')\n");
        IHM::afficherTexte("Sélection Joueur (Tapez '\033[1;31mjoueurs\033[0m')\n");
        continueEdition = attendreCommande();
    }
}

bool Parametres::attendreCommande()
{
    string commande;
    while(true)
    {
        IHM::afficherTexte("\nTapez une commande d'édition ou 'menu' pour quitter\n");
        cin >> commande;
        IHM::effacerSaisie();
        IHM::effacerLignes();
        bool affichageDynamique = true;
        if(commande == "difficulte" || commande == "d")
        {
            int choixDifficultee = -1;
            while(true)
            {
                choixDifficultee = editerParametre({ getTexte(getDifficulte()) },
                                                   { getTexte(Difficulte(FACILE)),
                                                     getTexte(Difficulte(NORMAL)),
                                                     getTexte(Difficulte(DIFFICILE)),
                                                     getTexte(Difficulte(EPIQUE)) },
                                                   affichageDynamique);
                if(choixDifficultee == 0)
                {
                    break;
                }
                setDifficulte(getDifficulteIndexe(choixDifficultee));
                IHM::effacerLignes();
                affichageDynamique = false;
                sauvegarder();
            }
            return true;
        }
        if(commande == "animation" || commande == "a")
        {
            int choixAnimations = -1;
            while(choixAnimations != 0)
            {
                string texteAnimation = "Activé";
                if(!animations)
                {
                    texteAnimation = "Désactivé";
                }
                choixAnimations = editerParametre({ texteAnimation },
                                                  { "Activé", "Désactivé" },
                                                  affichageDynamique);
                if(choixAnimations == 0)
                {
                    break;
                }
                animations = choixAnimations == 1;
                IHM::effacerLignes();
                affichageDynamique = false;
                sauvegarder();
            }
            return true;
        }
        if(commande == "joueurs" || commande == "j")
        {
            afficherMenuJoueurs();
            return true;
        }
        if(commande == "menu" || commande == "m")
        {
            return false;
        }
    }
    return false;
}

int Parametres::editerParametre(const vector<string>& selection,
                                const vector<string>& elements,
                                bool                  affichageDynamique)
{
    afficherParametre(selection, elements, affichageDynamique);
    int choixParametre = -1;
    while(choixParametre < 0 || choixParametre > (int)elements.size())
    {
        cin >> choixParametre;
        IHM::effacerSaisie();
    }
    return choixParametre;
}

void Parametres::afficherParametre(const vector<string>& selection,
                                   const vector<string>& elements,
                                   bool                  dynamique)
{
    for(int i = 0; i < (int)elements.size(); i++)
    {
        string element = elements.at(i);
        if(find(selection.begin(), selection.end(), element) != selection.end())
        {
            IHM::afficherTexte(to_string(i + 1) + " : \033[44m\033[1;37m[ " + element +
                               " ]\033[0m\n");
        }
        else
        {
            IHM::afficherTexte(to_string(i + 1) + " : [ " + element + " ]\033[0m\n");
        }
    }
    IHM::afficherTexte("\n0 : \033[1;31mRetour\033[0m\n");
    string message = "\nTapez le numéro du paramètre souhaité (\033[1;34m1\033[0m - \033[1;34m" +
                     to_string(elements.size()) + "\033[0m) :\n";
    if(dynamique)
    {
        IHM::afficherDynamiquement(message);
    }
    else
    {
        IHM::afficherTexte(message);
    }
}

bool Parametres::possedeAnimation()
{
    return animations;
}

int Parametres::getNbLignes()
{
    return Parametres::nbLignes;
}

void Parametres::setNbLignes(int nbLignes)
{
    Parametres::nbLignes = nbLignes;
}

int Parametres::getNbColonnes()
{
    return Parametres::nbColonnes;
}

void Parametres::setNbColonnes(int nbColonnes)
{
    Parametres::nbColonnes = nbColonnes;
}

int Parametres::getNbPionsAlignement()
{
    return Parametres::nbPionsAlignement;
}

void Parametres::setNbPionsAlignement(int nbPionsAlignement)
{
    Parametres::nbPionsAlignement = nbPionsAlignement;
}

void Parametres::chargerParametres()
{
    JSON parametres("src/parametres.json");
    Parametres::animations = parametres.getBoolean("animation");
    Parametres::difficulte = getDifficulteIndexe(parametres.getInt("difficulte"));
    Parametres::version    = parametres.getString("version");

    JSON statistiques("src/statistiques.json");
    for(string nomJoueur: statistiques.getCles("", false))
    {
        if(statistiques.getBoolean(nomJoueur + ".ia"))
        {
            joueursExistant.push_back(new IA(Jeton(VIDE), nomJoueur));
        }
        else
        {
            joueursExistant.push_back(new Humain(Jeton(VIDE), nomJoueur));
        }
    }
    IHM::afficherTexte("Choisissez vos " + to_string(nbJoueursRequis) +
                       " joueur(s) qui sont s'affronter\n\n");
    IHM::mettreZeroNbLignesASupprimer();
    afficherMenuJoueurs();
    IHM::effacerTout();
}

void Parametres::afficherMenuJoueurs()
{
    bool affichageDynamique = true;
    int  choixJoueur        = -1;
    while(choixJoueur != 0)
    {
        vector<string> joueurs;
        vector<string> nomJoueurs;
        joueurs.push_back("\033[1;37m(\033[1;36m+\033[1;37m) \033[1;36mCréer un profil\033[0m");
        joueurs.push_back("\033[1;37m(\033[1;31m-\033[1;37m) \033[1;31mSupprimer un profil\033[0m");
        for(Joueur* joueur: joueursExistant)
        {
            string prefix = "";
            if(joueur->estUneIA())
            {
                prefix = "[IA] ";
            }
            nomJoueurs.push_back(joueur->getNom());
            joueurs.push_back(prefix + joueur->getNom());
        }
        vector<string> joueursSelection;
        for(Joueur* joueur: joueursChoisis)
        {
            string prefix = "";
            if(joueur->estUneIA())
            {
                prefix = "[IA] ";
            }
            joueursSelection.push_back(prefix + joueur->getNom());
        }
        choixJoueur = editerParametre(joueursSelection, joueurs, affichageDynamique);
        if(choixJoueur == 0)
        {
            if((int)joueursChoisis.size() != nbJoueursRequis)
            {
                IHM::effacerLignes();
                affichageDynamique = false;
                choixJoueur        = -1;
                IHM::afficherErreur("\033[1;31mErreur: Le nombre de joueurs actifs doit être de " +
                                    to_string(nbJoueursRequis) + "\033[0m\n");
                continue;
            }
            break;
        }
        if(choixJoueur == 1)
        {
            IHM::effacerLignes();
            affichageDynamique    = false;
            Joueur* nouveauJoueur = IHM::saisirJoueur();
            if(nouveauJoueur != nullptr)
            {
                joueursExistant.push_back(nouveauJoueur);
                JSON statistiques("src/statistiques.json");
                statistiques.setBoolean(nouveauJoueur->getNom() + ".ia", nouveauJoueur->estUneIA());
                statistiques.setInt(nouveauJoueur->getNom() + ".parties", 0);
                statistiques.setInt(nouveauJoueur->getNom() + ".points", 0);
                statistiques.sauvegarder();
            }
            IHM::effacerLignes();
            continue;
        }
        if(choixJoueur == 2)
        {
            IHM::effacerLignes();
            affichageDynamique = false;
            Joueur* joueurASupprimer =
              recupererJoueurParNom(IHM::saisieNomJoueur("à supprimer", false));
            if(joueurASupprimer == nullptr)
            {
                IHM::afficherErreur("\033[1;31mErreur: Ce joueur n'existe pas\033[0m\n");
            }
            else
            {
                for(int i = 0; i < (int)joueursExistant.size(); i++)
                {
                    if(joueursExistant.at(i)->getNom() == joueurASupprimer->getNom())
                    {
                        joueursExistant.erase(joueursExistant.begin() + i);
                        if(find(joueursChoisis.begin(), joueursChoisis.end(), joueurASupprimer) !=
                           joueursChoisis.end())
                        {
                            for(int j = 0; j < (int)joueursChoisis.size(); j++)
                            {
                                joueursChoisis.erase(joueursChoisis.begin() + j);
                            }
                        }
                        JSON statistiques("src/statistiques.json");
                        statistiques.supprimer(joueurASupprimer->getNom() + ".ia");
                        statistiques.supprimer(joueurASupprimer->getNom() + ".parties");
                        statistiques.supprimer(joueurASupprimer->getNom() + ".points");
                        statistiques.sauvegarder();
                        delete joueurASupprimer;
                        break;
                    }
                }
            }
            IHM::effacerLignes();
            continue;
        }
        if((int)joueursChoisis.size() == nbJoueursRequis)
        {
            joueursChoisis.clear();
        }
        Joueur* joueurChoisi = recupererJoueurParNom(nomJoueurs.at(choixJoueur - 3));
        if(find(joueursChoisis.begin(), joueursChoisis.end(), joueurChoisi) != joueursChoisis.end())
        {
            IHM::effacerLignes();
            affichageDynamique = false;
            IHM::afficherErreur("\033[1;31mErreur: Ce joueur est déjà sélectionné\033[0m\n");
            continue;
        }
        joueursChoisis.push_back(joueurChoisi);
        IHM::effacerLignes();
        affichageDynamique = false;
    }
}

vector<Joueur*> Parametres::getJoueursExistant()
{
    return Parametres::joueursExistant;
}

vector<Joueur*> Parametres::getJoueursChoisis()
{
    return Parametres::joueursChoisis;
}

void Parametres::sauvegarder()
{
    JSON json("src/parametres.json");
    json.setBoolean("animation", Parametres::animations);
    json.setInt("difficulte", getIndice(Parametres::difficulte));
    json.sauvegarder();
}

string Parametres::getVersion()
{
    return Parametres::version;
}

void Parametres::sortie()
{
    for(int i = 0; i < (int)joueursExistant.size(); i++)
    {
        delete joueursExistant[i];
    }
    joueursExistant.clear();
}

Joueur* Parametres::recupererJoueurParNom(const string& nom)
{
    for(Joueur* joueur: joueursExistant)
    {
        if(joueur->getNom() == nom)
        {
            return joueur;
        }
    }
    return nullptr;
}