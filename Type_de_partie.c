//
// Created by Administrateur on 09/06/2021.
//

#include "Type_de_partie.h"
#include "Etat_partie.h"
#include "Execution_tir.h"
#include "Sauvegarde.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

void lancement_nouvelle_partie(Grid grille_de_jeu, Grid grille_bateaux, Boat *bateau, int check2, Inventory stuff, char rep, int Coo_X, int Coo_Y, char sauvegarde){
    do {
        check2 = 0;
        printf("Veuillez saisir le mode de jeu souhaite :\n -C : Mode Classique\n -B : Mode Blind\n -A : Mode Active\n");
        fflush(stdin);
        rep = getchar();                                                                                    //Récupération de la réponse du joueur
        rep = toupper(rep);

        if (rep == 'C') {                                                                                   //Lancement du mode de jeu correspondant à cette réponse
            classique(stuff, grille_bateaux, grille_de_jeu, Coo_X, Coo_Y, sauvegarde);
        } else if (rep == 'B') {
            blind(stuff, grille_bateaux, grille_de_jeu, Coo_X, Coo_Y, sauvegarde);
        } else if (rep == 'A') {
            printf("Le mode active n'est pas termine !\n");
            active(stuff, grille_bateaux, grille_de_jeu, Coo_X, Coo_Y, sauvegarde, &bateau);
        } else {                                                                                            //Si le mode saisie par le joueur n'existe pas
            printf("Le mode saisie n'existe pas !\n");                                              //Demander un mode existant
            check2 = 1;
        }
    } while (check2 == 1);
}

int classique(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y, char sauvegarde){
    int check, nb_bateau;
    char missile, rep;
    int mode = 1;                                                   //mode de jeu utilisé pour la sauvegarde

    Grid cases_touchees;                                            //Grille utilisée uniquement pour le mode Blind
    cases_touchees.hauteur = 10;
    cases_touchees.largeur = 10;
    if(sauvegarde != 'O') {                                         //Si sauvegarde différent de 'O' cela signifie qu'on lance une nouvelle partie
        choix_difficult(&stuff);
        show_grid(grille_de_jeu);
    }else{                                                          //Sinon on récupère la grille de bateaux de la dernière partie
        init_save(&grille_bateaux, &grille_de_jeu);                 //On initialise la grille de jeu à l'aide de cette grille de bateaux
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
            choix_missile(&missile);                                //Demander le type de missile que l'on veut pour effectuer le tir
            tir(Coo_X, Coo_Y, &grille_de_jeu, &grille_bateaux, missile, &stuff, &check, &cases_touchees);
        } while (check == 1);

        show_grid(grille_de_jeu);

        /*show_grid(grille_bateaux);*/                  //Verif code
        missiles_restants(stuff);                                   //Afficher le nombre de missile restant à la fin du tour
        bateaux_restants(grille_bateaux, &nb_bateau);               //Afficher le nombre de bateau restant à la fin du tour
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

    Grid cases_touchees;                                            //Grille utilisée uniquement pour le mode Blind
    cases_touchees.hauteur = 10;
    cases_touchees.largeur = 10;

    if(sauvegarde != 'O') {                                         //Si sauvegarde différent de 'O' cela signifie qu'on lance une nouvelle partie
        choix_difficult(&stuff);                                    //On initialise la grille de jeu à l'aide de cette grille de bateaux
        /*show_grid(grille_de_jeu);*/           //Verif code
    }else{                                                          //Sinon on récupère la grille de bateaux de la dernière partie
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
            choix_missile(&missile);                                //Demander le type de missile que l'on veut pour effectuer le tir
            tir(Coo_X, Coo_Y, &grille_de_jeu, &grille_bateaux, missile, &stuff, &check, &cases_touchees);
        } while (check == 1);

        affichage_cases_blind(cases_touchees);
        /*show_grid(grille_de_jeu);*/                    //Verif code

        /*show_grid(grille_bateaux);*/                  //Verif code
        missiles_restants(stuff);                                   //Afficher le nombre de missile restant à la fin du tour
        bateaux_restants(grille_bateaux, &nb_bateau);               //Afficher le nombre de bateau restant à la fin du tour
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

int active(Inventory stuff, Grid grille_bateaux, Grid grille_de_jeu, int Coo_X, int Coo_Y, char sauvegarde, Boat *bateau){
    int check, nb_bateau, indice_bateau;
    char missile, rep;
    int mode = 3;                                                   //mode de jeu utilisé pour la sauvegarde

    Grid cases_touchees;                                            //Grille utilisée uniquement pour le mode Blind
    cases_touchees.hauteur = 10;
    cases_touchees.largeur = 10;
    if(sauvegarde != 'O'){                                          //Si sauvegarde différent de 'O' cela signifie qu'on lance une nouvelle partie
        choix_difficult(&stuff);
        show_grid(grille_de_jeu);
    }else{                                                          //Sinon on récupère la grille de bateaux de la dernière partie
        init_save(&grille_bateaux, &grille_de_jeu);                 //On initialise la grille de jeu à l'aide de cette grille de bateaux
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
            choix_missile(&missile);                                //Demander le type de missile que l'on veut pour effectuer le tir
            tir(Coo_X, Coo_Y, &grille_de_jeu, &grille_bateaux, missile, &stuff, &check, &cases_touchees);
        } while (check == 1);

        show_grid(grille_de_jeu);

        show_grid(grille_bateaux);                  //Verif code
        missiles_restants(stuff);                                   //Afficher le nombre de missile restant à la fin du tour
        bateaux_restants(grille_bateaux, &nb_bateau);               //Afficher le nombre de bateau restant à la fin du tour
        /*indice_bateau = bateau_a_deplacer(bateau, cases_touchees);*/
        bateau_a_deplacer(bateau, cases_touchees, &indice_bateau);
        printf("%d", indice_bateau);
        supp_ancienne_position(indice_bateau, bateau, &grille_bateaux);

        printf("%d\n", indice_bateau);
        show_grid(grille_bateaux);
        nouvelle_position(indice_bateau, bateau, &grille_bateaux);
        show_grid(grille_bateaux);
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

