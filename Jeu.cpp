#define _CRT_SECURE_N0_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"

void jouer(void) {
    t_grille_nos grille = {0};
    t_liste_couples liste_coups = {0};
    t_tab_chiffres chiffres_dispos = {0};

    int derniere_lig = 0;
    int caseA = 0, caseB = 0;
    int score = 0;
    int quitter = 0;
    int nb_coups = 0;
    int regen = 0;
    int nb_regen = 3;

    afficher_instructions();
    init_rand();
    derniere_lig = init_grille(grille, chiffres_dispos);
    afficher_infos_jeu(chiffres_dispos, score);
    afficher_grille(grille, derniere_lig);

    while(!quitter) {
          init_liste_couples(liste_coups);
          nb_coups = genere_liste_couples(grille, derniere_lig, liste_coups);

          if(nb_coups > 0) {
