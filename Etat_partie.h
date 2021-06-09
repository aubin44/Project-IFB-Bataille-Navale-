//
// Created by Administrateur on 09/06/2021.
//

#ifndef NEW_PROJECT_IFB_ETAT_PARTIE_H
#define NEW_PROJECT_IFB_ETAT_PARTIE_H
#include "Initialisation_grille.h"

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

/**
 * Lecture de la grille dédiée au mode blind permettant d'informer les cases touchées où se trouvaient des bateaux
 * @param cases_touchees la grille en question
 */
void affichage_cases_blind(Grid cases_touchees);

/**
 * Cherche aléatoirement un bateau pouvant être déplacé (donc un bateau n'ayant pas été touché)
 * @param bateau les bateaux se trouvant sur la grille
 * @param cases_touchees le tableau de bateau
 * @return '-1' si tous les bateaux ont été touchés ou l'indice d'un des bateau choisit aléatoirement sinon
 */
int bateau_a_deplacer (Boat *bateau, Grid cases_touchees);

/**
 * Efface l'ancienne position d'un bateau dans la grille de bateau lorsque celui-ci est dépplacé en mode Active
 * @param indice_bateau le numero du bateau déplacé
 * @param bateau le bateau déplacé
 * @param tableau_bateau la grille dans laquelle se trouve le bateau
 */
void supp_ancienne_position(int indice_bateau, Boat *bateau, Grid *tableau_bateau);

void nouvelle_position(int indice, Boat *bateau, Grid *tableau_bateau);

#endif //NEW_PROJECT_IFB_ETAT_PARTIE_H
