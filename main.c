#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "Depart_Grille.h"

void fire_artillery(Grid *grille, Grid tableau_bateau, Grid *bateau, int X, int Y);

void fire_tactical(Grid *grille, Grid tableau_bateau, Grid *bateau, int X, int Y);

void fire_bomb(Grid *grille, Grid *tableau_bateau, int X, int Y);

void fire_simple(Grid *grille, Grid *tableau_bateau, int X, int Y);

typedef struct{
    int nb_missile_artillery;
    int nb_missile_tactical;
    int nb_missile_bomb;
    int nb_missile_simple;
}Inventory;

void easy(Inventory *stuff);

void medium(Inventory *stuff);

void hard(Inventory *stuff);

void choix_difficult(Inventory *stuff);

void affichage();

int main(){
    Grid grille_de_jeu, grille_bateaux;
    Boat bateau[5];
    Inventory stuff;
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
    printf("Dans quelle colonne souhaitez vous tirer :");
    scanf("%d", &position_X);
    printf("Dans quelle ligne souhaitez vous tirer :");
    fflush(stdin);
    buffer = getchar();
    position_X = position_X - 1;
    position_Y = buffer - 'A';
    printf("%d\n", position_Y);

    fire_artillery(&grille_de_jeu, grille_bateaux, &grille_bateaux, position_X, position_Y);

    show_grid(grille_de_jeu);
    show_grid(grille_bateaux);
    return 0;
}

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

void easy(Inventory *stuff){
    (*stuff).nb_missile_artillery = 10;
    (*stuff).nb_missile_tactical = 10;
    (*stuff).nb_missile_bomb = 10;
    (*stuff).nb_missile_simple = 10;
    printf("Vous avez :\n %d missile(s) d'artillerie\n %d missile(s) tactiques\n %d bombe(s)\n %d missile(s) simple",
           (*stuff).nb_missile_artillery,(*stuff).nb_missile_tactical, (*stuff).nb_missile_bomb, (*stuff).nb_missile_simple);
}

void medium(Inventory *stuff){
    (*stuff).nb_missile_artillery = 3;
    (*stuff).nb_missile_tactical = 5;
    (*stuff).nb_missile_bomb = 5;
    (*stuff).nb_missile_simple = 10;
    printf("Vous avez :\n %d missile(s) d'artillerie\n %d missile(s) tactiques\n %d bombe(s)\n %d missile(s) simple",
           (*stuff).nb_missile_artillery,(*stuff).nb_missile_tactical, (*stuff).nb_missile_bomb, (*stuff).nb_missile_simple);
}

void hard(Inventory *stuff){
    (*stuff).nb_missile_artillery = 1;
    (*stuff).nb_missile_tactical = 4;
    (*stuff).nb_missile_bomb = 2;
    (*stuff).nb_missile_simple = 15;
    printf("Vous avez :\n %d missile(s) d'artillerie\n %d missile(s) tactiques\n %d bombe(s)\n %d missile(s) simple",
           (*stuff).nb_missile_artillery,(*stuff).nb_missile_tactical, (*stuff).nb_missile_bomb, (*stuff).nb_missile_simple);
}

void choix_difficult(Inventory *stuff){
    char rep_facile[15] = "FACILE";
    char rep_moyen[15] = "MOYEN";
    char rep_difficile[15] = "DIFFICILE";
    int check;
    char rep[15];
    int i = 0;

    printf("Quel mode souhaitez-vous ? (Facile/Moyen/Difficile)\n");
    gets(rep);
    while(rep[i] != '\0') {
        rep[i] = toupper(rep[i]);
        i = i + 1;
    }
    do {
        check = 0;
        i = 0;

        if(strcmp(rep, rep_facile) == 0){
            easy(&stuff);
        }else if(strcmp(rep, rep_moyen) == 0){
            medium(&stuff);
        }else if(strcmp(rep, rep_difficile) == 0){
            hard(&stuff);
        }else{
            printf("La difficulte saisie est incorrect, veuillez saisir le mot complet (Facile/Moyen/Difficile) :\n");
            gets(rep);
            while(rep[i] != '\0') {
                rep[i] = toupper(rep[i]);
                i = i + 1;
            }
            check = 1;
        }
    }while (check == 1);

}