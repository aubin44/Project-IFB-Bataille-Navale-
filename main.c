#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Depart_Grille.h"
#include "Execution_tir.h"
#include "Etat_Grille.h"


int main(){
    Grid grille_de_jeu, grille_bateaux;
    Boat bateau[5];
    Inventory stuff;
    grille_de_jeu.hauteur = 10;     //Initialisation de la taille des grilles de jeu
    grille_de_jeu.largeur = 10;
    grille_bateaux.hauteur = 10;
    grille_bateaux.largeur = 10;
    int Coo_X, Coo_Y;
    int i;
    int check, nb_bateau;
    char missile;
    srand(time(0));

    bateau[0].taille = 5;           //Initialisation de la taille des 5 bateaux
    bateau[1].taille = 4;
    bateau[2].taille = 3;
    bateau[3].taille = 3;
    bateau[4].taille = 2;

    init_grille(&grille_bateaux);
    init_grille(&grille_de_jeu);
    choix_difficult(&stuff);

    for(i = 0; i < 5; i++){
        do {
            genere_bateau(&bateau, i, grille_bateaux);

        } while (app_grille(bateau, i) == 1 || chevauchement(bateau, i, grille_bateaux) == 1);
        /*printf("Le bateau de taille %d et d'orientation %c se trouve en (%d,%c)\n", bateau[i].taille,
               bateau[i].orientation, bateau[i].position_x + 1, 'A'+bateau[i].position_y);*/                //Verif code

        placement_bateaux(bateau, i, &grille_bateaux);

    }
    show_grid(grille_bateaux);                      //Vérif code


    do {
        check_loose(stuff);
        choix_coo_de_tir(&Coo_X, &Coo_Y);
        while(grille_bateaux.grille[Coo_X][Coo_Y] <= 'F'){
            printf("Vous avez déjà tirez sur cette case !");
            choix_coo_de_tir(&Coo_X, &Coo_Y);
        }
        do {
            check = 0;
            choix_missile(&missile);
            tir(Coo_X, Coo_Y, &grille_de_jeu, &grille_bateaux, missile, &stuff, &check);
        } while (check == 1);
        show_grid(grille_de_jeu);

        show_grid(grille_bateaux);                  //Verif code
        missiles_restants(stuff);
        bateaux_restants(grille_bateaux, &nb_bateau);

    }while(nb_bateau > 0);

    printf("Youpi vous avez gagné !");
    return 0;
}
