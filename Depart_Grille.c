//
// Created by anais on 27/05/2021.
//

#include "Depart_Grille.h"
#include <stdio.h>
#include <stdlib.h>

void init_grille(Grid *grille){
    int x, y;
    for(y = 0; y < (*grille).hauteur; y++){                 //Grille initialiser : Tous les caractères valent '_'
        for(x = 0; x < (*grille).largeur; x++){             //'_' représente une case vide
            (*grille).grille[x][y] = '_';
        }
    }
}

void show_grid(Grid grille){
    int x, y;
    printf("   1  2  3  4  5  6  7  8  9  10\n");   //Affiche les coordonnées en abscisse sous forme de chiffres
    for(y = 0; y < grille.hauteur; y++){
        printf("%c ", 'A' + y);                     //Affiche les coordonnées en ordonnée sous forme de lettres
        for(x = 0; x < grille.largeur; x++ ){
            printf(" %c ", grille.grille[x][y]);    //Affiche les caractères de la grille
        }
        printf("\n");                               //Va à la ligne tous les 10 caractères afin de former une grille à l'affichage
    }
}

int app_grille(Boat bateau[], int i){
    int test;
    if (bateau[i].orientation == 'H'){                      //Si l'orientation est horizontale, vérifier si le point en abscisse + la taille du bateau ne dépasse pas de la grille
        if(bateau[i].position_x + bateau[i].taille > 10){
            test = 1;
        }else{
            test = 0;
        }
    }else{                                                  //Si l'orientation est verticale, vérifier si le point en ordonnée + la taille du bateau ne dépasse pas de la grille
        if(bateau[i].position_y + bateau[i].taille > 10){
            test = 1;
        }else{
            test = 0;
        }
    }
    return test;
}

void placement_bateaux(Boat bateau[], int i, Grid *grille_bateaux){
    int a;
    if(bateau[i].orientation == 'H'){                                                       //Si l'orientation du bateau est 'H' parcourir les abscisses
        for(a = bateau[i].position_x; a < bateau[i].position_x + bateau[i].taille; a++){    //Du point généré x jusqu'au point x + la taille du bateau
            (*grille_bateaux).grille[a][bateau[i].position_y] = 'a'+i;
        }
    }else{                                                                                  //Si l'orientation du bateau est 'V' parcourir les ordonnées
        for(a = bateau[i].position_y; a < bateau[i].position_y + bateau[i].taille; a++){    //Du point généré x jusqu'au point x + la taille du bateau
            (*grille_bateaux).grille[bateau[i].position_x][a] = 'a'+i;
        }                                                                                   //Placer 'O' là où se trouve un bateau
    }
}

void genere_bateau(Boat *bateau, int i, Grid grille_bateau){
    if(rand() % 2 == 0){                                        //Dans le cas ou le nombre aléatoire vaut 0 l'orientation est horizontale si c'est 1 elle est verticale
        bateau[i].orientation = 'H';
    }else{
        bateau[i].orientation = 'V';
    }
    bateau[i].position_x = rand() % grille_bateau.largeur;     //Génération de la position en abscisse [0;9] --> tableau de 10 case de largeur
    bateau[i].position_y = rand() % grille_bateau.hauteur;     //Génération de la position en ordonnée [0;9] --> tableau de 10 case de hauteur
}

int chevauchement(Boat *bateau,int i, Grid grille_bateau){
    int a, test = 0;

    if(bateau[i].orientation == 'H'){
        for(a = bateau[i].position_x; a - bateau[i].position_x < bateau[i].taille; a++){
            if(grille_bateau.grille[a][bateau[i].position_y] != '_'){
                test = 1;
            }
        }
    }else{
        for(a = bateau[i].position_y; a - bateau[i].position_y < bateau[i].taille; a++){
            if(grille_bateau.grille[bateau[i].position_x][a] != '_'){
                test = 1;
            }
        }
    }
    return test;
}