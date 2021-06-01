//
// Created by Administrateur on 29/05/2021.
//

#ifndef NEW_PROJECT_IFB_ETAT_GRILLE_H
#define NEW_PROJECT_IFB_ETAT_GRILLE_H
#include "Depart_Grille.h"

/**
 * Compte le nombre de bateaux non coulé dans le tableau de bateaux ainsi que le nombre de cases restantes par bateau
 * @param tableau_bateau
 */
void bateaux_restants(Grid tableau_bateau, int *bateau);

void missiles_restants(Inventory missile);

#endif //NEW_PROJECT_IFB_ETAT_GRILLE_H
