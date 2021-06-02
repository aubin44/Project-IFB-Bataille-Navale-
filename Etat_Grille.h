//
// Created by Administrateur on 29/05/2021.
//

#ifndef NEW_PROJECT_IFB_ETAT_GRILLE_H
#define NEW_PROJECT_IFB_ETAT_GRILLE_H
#include "Depart_Grille.h"

/**
 * Compte le nombre de bateaux non coulés dans le tableau de bateaux ainsi que le nombre de cases restantes par bateau
 * @param tableau_bateau
 */
void bateaux_restants(Grid tableau_bateau, int *bateau);

/**
 * affiche le nombre restant de chaque missile
 * @param missile
 */
void missiles_restants(Inventory missile);

/**
 * Après avoir vérifier que le nombre de missile restant est égal à 0, affiche que le joueur a perdu
 * @param nb_missile
 */
void check_loose(Inventory nb_missile);

#endif //NEW_PROJECT_IFB_ETAT_GRILLE_H