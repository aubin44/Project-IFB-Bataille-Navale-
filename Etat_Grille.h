//
// Created by Administrateur on 29/05/2021.
//

#ifndef NEW_PROJECT_IFB_ETAT_GRILLE_H
#define NEW_PROJECT_IFB_ETAT_GRILLE_H
#include "Depart_Grille.h"

/**
 * Compte le nombre de bateaux non coulés dans le tableau de bateaux ainsi que le nombre de cases restantes par bateau
 * @param tableau_bateau la grille de bateaux
 */
void bateaux_restants(Grid tableau_bateau, int *bateau);

/**
 * Affiche le nombre restant de chaque missile
 * @param missile le type de missile
 */
void missiles_restants(Inventory missile);

/**
 * Après avoir vérifier que le nombre de missile restant est égal à 0, affiche que le joueur a perdu
 * @param nb_missile le nombre de chaque missile
 */
int check_loose(Inventory nb_missile);

#endif //NEW_PROJECT_IFB_ETAT_GRILLE_H