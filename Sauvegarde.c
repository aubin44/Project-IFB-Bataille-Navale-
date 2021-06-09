//
// Created by Administrateur on 09/06/2021.
//

#include "Sauvegarde.h"
#include "Type_de_partie.h"
#include <stdio.h>
#include <stdlib.h>

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

void lancement_mode_sauvegarde(Inventory stuff, int mode, Grid grille_bateaux, char sauvegarde, int Coo_X, int Coo_Y, Grid grille_de_jeu){
                                                                                    //Recharger le tableau de bateau, l'inventaire de missile
    load(&grille_bateaux, &stuff, &mode);                                           //et le mode de jeu de la dernière partie
    if(mode == '1'){                                                                //Si c'est le premier mode
        /*show_grid(grille_bateaux);*/          //Verif code
        sauvegarde = 'O';
        classique(stuff, grille_bateaux, grille_de_jeu, Coo_X, Coo_Y, sauvegarde);  //Lancer le mode classique
    }else if(mode == '2'){                                                          //Si c'est le second mode
        /*show_grid(grille_bateaux);*/
        sauvegarde = 'O';
        blind(stuff, grille_bateaux, grille_de_jeu, Coo_X, Coo_Y, sauvegarde);      //Lancer le mode Blind
    }else{
        printf("ERREUR");
    }
}