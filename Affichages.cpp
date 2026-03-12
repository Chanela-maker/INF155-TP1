#define _CRT_SECURE_NO_WARNINGS
#define <stdio.h>
#define <stdlib.h>
#include "WinConsole.h"
#include "affichages.h"
#define CH_MAX 9

void afficher_infos_jeu(const t_tab_chiffres nbr_chiffres, int pts) {
  gotoxy(COL_GRILLE + 12, LIG_POINTS);
  printf("Score: %d", pts);
  clreol();

  gotoxy(COL_GRILLE, LIG_CHIFFRES);
  printf("Chiffres:");

  for(int i = 1; i <= CH_MAX; i++) {
      if(nbr_chiffres[i] > 0) {
        printf("%d", i);
      } else {
        printf(" ");
      }
  }
  clreol();
}

void afficher_grille(const t_grille_nos grille, int dern_lig) {
    gotoxy(COL_GRILLE, LIG_GRILLE);
    textcolor(YELLOW);
    printf(" ");
    for(int col = 0; col < 9; col++) {
        printf("%c", 'A' + col);
    }

    for(int i = 0; i <= dern_lig; i++) {
        gotoxy(COL_GRILLE, LIG_GRILLE + 1 + i);

        textcolor(YELLOW);
        printf("%d", i + 1);

        textcolor(WHITE);

        for(int j = 1; j <= 9; j++) {
            if(grille[i][j] == 0) {
              printf(" ");
            } else {
              printf("%d", grille[i][j]);
            }
        }
        clreol();
    }

    for(int i = dern_lig + 1; i < MAX_LIG; i++) {
        gotoxy(COL_GRILLE, LIG_GRILLE + 1 + i);
        clreol();
    }
}

void afficher_instructions() {
      clrscr();
      textcolor(WHITE);
      gotoxy(10, 2);
      printf("=========================================================================");
      gotoxy(10, 3);
      printf(" JEU NUMBER MATCH ");
      gotoxy(10, 4);
      printf("==========================================================================");
      gotoxy(10, 6);
      printf("===========================================================================");
      gotoxy(10, 8);
      printf("Commandes ; ");
      gotoxy(10, 9);
      printf(" XX : Quitter le jeu");
      gotoxy(10, 10);
      printf("?? : Obtenir un indice");
      gotoxy(10, 11);
      printf("++ : Regenerer des chiffres");
      gotoxy(10, 14);
      printf("Appuyer sur ENTER pour commencer...");
      getchar();
      clrscr();
}

void afficher_couple(int colA, int ligA, int chA, int colB, int ligB, int chB) {
    int ecran_colA = COL_GRILLE + 1 + (colA * 2);
    int ecran_ligA = LIG_GRILLE + 1 + ligA;
    int  ecran_colB = COL_GRILLE + 1 + (colB * 2);
    int ecran_ligB = LIG_GRILLE + 1 + ligB;

    textcolor(LIGHTBLUE);
    gotoxy(ecran_colA, ecran_ligA); printf("%d", chA);
    gotoxy(ecran_colB, ecran_ligB); printf("%d", chB);

    delay(5000);

    textcolor(WHITE);
    gotoxy(ecran_colA, ecran_ligA); printf("%d", chA);
    gotoxy(ecran_colB, ecran_ligB); printf("%d", chB);
}

void message(const char* mess) {
    textcolor(WHITE);
    gotoxy(COL_GRILLE, LIG_MESSAGES);
    printf("%s", mess);
    clreol();
    delay(2000);
}

void mess_erreur(const char* mess) {
      for(int i = 0; i < 5; i++) {
          gotoxy(COL_GRILLE, LIG_MESSAGES);
          textcolor(LIGHTRED);
          printf("%s", mess);
          delay(500);
          gotoxy(COL_GRILLE, LIG_MESSAGES);
          clreol();
          delay(200);
      }
      textcolor(WHITE);
}

void mess_points(int pts) {
      for(int i = 0; i < 3; i++) {
          gotoxy(COL_GRILLE + 20, LIG_POINTS);
          textcolor(LIGHTGREEN);
          printf("+&d points!!", pts);
          delay(300);
          gotoxy(COL_GRILLE + 20, LIG_POINTS);
          clreol();
          delay(100);
      }
      textcolor(WHITE);
}

