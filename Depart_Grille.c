//
// Created by anais on 27/05/2021.
//
#include "Depart_Grille.h"
#include "Etat_Grille.h"
#include "Execution_tir.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


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

void choix_difficult(Inventory *stuff){
    char rep_facile[15] = "FACILE";
    char rep_moyen[15] = "MOYEN";
    char rep_difficile[15] = "DIFFICILE";
    int check;
    char rep[15];
    int i = 0;

    printf("Quel mode souhaitez-vous ? (Facile/Moyen/Difficile)\n");
    fflush(stdin);
    gets(rep);
    while(rep[i] != '\0') {
        rep[i] = toupper(rep[i]);                           //On met toutes les lettres du mot tapé en majuscule afin d'éviter les erreurs
        i = i + 1;
    }
    do {
        check = 0;
        i = 0;

        if(strcmp(rep, rep_facile) == 0){                   //On compare la chaine de caractère saisie au trois possibilités
            (*stuff).nb_missile_artillery = 10;             //(FACILE/MOYEN/DIFFICILE)
            (*stuff).nb_missile_tactical = 10;
            (*stuff).nb_missile_bomb = 10;
            (*stuff).nb_missile_simple = 10;
            printf("Vous avez :\n %d missile(s) d'artillerie\n %d missile(s) tactiques\n %d bombe(s)\n %d missile(s) simple\n",
                   (*stuff).nb_missile_artillery,(*stuff).nb_missile_tactical, (*stuff).nb_missile_bomb, (*stuff).nb_missile_simple);
        }else if(strcmp(rep, rep_moyen) == 0){
            (*stuff).nb_missile_artillery = 3;
            (*stuff).nb_missile_tactical = 5;
            (*stuff).nb_missile_bomb = 5;
            (*stuff).nb_missile_simple = 10;
            printf("Vous avez :\n %d missile(s) d'artillerie\n %d missile(s) tactiques\n %d bombe(s)\n %d missile(s) simple\n",
                   (*stuff).nb_missile_artillery,(*stuff).nb_missile_tactical, (*stuff).nb_missile_bomb, (*stuff).nb_missile_simple);
        }else if(strcmp(rep, rep_difficile) == 0){
            (*stuff).nb_missile_artillery = 1;
            (*stuff).nb_missile_tactical = 4;
            (*stuff).nb_missile_bomb = 2;
            (*stuff).nb_missile_simple = 15;
            printf("Vous avez :\n %d missile(s) d'artillerie\n %d missile(s) tactiques\n %d bombe(s)\n %d missile(s) simple\n",
                   (*stuff).nb_missile_artillery,(*stuff).nb_missile_tactical, (*stuff).nb_missile_bomb, (*stuff).nb_missile_simple);
        }else{
            printf("La difficulte saisie est incorrect, veuillez saisir le mot complet (Facile/Moyen/Difficile) :\n");
            gets(rep);
            while(rep[i] != '\0') {
                rep[i] = toupper(rep[i]);
                i = i + 1;
            }
            check = 1;
        }
    }while (check == 1);                                  //On répète tant que la chaine de caractères saisie ne correspond pas aux attentes

}

void classique(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y){
    int check, nb_bateau;
    char missile;

    Grid cases_touchees;                        //Grille utilisée uniquement pour le mode Blind
    cases_touchees.hauteur = 10;
    cases_touchees.largeur = 10;

    choix_difficult(&stuff);
    show_grid(grille_de_jeu);

    do {
        init_grille(&cases_touchees);
        check_loose(stuff);
        choix_coo_de_tir(&Coo_X, &Coo_Y);                           //Tant que la case à déja été touchée
        while(grille_bateaux.grille[Coo_X][Coo_Y] <= 'F'){          //Demande au joueur de choisir une autre case
            printf("Vous avez deja tirez sur cette case !");
            choix_coo_de_tir(&Coo_X, &Coo_Y);
        }
        do {
            check = 0;
            choix_missile(&missile);
            tir(Coo_X, Coo_Y, &grille_de_jeu, &grille_bateaux, missile, &stuff, &check, &cases_touchees);
        } while (check == 1);

        show_grid(grille_de_jeu);

        /*show_grid(grille_bateaux);*/                  //Verif code
        missiles_restants(stuff);
        bateaux_restants(grille_bateaux, &nb_bateau);
        save(grille_bateaux, stuff);

    }while(nb_bateau > 0);

    printf("Youpi vous avez gagne !");
}

void blind(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y){
    int check, nb_bateau;
    char missile;

    Grid cases_touchees;                        //Grille utilisée uniquement pour le mode Blind
    cases_touchees.hauteur = 10;
    cases_touchees.largeur = 10;

    choix_difficult(&stuff);

    do {
        init_grille(&cases_touchees);
        check_loose(stuff);
        choix_coo_de_tir(&Coo_X, &Coo_Y);                           //Tant que la case à déja été touchée
        while(grille_bateaux.grille[Coo_X][Coo_Y] <= 'F'){          //Demande au joueur de choisir une autre case
            printf("Vous avez deja tirez sur cette case !");
            choix_coo_de_tir(&Coo_X, &Coo_Y);
        }
        do {
            check = 0;
            choix_missile(&missile);
            tir(Coo_X, Coo_Y, &grille_de_jeu, &grille_bateaux, missile, &stuff, &check, &cases_touchees);
        } while (check == 1);

        affichage_cases_blind(cases_touchees);
        /*show_grid(grille_de_jeu);*/                    //Verif code

        /*show_grid(grille_bateaux);*/                  //Verif code
        missiles_restants(stuff);
        bateaux_restants(grille_bateaux, &nb_bateau);


    }while(nb_bateau > 0);

    printf("Youpi vous avez gagne !");
}

void affichage_cases_blind(Grid cases_touchees){
    int a, b;

    for(a = 0; a < cases_touchees.largeur; a++){
        for(b = 0; b < cases_touchees.hauteur; b++){
            if(cases_touchees.grille[a][b] == 'X'){
                printf("-Vous avez touche un bateau en (%d,%c)\n", a + 1, b + 'A');
            }
        }
    }
}

void save(Grid tableau_bateau, Inventory missile){
    FILE *fichier;
    int i, j;
    fichier = fopen("sauvegarde", "w");
    fprintf(fichier, "%d\n%d\n%d\n%d\n", missile.nb_missile_artillery, missile.nb_missile_bomb, missile.nb_missile_simple, missile.nb_missile_tactical);
    for (i = 0; i < tableau_bateau.largeur; i++) {
            for( j = 0; j < tableau_bateau.hauteur; j++){
                fprintf(fichier,"%c", tableau_bateau.grille[i][j]);
            }
    }
    fclose(fichier);
}

void load(Grid *tableau_bateau, Inventory *missile){
    FILE *fichier;
    char buffer[3];
    int i, j;
    fichier = fopen("sauvegarde", "r");
    fgets(&buffer, 3, fichier);
    (*missile).nb_missile_artillery = atoi(buffer);
    fgets(&buffer, 3, fichier);
    (*missile).nb_missile_bomb = atoi(buffer);
    fgets(&buffer, 3, fichier);
    (*missile).nb_missile_simple = atoi(buffer);
    fgets(&buffer, 3, fichier);
    (*missile).nb_missile_tactical = atoi(buffer);

    for(i = 0; i < (*tableau_bateau).largeur; i++){
        for(j = 0; j < (*tableau_bateau).hauteur; j++){
            (*tableau_bateau).grille[i][j] = fgetc(fichier);
        }
    }

}

void