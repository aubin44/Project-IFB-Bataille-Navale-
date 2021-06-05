//
// Created by anais on 27/05/2021.
//

#ifndef NEW_PROJECT_IFB_DEPART_GRILLE_H
#define NEW_PROJECT_IFB_DEPART_GRILLE_H

typedef struct{
    int position_x;
    int position_y;
    int taille;
    int orientation;
}Boat;

typedef struct{
    char grille[10][10];
    int hauteur;
    int largeur;
}Grid;

typedef struct{
    int nb_missile_artillery;
    int nb_missile_tactical;
    int nb_missile_bomb;
    int nb_missile_simple;
}Inventory;

/**
 * Initialise la grille
 * @param grille
 */
void init_grille(Grid *grille);

/**
 * Affiche la grille
 * @param grille
 */
void show_grid(Grid grille);

/**
 * Vérifie que le bateau généré appartienne à la grille
 * @param bateau le bateau généré
 * @param i
 * @return 0 si le bateau appartient à la grille 1 sinon
 */
int app_grille(Boat bateau[], int i);

/**
 * Place le bateau généré sur la grille de bateaux
 * @param bateau le bateau généré
 * @param i
 * @param grille_bateaux
 */
void placement_bateaux(Boat *bateau, int i, Grid *grille_bateaux);

/**
 * Génere aléatoirement la position (x,y) ainsi que l'orientation 'H' ou 'V' d'un bateau
 * @param bateau
 * @param i
 * @param grille_bateau
 */
void genere_bateau(Boat *bateau, int i, Grid grille_bateau);

/**
 * Vérifie que le bateau généré ne chevauche pas un bateau déjà placé
 * @param bateau le bateau généré
 * @param i
 * @param grille_bateau
 * @return 0 si le bateau ne chevauche pas d'autres bateaux 1 sinon
 */
int chevauchement(Boat *bateau,int i, Grid grille_bateau);

/**
 * Attribue le nombre de missile en fonction du niveau de difficulté sélectionné
 * @param stuff la variable contenant le nombre de missile
 */
void choix_difficult(Inventory *stuff);

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

/**
 * Lecture de la grille dédiée au mode blind permettant d'informer les cases touchées où se trouvaient des bateaux
 * @param cases_touchees la grille en question
 */
void affichage_cases_blind(Grid cases_touchees);

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

#endif //NEW_PROJECT_IFB_DEPART_GRILLE_H
