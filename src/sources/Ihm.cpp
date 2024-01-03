#include "Ihm.h"
#include "Jeton.h"
#include "Joueur.h"
#include "Parametres.h"
#include "Humain.h"
#include "IA.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int           IHM::nbLignesASupprimer = 0;
constexpr int tempsAffichageCaractere = 20;

const string rouge  = "\033[1;31m";
const string jaune  = "\033[1;33m";
const string violet = "\033[1;95m";

string IHM::saisirNomJoueur(int numeroJoueur)
{
    string nom;
    while(!estNomJoueurValide(nom))
    {
        afficherTexte("Entrez le nom/pseudo du Joueur " + to_string(numeroJoueur) + " : ");
        cin >> nom;
        effacerSaisie();
    }
    return nom;
}

int IHM::saisirCoup()
{
    int numeroColonne = 0;
    cin >> numeroColonne;
    IHM::effacerSaisie();
    return numeroColonne;
}

bool IHM::estNomJoueurValide(const std::string& nomJoueur)
{
    if(nomJoueur.empty())
    {
        return false;
    }

    static vector<string> nomJoueurs;
    for(string& nom: nomJoueurs)
    {
        if(nom == nomJoueur)
        {
            nbLignesASupprimer++;
            cerr << "\033[1;31mErreur: Ce nom est déjà utilisé par un autre joueur\033[0m\n";
            return false;
        }
    }
    nomJoueurs.push_back(nomJoueur);
    return true;
}

void IHM::afficherMessageTour(const Joueur& joueur)
{
    afficherDynamiquement("C'est au tour de " + getCouleur(joueur.getJeton()) + joueur.getNom() +
                          getCouleur(Jeton(VIDE)) + " de jouer !\n");
}

void IHM::afficherVictoire(Joueur* joueur)
{
    afficherTexte("____            _      _        _               ____\n");
    afficherTexte("\\ \\ \\    /\\   /(_) ___| |_ ___ (_)_ __ ___     / / /\n");
    afficherTexte(" \\ \\ \\   \\ \\ / / |/ __| __/ _ \\| | '__/ _ \\   / / / \n");
    afficherTexte("  \\ \\ \\   \\ V /| | (__| || (_) | | | |  __/  / / /  \n");
    afficherTexte("   \\_\\_\\   \\_/ |_|\\___|\\__\\___/|_|_|  \\___| /_/_/   \n");
    afficherTexte("                                                    \n");
    afficherTexte(joueur->getNom() + " remporte la partie !\n");
}

void IHM::afficherBanniere()
{
    afficherTexte(jaune + "  _____       _                               " + rouge + " _  _   \n");
    afficherTexte(jaune + " |  __ \\     (_)                              " + rouge + "| || |  \n");
    afficherTexte(jaune + " | |__) |   _ _ ___ ___  __ _ _ __   ___ ___  " + rouge + "| || |_ \n");
    afficherTexte(jaune + " |  ___/ | | | / __/ __|/ _` | '_ \\ / __/ _ \\ " + rouge +
                  "|__   _|\n");
    afficherTexte(jaune + " | |   | |_| | \\__ \\__ \\ (_| | | | | (_|  __/ " + rouge +
                  "   | |  \n");
    afficherTexte(jaune + " |_|    \\__,_|_|___/___/\\__,_|_| |_|\\___\\___| " + rouge +
                  "   |_|  \n");
    afficherTexte(jaune + "                                              " + rouge + "        \n");
    afficherTexte(violet + "V2.2\n");
    afficherTexte("\033[0m\n");
    ;
}

void IHM::afficherMenu()
{
    mettreZeroNbLignesASupprimer();
    afficherTexte(jaune + "Menu\033[0m\n");
    afficherTexte(jaune + "1" + "\033[0m - Jouer une nouvelle partie" + "\033[0m\n");
    afficherTexte(jaune + "2" + "\033[0m - Afficher l'historique" + "\033[0m\n");
    afficherTexte(jaune + "3" + "\033[0m - Accéder aux paramètres" + "\033[0m\n");
    afficherTexte(jaune + "4" + "\033[0m - Lire les règles" + "\033[0m\n");
    afficherTexte(rouge + "0" + "\033[0m - Quitter" + "\033[0m\n");
}

string IHM::saisirCommandeDeJeu()
{
    string commande;
    cin >> commande;
    IHM::effacerSaisie();
    return commande;
}

int IHM::saisirChoixParametre()
{
    int choixParametre;
    cin >> choixParametre;
    IHM::effacerSaisie();
    return choixParametre;
}

void IHM::effacerLignes(int nombreDeLignes)
{
    string effacerLigne       = "\x1B[2K";
    string deplacerVersLeHaut = "\x1B[A";
    for(int i = 0; i < nombreDeLignes; ++i)
    {
        cout << effacerLigne;
        if(i < nombreDeLignes - 1)
        {
            cout << deplacerVersLeHaut;
        }
    }
}

void IHM::attendreRetourMenu()
{
    afficherTexte("\nTapez '" + rouge + "0" + "\033[0m' pour revenir au menu\n");
    string commande;
    while(commande != "0")
    {
        cin >> commande;
        effacerSaisie();
    }
}

void IHM::effacerTout()
{
    std::system("clear");
    nbLignesASupprimer = 0;
}

void IHM::effacerLignes()
{
    effacerLignes(nbLignesASupprimer + 1);
    nbLignesASupprimer = 0;
}

void IHM::effacerSaisie()
{
    effacerLignes(2);
}

void IHM::mettreZeroNbLignesASupprimer()
{
    nbLignesASupprimer = 0;
}

void IHM::afficherTexte(const string& texte)
{
    compterNbLignes(texte);
    cout << texte;
}

void IHM::compterNbLignes(const string& texte)
{
    for(char caractere: texte)
    {
        if(caractere == '\n')
        {
            nbLignesASupprimer++;
        }
    }
}

void IHM::afficherDynamiquement(const string& message)
{
    if(!Parametres::possedeAnimation())
    {
        afficherTexte(message);
        return;
    }
    compterNbLignes(message);
    for(int i = 0; i < (int)message.size(); ++i)
    {
        if(message.at(i) == '\033')
        {
            int indiceFinCodeCouleur = message.find('m', i);
            cout << message.substr(i, indiceFinCodeCouleur - i + 1);
            i = indiceFinCodeCouleur;
        }

        else
        {
            std::cout << message.at(i) << flush;
            this_thread::sleep_for(chrono::milliseconds(tempsAffichageCaractere));
        }
    }
}

void IHM::afficherRegles()
{
    afficherTexte("\033[1;34m   _____            _           \n");
    afficherTexte("  |  __ \\          | |          \n");
    afficherTexte("  | |__) |___  __ _| | ___  ___ \n");
    afficherTexte("  |  _  // _ \\/ _` | |/ _ \\/ __|\n");
    afficherTexte("  | | \\ \\  __/ (_| | |  __/\\__ \\\n");
    afficherTexte("  |_|  \\_\\___|\\__, |_|\\___||___/\n");
    afficherTexte("               __/ |            \n");
    afficherTexte("              |___/              \n");
    afficherTexte("\033[0m\n");

    afficherTexte(
      "1. Le jeu se joue sur un plateau vertical de 6 lignes et horizontal de 7 colonnes.\n");
    afficherTexte("\n");
    afficherTexte("2. Deux joueurs s'affrontent avec des jetons de couleurs différentes "
                  "(\033[1;91mRouge\033[0m et \033[1;93mJaune\033[0m).\n");
    afficherTexte("\n");
    afficherTexte(
      "3. Les joueurs placent tour à tour un jeton dans l'une des colonnes du plateau.\n");
    afficherTexte("\n");
    afficherTexte("4. Le jeton tombe au point le plus bas possible dans la colonne choisie.\n");
    afficherTexte("\n");
    afficherTexte("5. Le premier joueur qui parvient à aligner quatre de ses jetons consécutifs "
                  "(horizontalement, verticalement ou en diagonale) remporte la partie.\n");
    afficherTexte("\n");
    afficherTexte("6. Si le plateau est rempli sans qu'aucun joueur n'ait aligné quatre "
                  "jetons, la partie est déclarée nulle.\n");
    afficherTexte("\n");
}

void IHM::afficherParametres()
{
    Parametres::afficher();
}

void IHM::saisirJoueurs(std::vector<Joueur*>& listeJoueurs, int nbJoueurs)
{
    bool contientIA = false;

    listeJoueurs.clear();
    for(int i = 0; i < nbJoueurs; i++)
    {
        string commande;
        while(commande != "oui" && commande != "non")
        {
            afficherTexte("Souhaitez-vous faire jouer ");
            if(contientIA)
            {
                afficherTexte("une autre ");
            }
            afficherTexte("IA ? (oui/non) : ");

            cin >> commande;
            effacerSaisie();
            if(commande == "oui")
            {
                listeJoueurs.push_back(new IA(Jeton(i), "Brendan #" + to_string(i + 1)));
                contientIA = true;
            }
            else if(commande == "non")
            {
                listeJoueurs.push_back(new Humain(Jeton(i), IHM::saisirNomJoueur(i + 1)));
            }
            afficherTexte(listeJoueurs.at(i)->getNom() + " à été ajouté\n");
        }
    }
}