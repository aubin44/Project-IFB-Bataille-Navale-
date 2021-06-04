#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
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
    int check, nb_bateau, check2;
    char missile, rep;
    srand(time(0));

    bateau[0].taille = 5;           //Initialisation de la taille des 5 bateaux
    bateau[1].taille = 4;
    bateau[2].taille = 3;
    bateau[3].taille = 3;
    bateau[4].taille = 2;

    load(&grille_bateaux, &stuff);
    show_grid(grille_bateaux);

    init_grille(&grille_bateaux);
    init_grille(&grille_de_jeu);


    for(i = 0; i < 5; i++){
        do {
            genere_bateau(&bateau, i, grille_bateaux);

        } while (app_grille(bateau, i) == 1 || chevauchement(bateau, i, grille_bateaux) == 1);
        /*printf("Le bateau de taille %d et d'orientation %c se trouve en (%d,%c)\n", bateau[i].taille,
               bateau[i].orientation, bateau[i].position_x + 1, 'A'+bateau[i].position_y);*/                //Verif code

        placement_bateaux(bateau, i, &grille_bateaux);

    }
    /*show_grid(grille_bateaux);*/                      //Vérif code

    do {
        check2 = 0;
        printf("Veuillez saisir le mode de jeu souhaité :\n -C : Mode Classique\n -B : Mode Blind\n -A : Mode Active\n");
        fflush(stdin);
        rep = getchar();
        rep = toupper(rep);

        if (rep == 'C') {
            classique(stuff, grille_bateaux, grille_de_jeu, Coo_X, Coo_Y);
        } else if (rep == 'B') {
            blind(stuff, grille_bateaux, grille_de_jeu, Coo_X, Coo_Y);
        } else if (rep == 'A') {
            printf("Le mode active n'est pas terminé !\n");
        } else {
            printf("Le mode saisie n'existe pas !\n");
            check2 = 1;
        }
    }while (check2 == 1);

    return 0;
}
