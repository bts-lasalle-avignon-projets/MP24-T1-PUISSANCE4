#ifndef FICHIER_YML_H
#define FICHIER_YML_H

#include <string>
#include <map>
#include <vector>

class JSON
{
  private:
    std::string                        nomFichier;
    std::map<std::string, std::string> configuration;
    void        extraireDonnee(std::string& chaine, const std::string& adressePrecedente);
    std::string lireFichier();
    bool        chaineCommencePar(const std::string& chaine, const std::string& chaineTeste);
    bool        remplacerChaine(std::string&       chaine,
                                const std::string& ancienneChaine,
                                const std::string& nouvelleChaine);
    void        supprimerCaractereChaine(std::string& string, char caractere);
    std::vector<std::string> separerChaineBlocActuel(const std::string& chaine,
                                                     const char&        caractereSeparateur);
    std::vector<std::string> separerChaine(const std::string& chaine,
                                           const char&        caractereSeparateur);
    std::string              extraireCle(const std::string& chaine);
    std::string              extraireContenu(const std::string& chaine, const std::string& cle);
    bool                     estUnNombre(const std::string& chaine);
    std::vector<std::string> getCles(const std::string& adresse,
                                     bool               inclureClesPossedantValeur,
                                     bool               uniquementClesPossesantValeur);
    void                     creerBloc(std::ofstream&     fichier,
                                       int&               nbEspaces,
                                       const std::string& adresse,
                                       bool               ajouterVirgule);
    bool                     estUneListe(const std::string& chaine);

  public:
    JSON();
    JSON(const std::string& nomFichier);
    JSON(const JSON& fichier);
    JSON(JSON&& fichier) noexcept;
    ~JSON();
    JSON& operator=(const JSON& fichier) noexcept;
    JSON& operator=(JSON&& fichier) noexcept;

    bool                     charger();
    void                     sauvegarder();
    std::vector<std::string> getCles(const std::string& adresse, bool inclureClesPossedantValeur);
    bool                     cleExiste(const std::string& cle);
    bool                     getBoolean(const std::string& cle);
    int                      getInt(const std::string& cle);
    std::string              getString(const std::string& cle);
    std::vector<std::string> getStringList(const std::string& cle);
    void                     setBoolean(const std::string& cle, bool valeur);
    void                     setInt(const std::string& cle, int valeur);
    void                     setString(const std::string& cle, const std::string& valeur);
    void setStringList(const std::string& cle, std::vector<std::string>& valeur);
    void supprimer(const std::string& cle);
};

#endif // FICHIER_YML_H
