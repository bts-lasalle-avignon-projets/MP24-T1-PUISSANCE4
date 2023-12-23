#include "../headers/JSON.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

JSON::JSON() : nomFichier(""), configuration()
{
}

JSON::JSON(const string& nomFichier) : nomFichier(nomFichier), configuration()
{
    charger();
}

JSON::JSON(const JSON& fichier) :
    nomFichier(fichier.nomFichier), configuration(fichier.configuration)
{
}

JSON::JSON(JSON&& fichier) noexcept :
    nomFichier(move(fichier.nomFichier)),
    configuration(move(fichier.configuration))
{
}

JSON::~JSON()
{
}

JSON& JSON::operator=(const JSON& fichier) noexcept
{
    if(this != &fichier)
    {
        nomFichier    = fichier.nomFichier;
        configuration = fichier.configuration;
    }
    return *this;
}

JSON& JSON::operator=(JSON&& fichier) noexcept
{
    if(this != &fichier)
    {
        nomFichier    = move(fichier.nomFichier);
        configuration = move(fichier.configuration);
    }
    return *this;
}

bool JSON::charger()
{
    string chaine = lireFichier();
    extraireDonnee(chaine, "");
    return true;
}

void JSON::sauvegarder()
{
    ofstream fichier;
    fichier.open(nomFichier, ofstream::out | ofstream::trunc);
    int nbEspaces = 1;
    creerBloc(fichier, nbEspaces, "", false);
    fichier.close();
}

void JSON::creerBloc(ofstream& fichier, int& nbEspaces, const string& adresse, bool ajouterVirgule)
{
    fichier << "{" << endl;
    nbEspaces += 2;
    string         adresseActuelle  = adresse.empty() ? adresse : adresse + ".";
    vector<string> cles             = getCles(adresse, false);
    vector<string> clesAyantValeurs = getCles(adresse, true, true);
    for(int i = 0; i < (int)clesAyantValeurs.size(); i++)
    {
        if(i != 0)
        {
            fichier << "," << endl;
        }
        string cleAyantValeurs = clesAyantValeurs.at(i);
        string contenu         = configuration[adresseActuelle + cleAyantValeurs];
        if(estUneListe(contenu))
        {
            string nouveauContenu = "[";
            string contenuExtrait = "";
            for(int i = 1; i < (int)contenu.size() - 1; i++)
            {
                contenuExtrait += contenu.at(i);
            }
            vector<string> contenuSepare = separerChaine(contenuExtrait, ',');
            for(int i = 0; i < (int)contenuSepare.size(); i++)
            {
                string chaineExtraite = contenuSepare.at(i);
                nouveauContenu += '"' + chaineExtraite + '"';
                if(i != (int)contenuSepare.size() - 1)
                {
                    nouveauContenu += ", ";
                }
            }
            nouveauContenu += ']';
            contenu = nouveauContenu;
        }
        else if(!estUnNombre(contenu) && contenu != "true" && contenu != "false")
        {
            contenu = '"' + contenu + '"';
        }
        fichier << setfill(' ') << setw(nbEspaces) << '"' << cleAyantValeurs << "\": " << contenu;
    }
    if(!cles.empty() && !clesAyantValeurs.empty())
    {
        fichier << "," << endl;
    }
    for(int i = 0; i < (int)cles.size(); i++)
    {
        string cle = cles.at(i);
        fichier << setfill(' ') << setw(nbEspaces) << '"' << cle << "\": ";
        creerBloc(fichier, nbEspaces, adresseActuelle + cle, i != (int)cles.size() - 1);
    }
    nbEspaces -= 2;
    if(nbEspaces != 1)
    {
        fichier << endl << setfill(' ') << setw(nbEspaces) << "}";
        if(ajouterVirgule)
        {
            fichier << "," << endl;
        }
    }
    else
    {
        fichier << endl << "}" << endl;
    }
}

bool JSON::estUneListe(const string& chaine)
{
    return chaine.at(0) == '[' && chaine.at(chaine.size() - 1) == ']';
}

bool JSON::estUnNombre(const string& chaine)
{
    for(char c: chaine)
    {
        if(!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

string JSON::lireFichier()
{
    ifstream fichier(nomFichier);
    if(!fichier.is_open())
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        return "";
    }
    string ligne;
    string chaine = "";
    while(getline(fichier, ligne))
    {
        for(char c: ligne)
        {
            if(c != ' ')
            {
                chaine += c;
            }
        }
    }
    fichier.close();
    return chaine;
}

void JSON::supprimerCaractereChaine(string& string, char caractere)
{
    size_t position = string.find(caractere);
    while(position != string::npos)
    {
        string.erase(position, 1);
        position = string.find(caractere);
    }
}

void JSON::extraireDonnee(string& chaine, const string& adressePrecedente)
{
    for(string chaineSeparee: separerChaineBlocActuel(chaine, ','))
    {
        string adresseActuelle =
          adressePrecedente.empty() ? adressePrecedente : adressePrecedente + ".";
        string cle     = extraireCle(chaineSeparee);
        string contenu = extraireContenu(chaineSeparee, cle);
        supprimerCaractereChaine(cle, '"');
        adresseActuelle += cle;
        if(adresseActuelle.empty())
        {
            continue;
        }
        if(contenu.find(':') != string::npos)
        {
            extraireDonnee(contenu, adresseActuelle);
        }
        else
        {
            supprimerCaractereChaine(contenu, '"');
            configuration[adresseActuelle] = contenu;
        }
    }
}

string JSON::extraireCle(const string& chaine)
{
    string cle = separerChaine(chaine, ':').at(0);
    return cle;
}

string JSON::extraireContenu(const string& chaine, const string& cle)
{
    string contenu = "";
    for(size_t i = cle.size() + 1; i < chaine.size(); i++)
    {
        contenu += chaine.at(i);
    }
    return contenu;
}

vector<string> JSON::separerChaine(const string& chaine, const char& caractereSeparateur)
{
    vector<string> chaines;
    string         chaineConstruction = "";
    for(char c: chaine)
    {
        if(c != caractereSeparateur)
        {
            chaineConstruction += c;
        }
        else
        {
            chaines.push_back(chaineConstruction);
            chaineConstruction = "";
        }
    }
    chaines.push_back(chaineConstruction);
    return chaines;
}

vector<string> JSON::separerChaineBlocActuel(const string& chaine, const char& caractereSeparateur)
{
    vector<string> chaines;
    string         chaineConstruction = "";
    int            nbBlocs            = 0;
    int            nbCrochets         = 0;
    for(int i = 1; i < (int)chaine.size() - 1; i++)
    {
        char c = chaine.at(i);
        if(c == '{')
        {
            nbBlocs++;
        }
        if(c == '}')
        {
            nbBlocs--;
        }
        if(c == '[')
        {
            nbCrochets++;
        }
        if(c == ']')
        {
            nbCrochets--;
        }
        if(c != caractereSeparateur || nbCrochets != 0 || nbBlocs != 0)
        {
            chaineConstruction += c;
        }
        else
        {
            chaines.push_back(chaineConstruction);
            chaineConstruction = "";
        }
    }
    chaines.push_back(chaineConstruction);
    return chaines;
}

bool JSON::cleExiste(const string& cle)
{
    for(map<string, string>::iterator it = configuration.begin(); it != configuration.end(); it++)
    {
        if(it->first == cle)
        {
            return true;
        }
    }
    return false;
}

bool JSON::chaineCommencePar(const string& chaine, const string& chaineTeste)
{
    if(chaine.size() < chaineTeste.size())
    {
        return false;
    }
    for(int i = 0; i < (int)chaineTeste.size(); i++)
    {
        if(chaine.at(i) != chaineTeste.at(i))
        {
            return false;
        }
    }
    return true;
}

bool JSON::remplacerChaine(string&       chaine,
                           const string& ancienneChaine,
                           const string& nouvelleChaine)
{
    size_t indiceDebutChaine = chaine.find(ancienneChaine);
    if(indiceDebutChaine == string::npos)
    {
        return false;
    }
    chaine.replace(indiceDebutChaine, ancienneChaine.length(), nouvelleChaine);
    return true;
}

bool JSON::getBoolean(const string& cle)
{
    return configuration[cle] == "true";
}

int JSON::getInt(const string& cle)
{
    return stoi(configuration[cle]);
}

string JSON::getString(const string& cle)
{
    return configuration[cle];
}

vector<string> JSON::getStringList(const string& cle)
{
    string contenu        = configuration[cle];
    string contenuExtrait = "";
    for(int i = 1; i < (int)contenu.size() - 1; i++)
    {
        contenuExtrait += contenu.at(i);
    }
    return separerChaine(contenuExtrait, ',');
}

vector<string> JSON::getCles(const string& adresse, bool inclureClesPossedantValeur)
{
    return getCles(adresse, inclureClesPossedantValeur, false);
}

vector<string> JSON::getCles(const string& adresse,
                             bool          inclureClesPossedantValeur,
                             bool          uniquementClesPossesantValeur)
{
    if(uniquementClesPossesantValeur && !inclureClesPossedantValeur)
    {
        inclureClesPossedantValeur = true;
    }
    vector<string> cles;
    string         adresseActuelle = adresse.empty() ? adresse : adresse + ".";
    for(map<string, string>::iterator it = configuration.begin(); it != configuration.end(); it++)
    {
        string cle = it->first;
        if(!chaineCommencePar(cle, adresseActuelle))
        {
            continue;
        }
        remplacerChaine(cle, adresseActuelle, "");
        cle = separerChaine(cle, '.').at(0);
        if(cleExiste(adresseActuelle + cle) && !inclureClesPossedantValeur &&
           !uniquementClesPossesantValeur)
        {
            continue;
        }
        if(!cleExiste(adresseActuelle + cle) && uniquementClesPossesantValeur)
        {
            continue;
        }
        if(!count(cles.begin(), cles.end(), cle))
        {
            cles.push_back(cle);
        }
    }
    return cles;
}

void JSON::setBoolean(const string& cle, bool valeur)
{
    string nomValeur = "true";
    if(!valeur)
    {
        nomValeur = "false";
    }
    configuration[cle] = nomValeur;
}

void JSON::setInt(const string& cle, int valeur)
{
    configuration[cle] = to_string(valeur);
}

void JSON::setString(const string& cle, const string& valeur)
{
    configuration[cle] = valeur;
}

void JSON::setStringList(const string& cle, vector<string>& valeur)
{
    string contenu = "[";
    for(int i = 0; i < (int)valeur.size(); i++)
    {
        string chaine = valeur.at(i);
        if(i != (int)valeur.size() - 1)
        {
            chaine += ',';
        }
        contenu += chaine;
    }
    configuration[cle] = contenu + "]";
}