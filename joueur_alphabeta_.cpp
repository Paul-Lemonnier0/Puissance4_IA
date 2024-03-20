#include "joueur_alphabeta_.h"
#include <vector>

Coup max(Coup a, Coup b) { return a.score() > b.score() ? a : b; }
Coup min(Coup a, Coup b) { return a.score() < b.score() ? a : b; }

Joueur_AlphaBeta_::Joueur_AlphaBeta_(std::string nom, bool joueur)
    : Joueur(nom, joueur), _nb_coups(0)
{
    for(int i = 0; i < MAX_HAUTEUR; i++) {
        for(int j = 0; j < MAX_LARGEUR; j++) {
            tableau[i][j] = -1;
        }
    }
}

char Joueur_AlphaBeta_::nom_abbrege() const
{
    return 'A';
}


int evaluer_alignement(int alignement[4], int joueur, int opposant) {
    int score = 0;
    int score_joueur = 0;
    int score_opposant = 0;

    for (int i = 0; i < 4; ++i) {        
        if (alignement[i] == joueur) {
            ++score_joueur;
        }
        else if (alignement[i] == opposant) {
            ++score_opposant;
        }
    }

    if (score_joueur == 4){
        score += 1000;
    }

    else if (score_joueur == 3 && score_opposant == 0){
        score += 50;
    }

    else if (score_joueur == 2 && score_opposant == 0){
        score += 20;
    }

    if (score_opposant == 4){
        score -= 1000;
    }

    else if (score_opposant == 3 && score_joueur == 0){
        score -= 1000;
    }

    else if (score_opposant == 2 && score_joueur == 0){
        score -= 20;
    }

    return score;
}

int evaluate(tableauAB plateau) {
    
    int score = 0;
    int alignement[4] = {-1, -1, -1, -1};
    int joueur = 0;
    int opposant = 1;

    for (int colonne = 0; colonne < MAX_LARGEUR; ++colonne) {
        for (int ligne = 0; ligne < MAX_HAUTEUR - 3; ++ligne) {
            for (int i = 0; i < 4; ++i) {
                alignement[i] = plateau[ligne + i][colonne];
                score += evaluer_alignement(alignement, joueur, opposant);
            }
        }
    }

    for (int ligne = 0; ligne < MAX_HAUTEUR; ++ligne) {
        for (int colonne = 0; colonne < MAX_LARGEUR - 3; ++colonne) {
            for (int i = 0; i < 4; ++i) {
                alignement[i] = plateau[ligne][colonne + i];
                score += evaluer_alignement(alignement, joueur, opposant);
            }
        }
    }

    return score;
 }


bool fini (tableauAB p) {
    int compteurTotal = 0;
    int compteurJ1 = 0;
    int compteurJ2 = 0;

    for(int i = 0; i < MAX_LARGEUR; i++) {

        compteurJ1 = 0;
        compteurJ2 = 0;
        for (int j = 0;  j < MAX_HAUTEUR ; j++) {
            if(p[j][i] == 0) {
                compteurJ2=0;
                compteurJ1 +=1;
                compteurTotal += 1;
            }

            else if(p[j][i] == 1) {
                compteurJ2 += 1;
                compteurJ1 = 0;
                compteurTotal += 1;
            }

            if(compteurJ1 ==4 || compteurJ2 == 4 || compteurTotal == 42) return true;

            if(p[j][i] == -1) {
                j = MAX_HAUTEUR;
            }
        }
    }

    compteurTotal = 0;
    
    for(int i = 0; i < MAX_HAUTEUR; i++) {
        //horizontal
        compteurJ1 = 0;
        compteurJ2 = 0;
        for (int j = 0;  j < MAX_LARGEUR ; j++) {
            if(p[i][j] == 0) {
                compteurJ2=0;
                compteurJ1 +=1;
                compteurTotal += 1;
            }
            else if(p[i][j] == 1) {
                compteurJ2 += 1;
                compteurJ1 = 0;
                compteurTotal += 1;
            }

            if(compteurJ1 ==4 || compteurJ2 == 4 || compteurTotal == 42) return true;
        }
       
    }
    return false;
}


bool coupValide(int coup, tableauAB p)
{
    return p[MAX_HAUTEUR - 1][coup] == -1;
}

void jouerCoup(tableauAB &p, int coup, int joueur) {
    if(coup >= 0 && coup < MAX_LARGEUR) {
        if(coupValide(coup, p)){
            int i = 0;

            while(p[i][coup] != -1 && i < MAX_HAUTEUR) {
                ++i;
            }

            p[i][coup] = joueur;
        }
    }
}
    
int premier_coup_valide(tableauAB p) {
    for(int i = 0; i < MAX_LARGEUR; ++i) {
        if(coupValide(i, p))
            return i;
    }

    return -1;
}   

Coup alpha_beta_U(tableauAB p, Coup & alpha, Coup & beta, int Prof, int coup_init);

Coup alpha_beta_E(tableauAB p, Coup & alpha, Coup & beta, int Prof, int coup_init) {
    int coup_a_jouer = coup_init;

    if(Prof == 0 || fini(p)) {
        if(coup_a_jouer == 8) coup_a_jouer = premier_coup_valide(p);
        int score = evaluate(p);
        return Coup(coup_a_jouer, score);
    }

    Coup meilleur_coup(-1, -99999999);
    for (int coup = 0; coup < MAX_LARGEUR; coup++)
    {
        if (coupValide(coup,p))
        {
            tableauAB CopiePlateau;
            for(int i = 0; i < MAX_HAUTEUR; i++) {
                for(int j = 0; j < MAX_LARGEUR; j++) {
                    CopiePlateau[i][j] = p[i][j];
                }
            }  
            
            coup_a_jouer = coup;

            jouerCoup(CopiePlateau, coup, 0);

            Coup s = alpha_beta_U(CopiePlateau, alpha, beta, Prof - 1, coup_a_jouer);
            meilleur_coup = max(meilleur_coup, s);

            if (meilleur_coup.score() >= beta.score())
                return meilleur_coup;

            alpha = max(meilleur_coup, alpha);
        }
    }

    return meilleur_coup;
}

Coup alpha_beta_U(tableauAB p, Coup & alpha, Coup & beta, int Prof, int coup_init) {
    if(Prof == 0 || fini(p)) {
        int score = evaluate(p);
        return Coup(coup_init, score);
    }

    Coup meilleur_coup(-1, 99999999);

    for (int coup = 0; coup < MAX_LARGEUR; coup++)
    {
        if (coupValide(coup, p))
        {
            tableauAB CopiePlateau;
            for(int i = 0; i < MAX_HAUTEUR; i++) {
                for(int j = 0; j < MAX_LARGEUR; j++) {
                    CopiePlateau[i][j] = p[i][j];
                }
            }
            
            jouerCoup(CopiePlateau, coup, 1);
            
            meilleur_coup = min(meilleur_coup, alpha_beta_E(CopiePlateau, alpha, beta, Prof - 1, coup));

            if (meilleur_coup.score() <= alpha.score())
                return meilleur_coup;

            beta = min(meilleur_coup, beta);
        }
    }
    
    return meilleur_coup;
}

void Joueur_AlphaBeta_::recherche_coup(Jeu jeu, int &coup)
{
    Coup alpha(-1, -99999999);
    Coup beta(-1, 99999999);

    if(coup >= -7 && coup <= 7) jouerCoup(tableau, abs(coup)-1, 1);
    ++_nb_coups;

    int profondeur = (_nb_coups > 6) ? 4 : 1;

    Coup meilleurCoup = alpha_beta_E(tableau, alpha, beta, profondeur, 8);

    jouerCoup(tableau, meilleurCoup.coup(), 0);

    coup = meilleurCoup.coup();
}




