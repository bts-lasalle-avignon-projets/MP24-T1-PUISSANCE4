#include "Parametres.h"
#include "Ihm.h"

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
    bool continueEdition = true;
    while(continueEdition)
    {
        IHM::effacerLignes();
        IHM::afficherTexte("Difficultée : \033[1;34m" + getTexte(getDifficulte()) +
                           "\033[0m (Tapez '\033[1;31m1\033[0m')\n");
        string texteAnimation = "Activé";
        if(!animations)
        {
            texteAnimation = "Désactivé";
        }
        IHM::afficherTexte("Animations : \033[1;34m" + texteAnimation +
                           "\033[0m (Tapez '\033[1;31m2\033[0m')\n");
        continueEdition = attendreCommande();
    }
}

bool Parametres::attendreCommande()
{
    string commande;
    while(true)
    {
        IHM::afficherTexte("\nTapez une commande d'édition ou '0' pour quitter\n");
        commande = IHM::saisirCommandeDeJeu();
        IHM::effacerLignes();

        bool affichageDynamique = true;
        if(commande == "1")
        {
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
                IHM::effacerLignes();
                affichageDynamique = false;
            }
            return true;
        }

        if(commande == "2")
        {
            int choixAnimations = -1;
            while(choixAnimations != 0)
            {
                string texteAnimation = "Activé";
                if(!animations)
                {
                    texteAnimation = "Désactivé";
                }

                choixAnimations =
                  editerParametre(texteAnimation, { "Activé", "Désactivé" }, affichageDynamique);
                if(choixAnimations == 0)
                {
                    break;
                }

                animations = choixAnimations == 1;
                IHM::effacerLignes();
                affichageDynamique = false;
            }
            return true;
        }

        if(commande == "0")
        {
            return false;
        }
    }
    return false;
}

int Parametres::editerParametre(const string&              selection,
                                const vector<std::string>& elements,
                                bool                       affichageDynamique)
{
    afficherParametre(selection, elements, affichageDynamique);
    int choixParametre = -1;
    while(choixParametre < 0 || choixParametre > (int)elements.size())
    {
        choixParametre = IHM::saisirChoixParametre();
    }
    return choixParametre;
}

void Parametres::afficherParametre(const string&         selection,
                                   const vector<string>& elements,
                                   bool                  dynamique)
{
    for(int i = 0; i < (int)elements.size(); i++)
    {
        string element = elements.at(i);
        if(element == selection)
        {
            IHM::afficherTexte(to_string(i + 1) + " : \033[44m\033[1;37m[ " + element +
                               " ]\033[0m\n");
        }

        else
        {
            IHM::afficherTexte(to_string(i + 1) + " : [ " + element + " ]\033[0m\n");
        }
    }

    IHM::afficherTexte("\n0 : \033[1;31mRetour au paramètres\033[0m\n");
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