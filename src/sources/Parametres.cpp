#include "../headers/Parametres.h"
#include "../headers/Difficulte.h"
#include "../headers/Ihm.h"
#include "../headers/JSON.h"
#include "../headers/Joueur.h"

#include <iostream>
#include <vector>

using namespace std;

constexpr int definitionNbLignes          = 6;
constexpr int definitionNbColonnes        = 7;
constexpr int definitionNbPionsAlignement = 4;

Difficulte     Parametres::difficulte        = Difficulte(NORMAL);
bool           Parametres::animations        = true;
int            Parametres::nbLignes          = definitionNbLignes;
int            Parametres::nbColonnes        = definitionNbColonnes;
int            Parametres::nbPionsAlignement = definitionNbPionsAlignement;
string         Parametres::version           = "Version inconnue";
vector<Joueur> Parametres::joueurs;

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
                choixAnimations =
                  editerParametre(texteAnimation, { "Activé", "Désactivé" }, affichageDynamique);
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
        if(commande == "menu" || commande == "m")
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
        cin >> choixParametre;
        IHM::effacerSaisie();
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
        bool estUneIA        = statistiques.getBoolean(nomJoueur + ".ia");
        int  nbPoints        = statistiques.getInt(nomJoueur + ".points");
        int  nbPartiesJouees = statistiques.getInt(nomJoueur + ".parties");
        cout << nomJoueur << ": " << estUneIA << " " << nbPoints << " " << nbPartiesJouees << endl;
    }
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