# IA Puissance 4

Implémentation d'une IA alpha beta qui joue au puissance 4

## Description

Ce répertoire contient une arène de jeu d'un puissance 4 avec 3 types de joueurs : Random, Brutal, AlphaBeta.    
    
Ce programme fait jouer 2 joueurs parmi la liste des joueurs ci-dessus dans un challenge de X parties (100 par défaut).     
Il renvoie la progression de chaque partie et le nombre de parties gagnées par chaque joueur.    

Chaque joueur à 10 millisecondes pour renvoyer son coup à l'arbitre.   
   
## Fichiers disponibles

Un fichier **main.cpp** qui choisi les joueurs, le nombre de parties et lance le jeu.   
Un fichier pour le jeu (**jeu.hh, jeu.o**).   
Un fichier pour l'arbitre (**arbitre.cc, arbitre.hh**).   
Un fichier pour le joueur brutal (**joueur_brutal.hh, joueur_brutal.o**).   
Un fichier pour le joueur random (**joueur_random.hh, joueur_random.o**).   
Un fichier pour le joueur alpha beta (**joueur_alphabeta.cc, joueur_alphabeta.hh**).   
    

## Utilisation

#### Dans un terminal à partir de la racine de ce répertoire, faire :   

```

mkdir build
cd build
cmake ..
make
./Arene_light

```

#### Pour choisir les joueurs ou le nombre de parties, il faut se rendre dans le fichier main.cpp et modifier cette ligne :

```
int nombre_parties = 100;
Arbitre a (9999, player::A_, player::BRUTAL_, nombre_parties);
```

Les joueurs disponibles sont : 

```
player::A_
player::BRUTAL_
player::RAND
```

>[!NOTE]   
>Les diagonales ne sont pas prises en compte ici. Afin de le modifier il faut juste se rendre dans le fichier joueur_alphabeta.cpp et modifier en ce sens la fonction d'évaluation.

## Auteur

Paul Lemonnier     
paul.lemonnier49070@gmail.com  
