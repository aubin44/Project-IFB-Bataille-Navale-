//
// Created by Administrateur on 29/05/2021.
//

#include "Execution_tir.h"
#include <ctype.h>
#include <stdio.h>

void fire_artillery(Grid *grille, Grid tableau_bateau, Grid *bateau, int X, int Y){
    int a, b;
    for(a = 0; a < tableau_bateau.largeur; a++) {                       //On parcourt la colonne de coordonnée Y du point d'impact dans le tableau de bateaux
        if (tableau_bateau.grille[a][Y] != '_') {                       //Lorsqu'une case sur cette colonne est un bateau
            (*grille).grille[a][Y] = 'X';                               //La case correspondante de la grille de jeu affiche 'X'
            (*bateau).grille[a][Y] = toupper((*bateau).grille[a][Y]);   //Marquage des case contenant des bateaux touchés
        } else if (tableau_bateau.grille[a][Y] == '_') {                //Lorsq'une case sur cette colonne est de l'eau
            (*grille).grille[a][Y] = 'O';                               //La case correspondante de la grille de jeu affiche 'O'
        }
    }
    for(b = 0; b < tableau_bateau.hauteur; b++){                        //On parcourt la ligne de coordonnée X du point d'impact dans le tableau de bateaux
        if(tableau_bateau.grille[X][b] != '_'){                         //Lorsqu'une case sur cette ligne est un bateau
            (*grille).grille[X][b] = 'X';                               //La case correspondante de la grille de jeu affiche 'X'
            (*bateau).grille[X][b] = toupper((*bateau).grille[X][b]);   //Marquage des case contenant des bateaux touchés
        }else if(tableau_bateau.grille[X][b] == '_'){                   //Lorsq'une case sur cette ligne est de l'eau
            (*grille).grille[X][b] = 'O';                               //La case correspondante de la grille de jeu affiche 'O'
        }
    }
}

void fire_tactical(Grid *grille, Grid tableau_bateau, Grid *bateau, int X, int Y){
    int a, b;
    for(a = 0; a < tableau_bateau.largeur; a++){
        for(b = 0; b < tableau_bateau.hauteur; b++){                                //On parcourt tous le tableau de bateaux
            if(tableau_bateau.grille[X][Y] != '_'){                                 //Si le point d'impact est un bateau
                if(tableau_bateau.grille[a][b] == tableau_bateau.grille[X][Y]){     //Pour toutes les cases de ce bateau
                    (*grille).grille[a][b] = 'X';                                   //Les cases correspondantes de la grille de jeu affiche 'X'
                    (*bateau).grille[a][b] = toupper((*bateau).grille[a][b]);       //Marquage des case contenant des bateaux touchés
                }
            }else if(tableau_bateau.grille[X][Y] == '_'){                           //Si le point d'impact est de l'eau
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

    printf("Quel missile souhaitez vous utiliser ?\n");
    printf(" -A : Pour missile d'artillerie\n -T : Pour missile tactique\n -B : Pour bombe\n -S : Pour missile simple\n");
    rep = getchar();
    rep = toupper(rep);
    *missile = rep;
}

void choix_coo_de_tir(int *Coo_X, int *Coo_Y){
    int position_X, position_Y;
    char buffer;

    printf("Dans quelle colonne souhaitez vous tirer :");
    scanf("%d", &position_X);
    printf("Dans quelle ligne souhaitez vous tirer :");
    fflush(stdin);
    buffer = getchar();
    buffer = toupper(buffer);
    *Coo_X = position_X - 1;
    *Coo_Y = buffer - 'A';
}