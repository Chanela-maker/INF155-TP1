#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "liste_couples.h"
#include "grille_chiffres.h"
#include "utilitaires.h"

void init_liste_couples(t_liste_couplesliste) {
      liste[LIG_INFOS][COL_TAILLE]= MAX_COUPLES;
      liste[LIG_INFOS][COL_NBELEM] = 0;
}

int nb_couples(const t_liste_couplesliste) {
    returnliste[LIG_INFOS][COL_NBELEM];
}

int liste_contient(const t_liste_couplesliste,int caseA,int caseB) {
    int total_couples = nb_couples(liste);

    for (int i = 1; i <= total_couples; i++){
        if ((liste[i][0] == caseA && liste[i][1] == caseB) ||
            (liste[i][0] == caseB && liste[i][1] == caseA)) {
            return 1;
        }
    }

    return 0;
}

int ajouter_couple(t_liste_couples liste, int caseA, int caseB) {
    int total_couples = nb_couples(liste);

    if (total_couples < liste[LIG_INFOS][COL_TAILLE]) {
        if (!liste_contient(liste, caseA, caseB)) {
            total_couples++;

            liste[total_couples][0] = caseA;
            liste[total_couples[1] = caseB;

            liste[LIG_INFOS][COL_NBELEM] = total_couples;
            return 1;
        }
    }
    return 0;
}

int generer_liste_couples(const t_grille_nod grille,int derniere_ligne, t_liste_couples liste) {
    for (int i =0; i <= derniere_ligne; i++) {
        for (int j = 1; j <= 9; j++) {
            int val1 = grille[i][j];

            if (val1 == 0) {
                continue;
            }

            int posA = (i * 10) + j;
            int r, c, val2;

            r = i;
            c = j + 1
            while (r <= derniere_ligne) {
                  if (c > 9) { r++; c = 1; continue;}
                  val2 = grille[r][c];
                  if (val2 != 0) {
                      if (val1 == val2 || val1 + val2 == 10) {
                          ajouter_couple(liste, posA, (r * 10) + c);
                      }

                      break;
                  }

                  c++;
            }

            r = i + 1;
            c = j;
            while (r <=derniere_ligne) {
                  val2 = grille[r][c];
                  if (val2 != 0) {
                      if (val1 == val2 || val1 + val2 == 10) {
                          ajouter_couple(liste, posA, (r * 10) + c);
                      }

                      break;
                  }

                  r++;
            }

            r = i + 1;
            c = j + 1;
            while (r <= derniere_ligne && c <= 9) {
                  val2 = grille[r][c];
                  if (val2 != 0) {
                      if (val1 == val2 || val1 + val2 == 10) {
                          ajouter_couple(liste, posA, (r * 10) + c);
                      }

                      break;
                  }

                  r++; c++;
            }

            r = i + 1;
            c = j- 1;
            while (r <= derniere_ligne && c >= 1) {
                  val2 = grille[r][c];
                  if (val2 != 0) {
                      if (val1 == val2 || val1 + val2 == 10) {
                          ajouter_couple(liste, posA, (r * 10) + c);
                      }

                      break;
                  }

                  r++; c++;
            }
        }
    }

    return nb_couples(liste);
}

void choix_couple_alea(const t_liste_couples liste, int *suggA, int suggB) {
      int total_couples = nb_couples(liste);

      if (total_couples > 0) {
          int index_alea = entier_aleatoire(1, total_couples);
          *suggA = liste[index_alea][0];
          *suggB = liste[index_alea][1];
      } else {
        *suggA = 0;
        *suggB = 0;
      }
}
