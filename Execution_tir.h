//
// Created by Administrateur on 29/05/2021.
//

#ifndef NEW_PROJECT_IFB_EXECUTION_TIR_H
#define NEW_PROJECT_IFB_EXECUTION_TIR_H
#include "Depart_Grille.h"

/**
 * Déclenchement du missile d'artillerie et affichage sur les grilles
 * @param grille la grille de jeu
 * @param tableau_bateau la grille de bateaux
 * @param X la coordonnée du point d'impact en abscisse
 * @param Y la coordonnée du point d'impact en ordonnée
 * @param cases_touchees la grille du mode blind
 */
void fire_artillery(Grid *grille, Grid *tableau_bateau, int X, int Y, Grid *cases_touchees);

/**
 * Déclenchement du missile tactique et affichage sur les grilles
 * @param grille la grille de jeu
 * @param tableau_bateau la grille de bateaux
 * @param X la coordonnée du point d'impact en abscisse
 * @param Y la coordonnée du point d'impact en ordonnée
 * @param cases_touchees la grille du mode blind
 */
void fire_tactical(Grid *grille, Grid *tableau_bateau, int X, int Y, Grid *cases_touchees);

/**
 * Déclenchement du missile bombe et affichage sur les grilles
 * @param grille la grille de jeu
 * @param tableau_bateau la grille de bateaux
 * @param X la coordonnée du point d'impact en abscisse
 * @param Y la coordonnée du point d'impact en ordonnée
 * @param cases_touchees la grille du mode blind
 */
void fire_bomb(Grid *grille, Grid *tableau_bateau, int X, int Y, Grid *cases_touchees);

/**
 * Déclenchement du missile simple et affichage sur les grilles
 * @param grille la grille de jeu
 * @param tableau_bateau la grille de bateaux
 * @param X la coordonnée du point d'impact en abscisse
 * @param Y la coordonnée du point d'impact en ordonnée
 * @param cases_touchees la grille du mode blind
 */
void fire_simple(Grid *grille, Grid *tableau_bateau, int X, int Y, Grid *cases_touchees);

/**
 * Demande quel missile doit être utilisé pour le prochain tir
 * @param missile le type de missile retourné
 */
void choix_missile(char *missile);

/**
 * Demande les coordonnées de tir
 * @param Coo_X la coordonnée en abscisse
 * @param Coo_Y la coordonnée en ordonnée
 */
void choix_coo_de_tir(int *Coo_X, int *Coo_Y);

/**
 * Execution du tir grâce au différents paramètres donnés par le joueur
 * @param Coo_X la coordonnée en abscisse
 * @param Coo_Y la coordonnée en ordonnée
 * @param grille_de_jeu la grille de jeu
 * @param grille_bateaux le tableaau de bateaux
 * @param missile le type de missile
 * @param stuff le nombre de missiles restants
 * @param check
 * @param cases_touchees la grille en mode blind
 */
void tir(int Coo_X, int Coo_Y, Grid *grille_de_jeu, Grid *grille_bateaux, int missile, Inventory *stuff, int *check, Grid *cases_touchees);


#endif //NEW_PROJECT_IFB_EXECUTION_TIR_H
