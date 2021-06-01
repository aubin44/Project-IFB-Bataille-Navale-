#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Depart_Grille.h"
#include "Execution_tir.h"
#include "Etat_Grille.h"

void tir(int Coo_X, int Coo_Y, Grid *grille_jeu, Grid *grille_bateau, int missile);

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
        printf("Le bateau de taille %d et d'orientation %c se trouve en (%d,%c)\n", bateau[i].taille,
               bateau[i].orientation, bateau[i].position_x + 1, 'A'+bateau[i].position_y);

        placement_bateaux(bateau, i, &grille_bateaux);

    }
    show_grid(grille_bateaux);


    do {
        choix_coo_de_tir(&Coo_X, &Coo_Y);
        do {
            check = 0;
            choix_missile(&missile);

            if (missile == 'A' && stuff.nb_missile_artillery > 0) {
                fire_artillery(&grille_de_jeu, grille_bateaux, &grille_bateaux, Coo_X, Coo_Y);
                stuff.nb_missile_artillery = stuff.nb_missile_artillery - 1;
            } else if (missile == 'T' && stuff.nb_missile_tactical > 0) {
                fire_tactical(&grille_de_jeu, grille_bateaux, &grille_bateaux, Coo_X, Coo_Y);
                stuff.nb_missile_tactical = stuff.nb_missile_tactical - 1;
            } else if (missile == 'B' && stuff.nb_missile_bomb > 0) {
                fire_bomb(&grille_de_jeu, &grille_bateaux, Coo_X, Coo_Y);
                stuff.nb_missile_bomb = stuff.nb_missile_bomb - 1;
            } else if (missile == 'S' && stuff.nb_missile_simple > 0) {
                fire_simple(&grille_de_jeu, &grille_bateaux, Coo_X, Coo_Y);
                stuff.nb_missile_simple = stuff.nb_missile_simple - 1;
            } else {
                printf("ERREUR, vous n'avez plus de ce missile");
                check = 1;
            }
        } while (check == 1);
        show_grid(grille_de_jeu);

        show_grid(grille_bateaux);
        missiles_restants(stuff);
        bateaux_restants(grille_bateaux, &nb_bateau);
    }while(nb_bateau > 0);

    printf("Youpi vous avez gagné !");
    return 0;
}

/*void tir(int Coo_X, int Coo_Y, Grid *grille_jeu, Grid *grille_bateau, int missile){

    printf("%d, %d, %d, %d\n", Coo_X, Coo_Y, missile, 'A');
    if(missile == 'A'){
        fire_artillery(&grille_jeu, *grille_bateau, &grille_bateau, Coo_X, Coo_Y);          //ESSai de fonction de tir (NE FONCTIONNE PAS)
        printf("Le missile a bien été lancé");
    }else if(missile == 'T'){
        fire_tactical(&grille_jeu, *grille_bateau, &grille_bateau, Coo_X, Coo_Y);
    }else if(missile == 'B'){
        fire_bomb(&grille_jeu, &grille_bateau, Coo_X, Coo_Y);
    }else if(missile == 'S'){
        fire_simple(&grille_jeu, &grille_bateau, Coo_X, Coo_Y);
    }else{
        printf("ERREUR");
    }
}*/