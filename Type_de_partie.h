//
// Created by Administrateur on 09/06/2021.
//

#ifndef NEW_PROJECT_IFB_TYPE_DE_PARTIE_H
#define NEW_PROJECT_IFB_TYPE_DE_PARTIE_H
#include "Initialisation_grille.h"

/**
 * Attribue le nombre de missile en fonction du niveau de difficulté sélectionné
 * @param stuff la variable contenant le nombre de missile
 */
void choix_difficult(Inventory *stuff);

/**
 * Demande le mode de jeu désiré par le joueur et démarre une nouvelle partie dans ce mode
 * @param grille_de_jeu la grille de jeu
 * @param grille_bateaux le tableau de bateau
 * @param bateau les bateau sur la grille
 * @param check2 variable permettant de vérifier que le joueur saisisse un mode existant
 * @param stuff l'inventaire de missile
 * @param rep la variable stockant la réponse du joueur concernant le mode de jeu désiré
 * @param Coo_X le point d'impact du tir sur les abscisses
 * @param Coo_Y le point d'impact du tir sur les ordonnées
 * @param sauvegarde
 */
void lancement_nouvelle_partie(Grid grille_de_jeu, Grid grille_bateaux, Boat bateau[], int check2, Inventory stuff, char rep, int Coo_X, int Coo_Y, char sauvegarde);

/**
 * Lancement du mode de jeu Classique
 * @param stuff le nombre de missile
 * @param grille_bateaux le tableau où sont placés les bateaux
 * @param grille_de_jeu la grille utilisée pour repérer les cases touchées
 * @param Coo_X la coordonnée du point d'impact en abscisse
 * @param Coo_Y la coordonnée du point d'impact en ordonnée
 * @param sauvegarde permet de reprendre une ancienne partie
 * @return 0 si le joueur veut quitter la partie
 */
int classique(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y, char sauvegarde);

/**
 * Lancement du mode de jeu Blind
 * @param stuff le nombre de missile
 * @param grille_bateaux le tableau où sont placés les bateaux
 * @param grille_de_jeu la grille utilisée pour repérer les cases touchées
 * @param Coo_X la coordonnée du point d'impact en abscisse
 * @param Coo_Y la coordonnée du point d'impact en ordonnée
 * @param sauvegarde permet de reprendre une ancienne partie
 * @return 0 si le joueur veut quitter la partie
 */
int blind(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y, char sauvegarde);

int active(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y, char sauvegarde, Boat bateau[]);

#endif //NEW_PROJECT_IFB_TYPE_DE_PARTIE_H
