#include "Parametres.h"
#include "Difficulte.h"
#include "Ihm.h"

#include <iostream>
#include <vector>

using namespace std;

Difficulte Parametres::difficulte = Difficulte(NORMAL);
bool       Parametres::animations = true;

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
    IHM::effacerLignes(2);
    bool continueEdition = true;
    while(continueEdition)
    {
        cout << "Difficultée : "
             << "\033[1;34m" << getTexte(getDifficulte())
             << "\033[0m (Tapez '\033[1;31mdifficulte\033[0m')" << endl;
        string texteAnimation = "Activé";
        if(!animations)
        {
            texteAnimation = "Désactivé";
        }
        cout << "Animations : "
             << "\033[1;34m" << texteAnimation << "\033[0m (Tapez '\033[1;31manimation\033[0m')"
             << endl;
        continueEdition = attendreCommande();
    }
}

bool Parametres::attendreCommande()
{
    string commande = "";
    while(true)
    {
        cout << endl << "Tapez une commande d'édition ou 'menu' pour quitter" << endl;
        cin >> commande;
        IHM::effacerLignes(2);
        bool affichageDynamique = true;
        if(commande == "difficulte" || commande == "d")
        {
            IHM::effacerLignes(5);
            int choixDifficultee = -1;
            while(true)
            {
                choixDifficultee = editerParametre(getTexte(getDifficulte()),
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
                IHM::effacerLignes(9);
                affichageDynamique = false;
            }
            return true;
        }
        else if(commande == "animation" || commande == "a")
        {
            string texteAnimation = "Activé";
            if(!animations)
            {
                texteAnimation = "Désactivé";
            }
            IHM::effacerLignes(5);
            int choixAnimations = -1;
            while(choixAnimations != 0)
            {
                choixAnimations =
                  editerParametre(texteAnimation, { "Activé", "Désactivé" }, affichageDynamique);
                if(choixAnimations == 0)
                {
                    break;
                }
                animations = choixAnimations == 1;
                IHM::effacerLignes(8);
                affichageDynamique = false;
            }
            return true;
        }
        else if(commande == "menu" || commande == "m")
        {
            return false;
        }
    }
    return false;
}

int Parametres::editerParametre(std::string                     selection,
                                const std::vector<std::string>& elements,
                                bool                            affichageDynamique)
{
    afficherParametre(selection, elements, affichageDynamique);
    int choixParametre = 0;
    cin >> choixParametre;
    while(choixParametre < 0 || choixParametre > (int)elements.size())
    {
        IHM::effacerLignes(2);
        cin >> choixParametre;
    }
    return choixParametre;
}

void Parametres::afficherParametre(string selection, const vector<string>& elements, bool dynamique)
{
    cout << endl;
    for(int i = 0; i < (int)elements.size(); i++)
    {
        string element = elements.at(i);
        if(element == selection)
        {
            cout << i + 1 << " : \033[44m\033[1;37m[ " << element << " ]\033[0m" << endl;
        }
        else
        {
            cout << i + 1 << " : [ " << element << " ]\033[0m" << endl;
        }
    }
    cout << endl << "0 : \033[1;31mRetour au paramètres\033[0m" << endl;
    if(dynamique)
    {
        cout << endl;
        IHM::afficherDynamiquement("Tapez le numéro du paramètre souhaité (");
        cout << "\033[1;34m";
        IHM::afficherDynamiquement("1");
        cout << "\033[0m";
        IHM::afficherDynamiquement(" - ");
        cout << "\033[1;34m";
        IHM::afficherDynamiquement(to_string(elements.size()));
        cout << "\033[0m";
        IHM::afficherDynamiquement(") ou ");
        cout << "\033[1;31m";
        IHM::afficherDynamiquement("0");
        cout << "\033[0m";
        IHM::afficherDynamiquement(" pour quitter :");
        cout << endl;
    }
    else
    {
        cout << endl
             << "Tapez le numéro du paramètre souhaité (\033[1;34m1\033[0m - \033[1;34m"
             << elements.size() << "\033[0m) :" << endl;
    }
}

bool Parametres::possedeAnimation()
{
    return animations;
}