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
#include <time.h>


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
        }                                                                                   //Placer 'a' + i là où se trouve un bateau
    }                                                                                       //Afin de pouvoir diférencier les bateaux entre eux
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

    if(bateau[i].orientation == 'H'){                                                       //Si le bateau est horizontale
        for(a = bateau[i].position_x; a - bateau[i].position_x < bateau[i].taille; a++){    //Vérifier pour les coordonnées allant de (x,y) à (x + taille,y)
            if(grille_bateau.grille[a][bateau[i].position_y] != '_'){                       //Si une des cases n'est pas vide
                test = 1;
            }
        }
    }else{
        for(a = bateau[i].position_y; a - bateau[i].position_y < bateau[i].taille; a++){    //Si le bateau est verticale
            if(grille_bateau.grille[bateau[i].position_x][a] != '_'){                       //Vérifier pour les coordonnées allant de (x,y) à (x,y + taille)
                test = 1;                                                                   //Si une des cases n'est pas vide
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

int classique(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y, char sauvegarde){
    int check, nb_bateau;
    char missile, rep;
    int mode = 1;                                                //mode de jeu utilisé pour la sauvegarde

    Grid cases_touchees;                                            //Grille utilisée uniquement pour le mode Blind
    cases_touchees.hauteur = 10;
    cases_touchees.largeur = 10;
    if(sauvegarde != 'O') {
        choix_difficult(&stuff);
        show_grid(grille_de_jeu);
    }else{
        init_save(&grille_bateaux, &grille_de_jeu);
        show_grid(grille_de_jeu);
    }
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
        do {
            check = 0;
            printf("Voulez vous continuer a jouer ?\n- J : Jouer\n- S : Sauvegarder et Quitter\n");
            fflush(stdin);
            rep = getchar();
            rep = toupper(rep);
            if (rep == 'S') {
                save(grille_bateaux, stuff, mode);
                printf("Votre partie est sauvegardee, merci d'avoir joue !\n");
                return 0;
            } else if (rep != 'J') {
                printf("La reponse donne est incorrect\n");
                check = 1;
            }
        }while(check == 1);

    }while(nb_bateau > 0);

    printf("Youpi vous avez gagne !");
}

int blind(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y, char sauvegarde){
    int check, nb_bateau;
    char missile, rep;
    int mode = 2;

    Grid cases_touchees;                        //Grille utilisée uniquement pour le mode Blind
    cases_touchees.hauteur = 10;
    cases_touchees.largeur = 10;

    if(sauvegarde != 'O') {
        choix_difficult(&stuff);
        /*show_grid(grille_de_jeu);*/           //Verif code
    }else{
        init_save(&grille_bateaux, &grille_de_jeu);
        /*show_grid(grille_de_jeu);*/           //Verif code
    }

    do {
        init_grille(&cases_touchees);
        check_loose(stuff);
        choix_coo_de_tir(&Coo_X, &Coo_Y);                           //Tant que la case à déja été touchée
        while(grille_bateaux.grille[Coo_X][Coo_Y] <= 'F'){          //Demande au joueur de choisir une autre case
            printf("Vous avez deja tirez sur cette case !\n");
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
        do {
            check = 0;
            printf("Voulez vous continuer a jouer ?\n- J : Jouer\n- S : Sauvegarder et Quitter\n");
            fflush(stdin);
            rep = getchar();
            rep = toupper(rep);
            if (rep == 'S') {
                save(grille_bateaux, stuff, mode);
                printf("Votre partie est sauvegardee, merci d'avoir joue !\n");
                return 0;
            } else if (rep != 'J') {
                printf("La réponse donne est incorrect\n");
                check = 1;
            }
        }while(check == 1);

    }while(nb_bateau > 0);

    printf("Youpi vous avez gagne !");
}

void affichage_cases_blind(Grid cases_touchees){
    int a, b;

    for(a = 0; a < cases_touchees.largeur; a++){                    //Parcourir la grille dédiée au mode blind (initialisée entre chaque tour)
        for(b = 0; b < cases_touchees.hauteur; b++){                //Lorsqu'un point d'impact y apparait
            if(cases_touchees.grille[a][b] == 'X'){                 //Notifier le joueur en lui indiquant l'adresse de ce point d'impact
                printf("-Vous avez touche un bateau en (%d,%c)\n", a + 1, b + 'A');
            }
        }
    }
}

void save(Grid tableau_bateau, Inventory missile, int mode){
    FILE *fichier;
    int i, j;
    fichier = fopen("sauvegarde", "w");             //Sauvegarde du nombre de missile, du mode et de la grille de bateaux
    fprintf(fichier, "%d\n", mode);                         //Dans le fichier texte 'sauvegarde'
    fprintf(fichier, "%d\n%d\n%d\n%d\n", missile.nb_missile_artillery, missile.nb_missile_bomb, missile.nb_missile_simple, missile.nb_missile_tactical);
    for (i = 0; i < tableau_bateau.largeur; i++) {
            for( j = 0; j < tableau_bateau.hauteur; j++){
                fprintf(fichier,"%c", tableau_bateau.grille[i][j]);
            }
    }
    fclose(fichier);
}

void load(Grid *tableau_bateau, Inventory *missile, int *mode){
    FILE *fichier;
    char buffer[4];
    char tampon;
    int i, j;
    fichier = fopen("sauvegarde", "r");
    *mode = fgetc(fichier);                             //Enregistrement du mode de jeu de la partie en cours
    tampon = fgetc(fichier);                            //Variable tampon permettant de ne pas créer un décallage lors de l'insertion du tableau de bateau
    fgets(&buffer, 4, fichier);               //Initialisation du nombre de missile restant pour chaque type
    (*missile).nb_missile_artillery = atoi(buffer);
    fgets(&buffer, 4, fichier);
    (*missile).nb_missile_bomb = atoi(buffer);
    fgets(&buffer, 4, fichier);
    (*missile).nb_missile_simple = atoi(buffer);
    fgets(&buffer, 4, fichier);
    (*missile).nb_missile_tactical = atoi(buffer);

    for(i = 0; i < (*tableau_bateau).largeur; i++){     //Initialisation de la grille de bateau de l'ancienne partie
        for(j = 0; j < (*tableau_bateau).hauteur; j++){
            (*tableau_bateau).grille[i][j] = fgetc(fichier);
        }
    }
    fclose(fichier);
}

void init_save(Grid *tableau_bateau, Grid *grille){
    int a, b;

    for(a = 0; a < (*tableau_bateau).largeur; a++){     //Initialisation de la grille de jeu grâce à la grille de bateau de l'ancienne partie
        for(b = 0; b < (*tableau_bateau).hauteur; b++){
            if((*tableau_bateau).grille[a][b] == 'F'){
                (*grille).grille[a][b] = 'O';
            }else if((*tableau_bateau).grille[a][b] == '_' || (*tableau_bateau).grille[a][b] >= 'a'){
                (*grille).grille[a][b] = '_';
            }else{
                (*grille).grille[a][b] = 'X';
            }
        }
    }
}

int active(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y, char sauvegarde, Boat *bateau){
    int check, nb_bateau;
    char missile, rep;
    int mode = 3;                                                //mode de jeu utilisé pour la sauvegarde

    Grid cases_touchees;                                            //Grille utilisée uniquement pour le mode Blind
    cases_touchees.hauteur = 10;
    cases_touchees.largeur = 10;
    if(sauvegarde != 'O'){
        choix_difficult(&stuff);
        show_grid(grille_de_jeu);
    }else{
        init_save(&grille_bateaux, &grille_de_jeu);
        show_grid(grille_de_jeu);
    }
    init_grille(&cases_touchees);
    do {

        check_loose(stuff);
        choix_coo_de_tir(&Coo_X, &Coo_Y);                           //Tant que la case à déja été touchée
        while(grille_bateaux.grille[Coo_X][Coo_Y] <= 'E'){          //Demande au joueur de choisir une autre case
            printf("Vous avez deja tirez sur cette case !");
            choix_coo_de_tir(&Coo_X, &Coo_Y);
        }
        do {
            check = 0;
            choix_missile(&missile);
            tir(Coo_X, Coo_Y, &grille_de_jeu, &grille_bateaux, missile, &stuff, &check, &cases_touchees);
        } while (check == 1);

        show_grid(grille_de_jeu);

        show_grid(grille_bateaux);                  //Verif code
        missiles_restants(stuff);
        bateaux_restants(grille_bateaux, &nb_bateau);
        printf("%d", bateau_deplace(bateau, cases_touchees));
        do{
            check = 0;
            printf("Voulez vous continuer a jouer ?\n- J : Jouer\n- S : Sauvegarder et Quitter\n");
            fflush(stdin);
            rep = getchar();
            rep = toupper(rep);
            if (rep == 'S') {
                save(grille_bateaux, stuff, mode);
                printf("Votre partie est sauvegardee, merci d'avoir joue !\n");
                return 0;
            } else if (rep != 'J') {
                printf("La reponse donne est incorrect\n");
                check = 1;
            }
        }while(check == 1);

    }while(nb_bateau > 0);

    printf("Youpi vous avez gagne !");
}

int bateau_deplace(Boat *bateau, Grid cases_touchees){
    int i, indice_bateau, a;
    int somme = 0;
    int bateau_touche[5] = {0};

    srand(time(0));

    for(indice_bateau = 0; indice_bateau < 5; indice_bateau++) {                            //Effectuer une vérification sur chacun des bateaux

        if (bateau[indice_bateau].orientation == 'H') {                                     //Lorsque le bateau est horizontale, parcourir suivant les abscisses
            i = bateau[indice_bateau].position_x;
            while (i <= bateau[indice_bateau].position_x + bateau[indice_bateau].taille){   //Parcourir le bateau sur toute sa longueur
                if (cases_touchees.grille[i][bateau[indice_bateau].position_y] == 'X'){     //Si une de ses cases est touchées (symbole 'X')
                    bateau_touche[indice_bateau] = 1;                                       //Noter '1' dans le tableau pour dire que le bateau a été touché
                }
                i = i + 1;
            }
        } else {                                                                            //Lorque le bateau est verticale, parcourir suivant les ordonnées
            i = bateau[indice_bateau].position_y;
            while( i <= bateau[indice_bateau].position_y + bateau[indice_bateau].taille){   //Parcourir le bateau sur toute sa longueur
                if (cases_touchees.grille[bateau[indice_bateau].position_x][i] == 'X'){     //Si une de ses cases est touchées (symbole 'X')
                    bateau_touche[indice_bateau] = 1;                                       //Noter '1' dans le tableau pour dire que le bateau a été touché
                }
                i = i + 1;
            }
        }
    }
    somme = 0;
    for(a = 0; a < 5; a++){
        somme = somme + bateau_touche[a];                                                   //Si tous les bateaux ont été touchés alors somme = 5
    }
    if(somme == 5){
        printf("Aucun bateau n'a ete deplace car ils ont tous ete touches !\n");
        return -1;                                                                          //Retourner '-1' pour dire que tous les bateaux ont été touchés
    }else{
        do{
            indice_bateau = rand()% 5;                                                      //Générer un nombre appartenant à l'intervalle [0; 4]
        } while (bateau_touche[indice_bateau] == 1);                                        //Recommencer tant que le bateau correspondant à se nombre a été touché
        return indice_bateau;                                                               //Retourner l'indice d'un bateau non touché
    }
}