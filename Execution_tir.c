//
// Created by Administrateur on 29/05/2021.
//
#include "Execution_tir.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void fire_artillery(Grid *grille, Grid *bateau, int X, int Y){
    int a, b;
    printf("FA %d %d", X, Y);
    for(a = 0; a < (*bateau).largeur; a++) {                       //On parcourt la colonne de coordonnée Y du point d'impact dans le tableau de bateaux
        if ((*bateau).grille[a][Y] != '_') {                       //Lorsqu'une case sur cette colonne est un bateau
            printf("FA2 %d %d", X, Y);
            (*grille).grille[a][Y] = 'X';                               //La case correspondante de la grille de jeu affiche 'X'
            (*bateau).grille[a][Y] = toupper((*bateau).grille[a][Y]);   //Marquage des case contenant des bateaux touchés
        } else if ((*bateau).grille[a][Y] == '_') {                //Lorsq'une case sur cette colonne est de l'eau
            (*grille).grille[a][Y] = 'O';                               //La case correspondante de la grille de jeu affiche 'O'
        }
    }
    for(b = 0; b < (*bateau).hauteur; b++){                        //On parcourt la ligne de coordonnée X du point d'impact dans le tableau de bateaux
        if((*bateau).grille[X][b] != '_'){                         //Lorsqu'une case sur cette ligne est un bateau
            (*grille).grille[X][b] = 'X';                               //La case correspondante de la grille de jeu affiche 'X'
            (*bateau).grille[X][b] = toupper((*bateau).grille[X][b]);   //Marquage des case contenant des bateaux touchés
        }else if((*bateau).grille[X][b] == '_'){                   //Lorsq'une case sur cette ligne est de l'eau
            (*grille).grille[X][b] = 'O';                               //La case correspondante de la grille de jeu affiche 'O'
        }
    }
}

void fire_tactical(Grid *grille, Grid *bateau, int X, int Y){
    int a, b;
    char position = (*bateau).grille[X][Y];
    for(a = 0; a < (*bateau).largeur; a++){
        for(b = 0; b < (*bateau).hauteur; b++){                                //On parcourt tous le tableau de bateaux
            if((*bateau).grille[X][Y] != '_'){                                 //Si le point d'impact est un bateau
                if((*bateau).grille[a][b] == position){             //Pour toutes les cases de ce bateau
                    (*grille).grille[a][b] = 'X';                                   //Les cases correspondantes de la grille de jeu affiche 'X'
                    (*bateau).grille[a][b] = toupper((*bateau).grille[a][b]);       //Marquage des case contenant des bateaux touchés
                }
            }else if((*bateau).grille[X][Y] == '_'){                           //Si le point d'impact est de l'eau
                (*grille).grille[X][Y] = 'O';                                       //La case correspondante de la grille de jeu affiche 'O'
            }
        }
    }
}

void fire_bomb(Grid *grille, Grid *tableau_bateau, int X, int Y){
    int rayon = 1;                                                                          //On définit un rayon d'impact de la bombe
    int a, b;

    for(a = X-rayon; a <= X+rayon; a++){
        for(b = Y-rayon; b <= Y+rayon; b++){                                                //On parcourt dans le tableau de bateaux toute la zone autour du point d'impact de rayon prédéfinit
            if((*tableau_bateau).grille[a][b] == '_'){                                      //Si la case est de l'eau
                (*grille).grille[a][b] = 'O';                                               //La case correspondante dans la grille de jeu affiche 'O'
            }else if((*tableau_bateau).grille[a][b] != '_'){                                //Si la case est un bateau
                (*grille).grille[a][b] = 'X';                                               //La case correspondante dans la grille de jeu affiche 'X'
                (*tableau_bateau).grille[a][b] = toupper((*tableau_bateau).grille[a][b]);   //Marquage des case contenant des bateaux touchés
            }
        }
    }
}

void fire_simple(Grid *grille, Grid *tableau_bateau, int X, int Y){
    if((*tableau_bateau).grille[X][Y] == '_'){                                         //Si le point d'impact dans le tableau de bateaux est de l'eau
        (*grille).grille[X][Y] = 'O';                                                   //Le point correspondant sur la grille de jeu affiche 'O'
    }else if((*tableau_bateau).grille[X][Y] != '_'){                                    //Si le point d'impact dans le tableau de bateaux est un bateau
        (*grille).grille[X][Y] = 'X';                                                  //Le point correspondant sur la grille de jeu affiche 'X'
        (*tableau_bateau).grille[X][Y] = toupper((*tableau_bateau).grille[X][Y]);      //Marquage des case contenant des bateaux touchés
    }
}

void choix_missile(char *missile){
    char rep;


    printf("Veuillez saisir un des missiles suivants :\n");
    printf(" -A : Pour missile d'artillerie\n -T : Pour missile tactique\n"
           " -B : Pour bombe\n -S : Pour missile simple\n");
    fflush(stdin);
    rep = getchar();
    rep = toupper(rep);

    while (rep != 'A' && rep != 'T' && rep != 'B' && rep != 'S'){
        printf("ERREUR ! Veuillez saisir un missile existant !\n");
        printf("Veuillez saisir un des missiles suivants :\n");
        printf(" -A : Pour missile d'artillerie\n -T : Pour missile tactique\n"
               " -B : Pour bombe\n -S : Pour missile simple\n");
        fflush(stdin);
        rep = getchar();
        rep = toupper(rep);
    }

    *missile = rep;
}

void choix_coo_de_tir(int *Coo_X, int *Coo_Y){
    int position_X, position_Y;
    char buffer;


    printf("Dans quelle colonne souhaitez vous tirer :");
    scanf("%d", &position_X);
    while (position_X < 1 || position_X > 10){
        printf("Veuillez saisir une valeure comprise dans l'intervalle [1;10]\n");
        printf("Dans quelle colonne souhaitez vous tirer :\n");
        scanf("%d", &position_X);
    }
    printf("Dans quelle ligne souhaitez vous tirer :");
    fflush(stdin);
    buffer = getchar();
    buffer = toupper(buffer);
    while (buffer - 'A' < 0 || buffer - 'A' > 9){
        printf("Veuillez saisir une lettre entre A et J ");
        printf("Dans quelle ligne souhaitez vous tirer :");
        fflush(stdin);
        buffer = getchar();
        buffer = toupper(buffer);
    }
    *Coo_X = position_X - 1;
    *Coo_Y = buffer - 'A';
}

void tir(int Coo_X, int Coo_Y, Grid *grille_de_jeu, Grid *grille_bateaux, int missile, Inventory *stuff, int *check){
    (*check) = 0;
    if (missile == 'A' && (*stuff).nb_missile_artillery > 0) {
        fire_artillery(grille_de_jeu, grille_bateaux, Coo_X, Coo_Y);
        (*stuff).nb_missile_artillery -= 1;
    } else if (missile == 'T' && (*stuff).nb_missile_tactical > 0) {
        fire_tactical(grille_de_jeu, grille_bateaux, Coo_X, Coo_Y);
        (*stuff).nb_missile_tactical -= 1;
    } else if (missile == 'B' && (*stuff).nb_missile_bomb > 0) {
        fire_bomb(grille_de_jeu, grille_bateaux, Coo_X, Coo_Y);
        (*stuff).nb_missile_bomb -= 1;
    } else if (missile == 'S' && (*stuff).nb_missile_simple > 0) {
        fire_simple(grille_de_jeu, grille_bateaux, Coo_X, Coo_Y);
        (*stuff).nb_missile_simple -= 1;
    } else {
        printf("ERREUR, vous n'avez plus de ce missile");
        (*check) = 1;
    }
}