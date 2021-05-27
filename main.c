#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Depart_Grille.h"

void fire_artillery(Grid *grille, Grid tableau_bateau, int X, int Y);

void fire_tactical(Grid *grille, Grid tableau_bateau, int X, int Y);

int main(){
    Grid grille_de_jeu, grille_bateaux;
    Boat bateau[5];
    grille_de_jeu.hauteur = 10;     //Initialisation de la taille des grilles de jeu
    grille_de_jeu.largeur = 10;
    grille_bateaux.hauteur = 10;
    grille_bateaux.largeur = 10;
    int position_X, position_Y;
    int i, a;
    char buffer;

    srand(time(0));

    bateau[0].taille = 5;           //Initialisation de la taille des 5 bateaux
    bateau[1].taille = 4;
    bateau[2].taille = 3;
    bateau[3].taille = 3;
    bateau[4].taille = 2;

    init_grille(&grille_bateaux);
    init_grille(&grille_de_jeu);



    for(i = 0; i < 5; i++){
        do {
            genere_bateau(&bateau, i, grille_bateaux);

        } while (app_grille(bateau, i) == 1 || chevauchement(bateau, i, grille_bateaux) == 1);
        printf("Le bateau de taille %d et d'orientation %c se trouve en (%d,%c)\n", bateau[i].taille,
               bateau[i].orientation, bateau[i].position_x + 1, 'A'+bateau[i].position_y);

        placement_bateaux(bateau, i, &grille_bateaux);

    }
    show_grid(grille_bateaux);
    printf("Dans quelle colonne souhaitez vous tirer :");
    scanf("%d", &position_X);
    printf("Dans quelle ligne souhaitez vous tirer :");
    fflush(stdin);
    buffer = getchar();
    position_X = position_X - 1;
    position_Y = buffer - 'A';
    printf("%d\n", position_Y);

    fire_tactical(&grille_de_jeu, grille_bateaux, position_X, position_Y);

    show_grid(grille_de_jeu);

    return 0;
}

void fire_artillery(Grid *grille, Grid tableau_bateau, int X, int Y){
    int a, b;
    for(a = 0; a < tableau_bateau.largeur; a++) {
        if (tableau_bateau.grille[a][Y] != '_') {
            (*grille).grille[a][Y] = 'X';
        } else if (tableau_bateau.grille[a][Y] == '_') {
            (*grille).grille[a][Y] = 'O';
        }
    }
    for(b = 0; b < tableau_bateau.hauteur; b++){
        if(tableau_bateau.grille[X][b] == 'O'){
            (*grille).grille[X][b] = 'X';
        }else if(tableau_bateau.grille[X][b] == '_'){
            (*grille).grille[X][b] = 'O';;
        }
    }
}

void fire_tactical(Grid *grille, Grid tableau_bateau, int X, int Y){
    int a, b;
    for(a = 0; a < tableau_bateau.largeur; a++){
        for(b = 0; b < tableau_bateau.largeur; b++){
            if(tableau_bateau.grille[X][Y] != '_'){
                if(tableau_bateau.grille[a][b] == tableau_bateau.grille[X][Y]){
                    (*grille).grille[a][b] = 'X';
                }
            }else if(tableau_bateau.grille[X][Y] == '_'){
                (*grille).grille[X][Y] = 'O';
            }
        }
    }
}
