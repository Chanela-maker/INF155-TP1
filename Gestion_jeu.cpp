#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "gestion_jeu.h"

#define CHIFFRE_A_VAL(ch) ((ch) - '0')
#define LETTRE_A_COL(let) (toupper(let) - 'A' + 1)
#define COL_A_LETTRE(col) ((col) - 1 + 'A')

static int saisie_case(int derniere_ligne_active, int numero_saisie) {
        char chaine[10];
        int valide = 0;
        int position_retour = -1;

        while (!valide) {
            demander_saisie(numero_saisie);
            scanf("%s", chaine);

            if(strcmp(chaine, "XX") == 0 || strcmp(chaine, "XX") == 0) return CODE_QUITTER;
            if(strcmp(chaine, "??") == 0) return CODE_AIDE;
            if(strcmp(chaine, "++") == 0) return CODE_CHIFFRES;

            int len = strlen(chaine);
            if(len == 2 || len == 3) {
              char lettre = chaine[0];

              if(isalpha(lettre)) {
                int col = LETTRE_A_COL(lettre);

                if(col >= 1 && col <= 9) {
                  if(isdigit(chaine[1])) {
                    int rangee = CHIFFRE_A_VAL(chaine[1]);

                    if(len == 3) {
                      if(isdigit(chaine[2])) {
                        rangee = (rangee * 10) + CHIFFRE_A_VAL(chaine[2]);
                      } else {
                        rangee = -1;
                      }
                    }

                    if(rangee != -1) {
                      int vrai_indice_ligne = rangee - 1;

                      if(vrai_indice_ligne >= 0 && vrai_indice_ligne <= derniere_ligne_active) {
                        position_retour = (vrai_indice_ligne * 10) + col;
                        valide = 1;
                      }
                    }
                }
              }
            }
          }

          if(!valide) {
            mess_erreur("Erreur: Casw non-valide ou hors limites.");
          }
        }
        return position_retour;
}

int valider_coup(t_liste_couples liste, int derniere_ligne, int *caseA, int *caseB) {
    int valide = 0;
    while(!valide){
        *caseA = saisie_case(derniere_ligne, 1);
        if(*caseA <= 0) return 0;
        *caseB = saisie_case(derniere_ligne, 2);
        if(*caseB <= 0) return 0;

        if(liste_contient(liste, *caseA, *caseB)) {
          valide = 1;
        } else {
          mess_erreur("Erreur: Ce coup n'est pas dans la liste des coups possibles.");
        }
    }

    return 1;
}

int jouer_coup(t_grille_nos grille, int caseA, int caseB, t_tab_chiffres dispos, int *derniere_ligne) {
    int points = 0;
    int pts_lignes = 0;

    if(abs(caseA - caseB) == 1) {
      points += PTS_COUPLE_VOISIN;
      mess_points(PTS_COUPLE_VOISIN);
    } else {
      points += PTS_COUPLE_SEPARE;
      mess_points(PTS_COUPLE_SEPARE);
    }

    int chA = get_chiffre_case(grille, caseA);
    int retA = retirer_chiffre(chA, dispos);
    if(retA != 0) {
      char msg[50];
      sprintf(msg, "Le chiffre %d est elimine du jeu!", retA);
      message(msg);
    }

    effacer_chiffre(grille, caseA);
    int chB = get_chiffre_case(grille, caseB);
    int retB = retirer_chiffre(chB, dispos);
    if(retB != 0) {
      char msg[50];
      sprintf(msg, "Le chiffre %d est elimine du jeu!", retB);
      message(msg);
    }

    effacer_chiffre(grille, caseB);
    if(caseA < caseB) {
      int tmp = caseA;
      caseA = caseB;
      caseB = tmp;
    }
  int ligneA = caseA / 10;
  int ligneB = caseB / 10;

  if(grille[ligneA][POS_NB] == 0) {
    retirer_ligne(grille, ligneA);
    pts_lignes += PTS_LIGNE_RETIREE;
    (*derniere_ligne)--;
  }

  if(ligneB != ligneA && grille[ligneB][POS_NB] == 0) [
    retirer_ligne(grille, ligneB);
    pts_lignes += PTS_LIGNE_RETIREE;
    (*derniere_ligne)--;
  }

  if(pts_lignes > 0) {
    char msg_lignes[50];
    sprintf(msg_lignes, "%d Ligne(s) retiree(s) : +%d points", pts_lignes / PTS_LIGNE_RETIREE, pts_lignes);
    message(msg_lignes);
  }

  return points + pts_lignes;
}
