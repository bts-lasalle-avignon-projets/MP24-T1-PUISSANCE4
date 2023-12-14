#include "Ihm.h"
#include "Jeton.h"
#include "Joueur.h"
#include "Parametres.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int IHM::nbLignesASupprimer = 0;

string IHM::saisieNomJoueur(int numeroJoueur)
{
    string nom;
    afficherTexte("Entrez le nom/pseudo du Joueur " + to_string(numeroJoueur) + " : ");
    cin >> nom;
    effacerSaisie();
    return nom;
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

void IHM::afficherMenu()
{
    string rouge = "\033[1;31m";
    string jaune = "\033[1;33m";
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
    afficherTexte(jaune + "                                              " + rouge + "        \n");
    mettreZeroNbLignesASupprimer();
    afficherTexte(jaune + "Commandes de jeu à taper:\033[0m\n");
    afficherTexte(" - Jouer une nouvelle partie: " + rouge + "play\033[0m\n");
    afficherTexte(" - Afficher l'historique: " + rouge + "history\033[0m\n");
    afficherTexte(" - Accéder aux paramètres: " + rouge + "settings\033[0m\n");
}

string IHM::saisirCommandeDeJeu()
{
    string commande;
    cin >> commande;
    return commande;
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
    afficherTexte("Tapez 'menu' pour quitter\n");
    string commande = "";
    while(commande != "menu")
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
            this_thread::sleep_for(chrono::milliseconds(20));
        }
    }
}