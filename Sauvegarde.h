//
// Created by Administrateur on 09/06/2021.
//

#ifndef NEW_PROJECT_IFB_SAUVEGARDE_H
#define NEW_PROJECT_IFB_SAUVEGARDE_H
#include "Initialisation_grille.h"

/**
 * Sauvegarde la position des bateaux ainsi que le nombre de missile
 * @param tableau_bateau la grille de bateaux
 * @param missile le nombre de missile
 * @param mode le mode de jeu
 */
void save(Grid tableau_bateau, Inventory missile, int mode);

/**
 * Redémarre une ancienne partie sauvegardée
 * @param tableau_bateau la grille de bateaux
 * @param missile le nombre de missile
 * @param mode le mode de jeu
 */
void load(Grid *tableau_bateau, Inventory *missile, int *mode);

/**
 * Initialise la grille de jeu lorsque l'on relance une partie sauvegardée
 * @param tableau_bateau la grille de bateau
 * @param grille la grille de jeu
 */
void init_save(Grid *tableau_bateau, Grid *grille);

void lancement_mode_sauvegarde(Inventory stuff, int mode, Grid grille_bateaux, char sauvegarde, int Coo_X, int Coo_Y, Grid grille_de_jeu);

#endif //NEW_PROJECT_IFB_SAUVEGARDE_H
