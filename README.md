[![C/C++ make](https://github.com/btssn-lasalle-84/MP24-T1-PUISSANCE4/actions/workflows/c-cpp.yml/badge.svg?branch=develop)](https://github.com/btssn-lasalle-84/MP24-T1-PUISSANCE4/actions/workflows/c-cpp.yml)[![C/C++ format](https://github.com/btssn-lasalle-84/MP24-T1-PUISSANCE4/actions/workflows/cppformat.yml/badge.svg?branch=develop)](https://github.com/btssn-lasalle-84/MP24-T1-PUISSANCE4/actions/workflows/cppformat.yml)

# Mini-Projet Puissance 4

## Informations

- Nom du logiciel : Puissance 4
- Date de début : 24 novembre 2023 à 14:58
- Numéro de version du logiciel : 1.1

## Présentation

Ce projet implémente le jeu classique "Puissance4" en POO/C++. Le jeu met en scène deux joueurs qui alternent pour placer des jetons de couleur dans une grille suspendue verticalement. L'objectif est de connecter quatre jetons de sa propre couleur consécutivement en ligne (horizontalement, verticalement ou diagonalement) avant l'adversaire.

Lien Wikipédia : [Puissance 4](https://fr.wikipedia.org/wiki/Puissance_4)

## Utilisation

```bash
$ make

$ ./puissance4.out
```

## Ce que le logiciel fait dans cette version

Permet de jouer une partie de Puissance 4 à deux joueurs.

### Version 1.0

- [x] saisir le nom du joueur
- [x] jouer une partie
- [x] afficher le déroulement d’une partie

### Version 1.1

- [x] Affichage de Nom et version du jeu
- [x] Affichage d'un menu
- [x] Correction de bug

![Puissance4](images/puissance4-1.1.gif)

## TODO

### Version 2.0

- [ ] Choix du niveau de difficulté
- [ ] Possibilité de jouer une ou plusieurs parties
- [ ] Affichage de l'historique des parties jouées

### Version 3.0

- [ ] Configuration de la grille et du nombre de pions à aligner
- [ ] Affichage des statistiques du joueur
- [ ] Sauvegarde des statistiques du joueur dans un fichier
- [ ] Chronométrage de la partie

## Défauts constatés non corrigés


## Itérations 1

![Jira-iteration](images/jira-iteration1.png)

## Diagramme du domaine

```mermaid
classDiagram

class Jeton {
  <<enumeration>>
  VIDE
  ROUGE
  JAUNE
}

class IHM {
 
}

class Joueur {
  -nom: string
}

class Puissance {
  -indiceJoueurActuel: int
}

class Plateau {
  -lignes: int
  -colonnes: int
}

Jeton "- couleur" <-- Joueur
Puissance --> IHM
Plateau --> IHM
Joueur "- listeJoueurs" --* Puissance : vector< Joueur >
Plateau "- plateau" <--o "- partie" Puissance
Jeton "- cases" <--o Plateau : vector< Jeton >
```


## Diagramme de classes

![diagramme-classes-1.0](images/diagramme-classes-1.0.png)

## Équipe de développement

- [Jules HILLION](mailto:redisbackhere@gmail.com)
- [Thomas HNIZDO](mailto:thomas.hnizdo@gmail.com)

---
&copy; 2023 LaSalle Avignon