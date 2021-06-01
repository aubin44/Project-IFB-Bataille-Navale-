//
// Created by Administrateur on 29/05/2021.
//

#ifndef NEW_PROJECT_IFB_EXECUTION_TIR_H
#define NEW_PROJECT_IFB_EXECUTION_TIR_H
#include "Depart_Grille.h"


void fire_artillery(Grid *grille, Grid *bateau, int X, int Y);

void fire_tactical(Grid *grille, Grid *bateau, int X, int Y);

void fire_bomb(Grid *grille, Grid *tableau_bateau, int X, int Y);

void fire_simple(Grid *grille, Grid *tableau_bateau, int X, int Y);

void choix_missile(char *missile);

/**
 * Demande les coordonnées de tir
 * @param Coo_X
 * @param Coo_Y
 */
void choix_coo_de_tir(int *Coo_X, int *Coo_Y);

#endif //NEW_PROJECT_IFB_EXECUTION_TIR_H
