// liste_couples.cpp		   
// Auteur: Giannela Venancio
// Date: 08/03/26
// 
// Module qui g�re la liste des coups possibles � jouer.
#include "liste_couples.h"

/************************* les FONCTIONS PUBLIQUES ***************************/

//remise � z�ro de la liste des couples possibles (NOTE: fonction donn�e aux �l�ves!)
void init_liste_couples(t_liste_couples liste) {
	//remise � VIDE du tableau (NOTE: l'utilisation des constantes ici est OBLIGATOIRE!)
	liste[LIG_INFOS][COL_TAILLE] = MAX_COUPLES;
	liste[LIG_INFOS][COL_NBELEM] = 0;
}

//Retourne le nombre de couples disponibles dans la liste
int  nb_couples(const t_liste_couples liste) {
	return liste[LIG_INFOS][COL_NBELEM];
}

//Vérifier si on peut ajouter un nouveau couple à la liste
int  ajouter_couple(t_liste_couples liste, int caseA, int caseB){

	//1)Vérifie si la liste est pleine
	if (liste [LIG_INFOS][COL_NBELEM]>= MAX_COUPLES){
		return 0;
	}

	//2)On ajoute le nouveau couple après vérification de la liste
	int nb_couple= liste[LIG_INFOS][COL_NBELEM];
	liste [nb_couple+1][0] = caseA; //ligne libre= nb_couples +1
	liste [nb_couple+1][1] = caseB;

	//3)On met à jour la liste
	liste[LIG_INFOS][COL_NBELEM] = nb_couple + 1;
	return 1;
}

//Verifier si le couple existe déjà, dans un sens ou l'autre
int  liste_contient(t_liste_couples liste, int caseA, int caseB){

	int nb_couple= liste[LIG_INFOS][COL_NBELEM];

	//Parcourir le tableau, ligne par ligne
	for (int i=1; i<=nb_couple; i++){

		int case1 = liste[i][0]; //Compare colonne 0 vs colonne 1
		int case2 = liste[i][1];

		//Si c'est le même couple dans n'importe quel aordre, return 1
		if ((case1==caseA && case2==caseB) || (case1==caseB && case2==caseA)){
			return 1;
		}
	}
	return 0;
}

//Génère un nombre aléatoire
int nb_aleatoire(int min, int max){
	return min+ (int)(rand()/(RAND_MAX+0.001)*(max-min+1));
}

//Choisir un couple au hasard
void choix_couple_alea(const t_liste_couples liste, int *caseA, int *caseB){

	int nb_couple= liste[LIG_INFOS][COL_NBELEM];

	int i = nb_aleatoire(1, nb_couple); //le choix est fait

	*caseA= liste[i][0]; // Le main recevera le couple choisi
	*caseB= liste[i][1];
}
