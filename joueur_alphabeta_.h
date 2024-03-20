#pragma once

#include "joueur.h"
#include <vector>
#include <stdlib.h>

#define MAX_HAUTEUR 6
#define MAX_LARGEUR 7

class Coup
{
private:
  int _coup;
  int _score;

public:
  Coup(int coup, int score) : _coup(coup), _score(score){};
  int coup() const { return _coup;};
  int score() const { return _score;};
};

using tableauAB = int[6][7];

class Joueur_AlphaBeta_ : public Joueur
{
 public:
    tableauAB tableau;

    int _nb_coups;

    Joueur_AlphaBeta_(std::string nom, bool joueur);
    char nom_abbrege() const override;

    void recherche_coup(Jeu, int &coup) override;

    void afficher_tableau_interne() const {
      for(int i = MAX_HAUTEUR-1; i >= -1; --i) {
        if(i == -1) {
          for(int k = 0; k<MAX_LARGEUR; ++k) {
            std::cout<<"|"<<k+1;
          }

          std::cout<<"|"<<std::endl;
        }

        else {
          for(int j = 0; j < MAX_LARGEUR; ++j) {
            std::cout<<"|";

            if(tableau[i][j] == -1) std::cout<<" ";
            else if(tableau[i][j] == 0) std::cout<<"x";
            else std::cout<<"o";
          }

          std::cout<<"|"<<std::endl;
        }
      }
    }
};