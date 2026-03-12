//grilles_chiffres.cpp
//Auteur: Giannela Venancio
//Date: 08/02/26

//Module qui vérifie qu'un chiffre n'apparaisse pas deux fois dans un même voisinnage

#include "grille_chiffres.h"
#include "liste_couples.h"

static int verifier_ch_voisins(const t_grille_nos grille, int lig, int col, int chif) {

    //Vérifier si le case d'en haut existe
    if (lig-1>=0) {
        //Vérifier si la case n'est pas vide
        if (grille[lig-1][col]!=0) {
            //Vérifier si la case d'en haut == chif
            if (grille[lig-1][col]==chif) {
                return 0;
            }
        }
    }
    //Vérifier si le case d'en haut à droite existe
    if (lig-1>=0 && col+1<NB_COL) {  //Il y a une colonne dédié au nombre de chiffres
        //Vérifier si la case n'est pas vide
        if (grille[lig-1][col+1]!=0) {
            //Vérifier si la case d'en haut == chif
            if (grille[lig-1][col+1]==chif) {
                return 0;
            }
        }
    }
    //Vérifier si le case d'en haut à gauche existe
    if (lig-1>=0 && col-1>=1) { // col case 0=nb de chiffres
        //Vérifier si la case n'est pas vide
        if (grille[lig-1][col-1]!=0) {
            //Vérifier si la case d'en haut == chif
            if (grille[lig-1][col-1]==chif) {
                return 0;
            }
        }
    }
    //Vérifier si le case à gauche existe
    if (col-1>=1) {
        //Vérifier si la case n'est pas vide
        if (grille[lig][col-1]!=0) {
            //Vérifier si la case d'en haut == chif
            if (grille[lig][col-1]==chif) {
                return 0;
            }
        }
    }
    //Vérifier si le case en bas à gauche existe
    if (lig+1<MAX_LIG && col-1>=1) {
        //Vérifier si la case n'est pas vide
        if (grille[lig+1][col-1]!=0) {
            //Vérifier si la case d'en haut == chif
            if (grille[lig+1][col-1]==chif) {
                return 0;
            }
        }
    }
    //Vérifier si le case d'en bas existe
    if (lig+1<MAX_LIG) {
        //Vérifier si la case n'est pas vide
        if (grille[lig+1][col]!=0) {
            //Vérifier si la case d'en haut == chif
            if (grille[lig+1][col]==chif) {
                return 0;
            }
        }
    }
    //Vérifier si le case en bas à droite existe
    if (lig+1<MAX_LIG && col+1<NB_COL) {
        //Vérifier si la case n'est pas vide
        if (grille[lig+1][col+1]!=0) {
            //Vérifier si la case d'en haut == chif
            if (grille[lig+1][col+1]==chif) {
                return 0;
            }
        }
    }
    //Vérifier si le case à droite existe
    if (col+1<NB_COL) {
        //Vérifier si la case n'est pas vide
        if (grille[lig][col+1]!=0) {
            //Vérifier si la case d'en haut == chif
            if (grille[lig][col+1]==chif) {
                return 0;
            }
        }
    }
    //S'il n'y a pas chiffre identique:
    return 1;
}
// L'initialisation de la grille
int init_grille(t_grille_nos grille, t_tab_chiffres nbr_chiffres) {

    //initialisation de la grille
    for (int i=0; i<MAX_LIG; i++) {
        for (int j=0; j<NB_COL; j++) {
            grille[i][j] =0;
        }
    }
    //Initialise la liste de chiffres disponibles
    for (int i=0;i<NB_COL; i++) {
        nbr_chiffres[i]=0;
    }

    //On détermine le nombre initial de chiffres à générer
    double facteur= reel_aleatoire(4.0,5.0);
    int nb_chiffres = facteur *9;

    if (nb_chiffres % 2 == 1) {
        nb_chiffres++; //augmente +1 pour avoir un nombre pair
    }

    int lig=0;
    int col=1;
    int chif;

    //On génère les chiffres
    for (int i = 0; i < nb_chiffres; i++) {
        chif = entier_aleatoire(1, 9);

        //Faire appel à une fonction => vérifier chaque voisin
        while (verifier_ch_voisins(grille, lig, col, chif) ==0) {
            chif = entier_aleatoire(1, 9); //Si le chiffre pas valide, il repigera
        }
        //On place le bon chiffre dans la grille
        grille[lig][col]= chif;

        //On met à jour le tableau
        nbr_chiffres[chif]++; //Le nombre d'occurrences d'un chiffre en particulier
        grille[lig][0]++; //Le nombre de chiffres sur cette ligne
        nbr_chiffres[0]++; //Le nombre total des chiffres

        INC_POS(lig, col); //On avance la position
    }

    //Au cas où un chiffre n'apparait jamais dans la grille
    for (int chiffre=1; chiffre <= 9;chiffre++) {
        if (nbr_chiffres[chiffre]==0) {  //Si un chiffre est apparu 0 fois, faire:

            grille[lig][col]= chiffre;

            //Et il faut mettre à jour les compteurs
            grille[lig][0]++;
            nbr_chiffres[chiffre]++;
            nbr_chiffres[0]++;

            INC_POS(lig,col);
        }
    }
    return lig;
}

//Création du couple, direction est, cas spécial
static void verifier_sens_est(t_grille_nos grille, int lig, int col, t_liste_couples liste){

    int lig2=lig; //Case à explorer
    int col2=col;
    int chiffre1= grille[lig][col];

    INC_POS (lig2, col2); //On débute

    while (col2< NB_COL && grille[lig2][col2]==0) { //On saut les 0

        INC_POS(lig2, col2); //On avance grâce à la macro-fonction vers la droite
    }
    if (col2<NB_COL) { //Vérifie si on est encore dans la grille
        int chiffre2= grille[lig2][col2];

        if (chiffre1==chiffre2 || chiffre1+chiffre2==10) {
            ajouter_couple(liste, lig*10+col, lig2*10+col2);
        }
    }

}

//Création des couples, vers tous les directions sauf est
static void verifier_huit_directions(t_grille_nos grille, int lig, int col, t_liste_couples liste) {

    int ligN = lig -1; //On va vers le nord
    int colN= col;
    int chiffre1= grille[lig][col]; //Le point de départ, donc premier chiffre

    while (ligN>=0 && grille [ligN][colN]==0) { //On avance vers le haut
       ligN--; //Car on veut diminuer le compteur, on monte, les indices diminuent
    }
    if (ligN>=0){
        int chiffre2= grille[ligN][colN]; // Le chiffre retrouvé grâce au while (le couple est fait)
        //Vérifier si c'est un bon couple et l'ajouter dans la liste
        if (chiffre1==chiffre2 || chiffre1 +chiffre2==10) {
            ajouter_couple(liste, lig*10+col, ligN*10+colN); 
        }
    }

    int ligO= lig; //On va vers l'ouest
    int colO= col-1;

    while (colO>=1 && grille[ligO][colO]==0) { //On avance vers la gauche
        colO--; //L'indice doit diminuer car vers la gauche
    }
    if (colO>=1) {
        int chiffre2= grille[ligO][colO];

        //Vérifier si c'Est un bon couple et on l'ajoute dans la liste
        if (chiffre1==chiffre2 || chiffre1 +chiffre2 ==10){
            ajouter_couple(liste, lig*10+col, ligO*10+colO);
        }
    }
    
    int ligS= lig+1;
    int colS= col;

    while (ligS<MAX_LIG && grille[ligS][colS]==0) { //On avance vers le bas et sautant les 0
        ligS++; //L'indice augmente, donc +
    }
    if (ligS<MAX_LIG) {
        int chiffre2= grille[ligS][colS];

        //Vérifier si c'est un bon couple et on l'ajoute dans la liste
        if (chiffre1==chiffre2 || chiffre1 +chiffre2 ==10){
            ajouter_couple(liste, lig*10+col, ligS*10+colS);
        }
    }
    
    int ligNO= lig-1; //Vers le nord-ouest
    int colNO= col-1;

    while (ligNO>=0 && colNO >= 1 && grille[ligNO][colNO]==0) {  //On avance vers haut à gauche
        ligNO--; // L'indice diminue
        colNO--; // L'indice diminue
    }
    if (ligNO>=0 && colNO >=1) {
        int chiffre2= grille[ligNO][colNO];
        //Vérifier si c'est un bon couple et si c'est le cas on l'ajoute dans la liste
        if (chiffre1==chiffre2 || chiffre1 + chiffre2==10) {
            ajouter_couple(liste, lig*10+col, ligNO*10+colNO);
        }
    }
    
    int ligNE= lig-1;
    int colNE= col+1;

    while (ligNE>=0 && colNE< NB_COL && grille[ligNE][colNE]==0) {
        ligNE--; //Vers le haut, l'indice diminue
        colNE++; //Vers la droite, l'indice augmente
    }
    if (ligNE>=0 && colNE < NB_COL) {
        int chiffre2= grille[ligNE][colNE];
        //Vérifiez si le couple est correct et on l'ajoute dans la liste
        if (chiffre1==chiffre2 || chiffre1+chiffre2==10) {
            ajouter_couple(liste, lig*10+col, ligNE*10+colNE);
        }
    }
    
    int ligSO=lig+1;
    int colSO=col-1;

    while (ligSO<MAX_LIG && colSO>=1 && grille[ligSO][colSO]==0){
        ligSO++; //Vers le bas = l'indice augmente
        colSO--; //Vers la gauche = l'indice diminue
    }
    if (ligSO< MAX_LIG && colSO>=1) {
        int chiffre2= grille[ligSO][colSO];
        //Vérifiez si le couple est correct et on l'ajoute dans la liste
        if (chiffre1==chiffre2 || chiffre1+chiffre2==10) {
            ajouter_couple(liste, lig*10+col, ligSO*10+colSO);
        }
    }
    
    int ligSE= lig+1;
    int colSE= col+1;

    while (ligSE< MAX_LIG && colSE < NB_COL && grille[ligSE][colSE]==0) {
        ligSE++; //Vers le bas, l'indice augmente
        colSE++; //Vers la droite, l'indice augmente
    }
    if (ligSE<MAX_LIG && colSE < NB_COL) {
        int chiffre2= grille[ligSE][colSE];
        //Vérifiez si le couple est correct et on l'ajoute dans la liste
        if (chiffre1==chiffre2 || chiffre1+chiffre2==10) {
            ajouter_couple(liste, lig*10+col, ligSE*10+colSE);
        }
    }
    //Vérifiez direction est
    verifier_sens_est(grille, lig, col, liste);
}

int generer_listes_couples(t_grille_nos grille, int derniere_lig, t_liste_couples liste) {

    init_liste_couples(liste);
    
    for (int lig=0; lig<=derniere_lig; lig++){
        for (int col=1; col< NB_COL; col++) {
            if (grille[lig][col] !=0) {
                verifier_huit_directions(grille, lig, col, liste);
            }
        }
    }
    return nb_couples(liste);
}
