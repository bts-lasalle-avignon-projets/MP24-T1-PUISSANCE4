#include "../headers/Ihm.h"
#include "../headers/Jeton.h"
#include "../headers/Joueur.h"
#include "../headers/Parametres.h"
#include "../headers/IA.h"
#include "../headers/Historique.h"
#include "../headers/Puissance.h"
#include "../headers/Humain.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int           IHM::nbLignesASupprimer = 0;
constexpr int tempsAffichageCaractere = 20;

string IHM::saisieNomJoueur(const string& indicationTextuelle, bool verifierDoublons)
{
    string nom;
    while((nom.empty() && !verifierDoublons) || (verifierDoublons && !nomJoueurValide(nom)))
    {
        afficherTexte("Entrez le nom/pseudo du Joueur");
        if(!indicationTextuelle.empty())
        {
            afficherTexte(" " + indicationTextuelle);
        }
        afficherTexte(" : ");
        cin >> nom;
        effacerSaisie();
    }
    return nom;
}

bool IHM::nomJoueurValide(const std::string& nomJoueur)
{
    if(nomJoueur.empty())
    {
        return false;
    }
    for(Joueur* joueur: Parametres::getJoueursExistant())
    {
        if(joueur->getNom() == nomJoueur)
        {
            IHM::afficherErreur(
              "\033[1;31mErreur: Ce nom est déjà utilisé par un autre joueur\033[0m\n");
            return false;
        }
    }
    return true;
}

void IHM::afficherMessageTour(const Joueur* joueur)
{
    afficherDynamiquement("C'est au tour de " + getCouleur(joueur->getJeton()) + joueur->getNom() +
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

void IHM::afficherPartieNulle()
{
    afficherTexte("                                                \n");
    afficherTexte(" _____         _   _                _ _     \n");
    afficherTexte("|  _  |___ ___| |_|_|___    ___ _ _| | |___ \n");
    afficherTexte("|   __| .'|  _|  _| | -_|  |   | | | | | -_|\n");
    afficherTexte("|__|  |__,|_| |_| |_|___|  |_|_|___|_|_|___|\n");
    afficherTexte("                                            \n");
}

void IHM::afficherMenu()
{
    string rouge  = "\033[1;31m";
    string jaune  = "\033[1;33m";
    string violet = "\033[1;95m";
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
    afficherTexte(violet + "V" + Parametres::getVersion() + "\n");
    afficherTexte(jaune + "                                              " + rouge + "        \n");
    mettreZeroNbLignesASupprimer();
    afficherTexte(jaune + "Commandes de jeu à taper:\033[0m\n");
    afficherTexte(" - Jouer une nouvelle partie: " + rouge + "play\033[0m\n");
    afficherTexte(" - Afficher l'historique: " + rouge + "history\033[0m\n");
    afficherTexte(" - Accéder aux paramètres: " + rouge + "settings\033[0m\n");
    afficherTexte(" - Lire les règles: " + rouge + "rules\033[0m\n");
    afficherTexte("\n - " + rouge + "Quitter: " + jaune + "quit\033[0m\n");
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
    string commande;
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

void IHM::afficherErreur(const string& texte)
{
    compterNbLignes(texte);
    cerr << texte;
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
            attendre(tempsAffichageCaractere);
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

void IHM::attendre(int millisecondes)
{
    this_thread::sleep_for(chrono::milliseconds(millisecondes));
}

void IHM::initialiserJeu()
{
    bool       continueLeJeu = true;
    Historique historique;
    historique.charger();

    while(continueLeJeu)
    {
        IHM::effacerTout();
        IHM::afficherMenu();
        string commande = IHM::saisirCommandeDeJeu();
        IHM::effacerSaisie();
        IHM::effacerLignes();
        if(commande == "play" || commande == "p")
        {
            IHM::effacerTout();
            vector<Joueur*> listeJoueurs = Parametres::getJoueursChoisis();
            Puissance*      puissance    = new Puissance(listeJoueurs,
                                                 Parametres::getNbLignes(),
                                                 Parametres::getNbColonnes(),
                                                 Parametres::getNbPionsAlignement());
            puissance->demarrerPartie();
            historique.savegarderPartie(puissance, true);
            historique.ajouterVictoire(puissance->getVainqueur());
            IHM::attendreRetourMenu();
        }
        else if(commande == "history" || commande == "h")
        {
            historique.afficher();
            IHM::attendreRetourMenu();
        }
        else if(commande == "settings" || commande == "s")
        {
            Parametres::afficher();
        }
        else if(commande == "rules" || commande == "r")
        {
            IHM::effacerTout();
            IHM::afficherRegles();
            IHM::attendreRetourMenu();
        }
        else if(commande == "quit" || commande == "q")
        {
            IHM::effacerTout();
            continueLeJeu = false;
        }
    }
}

Joueur* IHM::saisirJoueur()
{
    afficherTexte("Tapez 'menu' pour annuler la création\n\n");
    string nomJoueur = IHM::saisieNomJoueur("", true);
    if(nomJoueur == "menu")
    {
        return nullptr;
    }
    string commande;
    while(commande != "oui" && commande != "non" && commande != "menu")
    {
        afficherTexte("Tapez 'menu' pour annuler la création\n\n");
        afficherTexte("Souhaitez-vous en faire une IA ? (oui/non) : ");
        cin >> commande;
        effacerSaisie();
        if(commande == "oui")
        {
            return new IA(Jeton(VIDE), nomJoueur);
        }
        else if(commande == "non")
        {
            return new Humain(Jeton(VIDE), nomJoueur);
        }
    }
    return nullptr;
}