//
// Created by Administrateur on 09/06/2021.
//

#include "Etat_partie.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bateaux_restants(Grid tableau_bateau, int *bateau){
    int i,x, y;
    int nb_case = 0, nb_bateau = 0;
    for(i = 'a'; i<= 'e'; i++){                                     //On utilise les caractères de marquage (a/b/c/d/e/A/B/C/D/E)
        nb_case = 0;                                                //placés dans le tableau contenant les bateaux
        for(x = 0; x < tableau_bateau.largeur; x++){                //Cela nous permet de savoir combien de case ont été touchées par bateau
            for(y = 0; y < tableau_bateau.hauteur; y++){
                if(tableau_bateau.grille[x][y] == i){
                    nb_case = nb_case + 1;
                }
            }
        }
        if(nb_case > 0){                                             //Si le nombre de case non touchées est supérieur à 0 cela signifie que le bateau n'est pas coulé
            nb_bateau = nb_bateau + 1;
            printf("-bateau%d : %d cases restantes\n", i - 'a' + 1, nb_case);
        }else if(nb_case == 0){                                     //Si le nombre de case non touchées est de 0 cela signifie que le bateau est coulé
            printf("-bateau%d : coule !\n", i - 'a' + 1);
        }
    }
    printf("\nIl vous reste %d bateaux a couler\n\n", nb_bateau);
    (*bateau) = nb_bateau;
}

void missiles_restants(Inventory missile){
    printf("Il vous reste :\n *%d missile(s) d'artillerie\n *%d missile(s) tactiques\n *%d bombe(s)\n *%d missile(s) simple\n\n",
           missile.nb_missile_artillery, missile.nb_missile_tactical, missile.nb_missile_bomb, missile.nb_missile_simple);
}

int check_loose(Inventory nb_missile){
    if(nb_missile.nb_missile_artillery == 0 && nb_missile.nb_missile_bomb == 0          //Si il ne reste plus aucun missile le joueur a perdu
       && nb_missile.nb_missile_simple == 0 && nb_missile.nb_missile_tactical == 0){
        printf("\nVous n'avez plus de missiles. Vous avez perdu !\n");
        exit(0);
    }
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

void bateau_a_deplacer(Boat bateau[], Grid cases_touchees, int *indice_bateau){
    int i, a, indice;
    int somme = 0;
    int bateau_touche[5] = {0};

    srand(time(0));

    for(indice = 0; indice < 5; indice++) {                                             //Effectuer une vérification sur chacun des bateaux
        if (bateau[indice].orientation == 'H') {                                        //Lorsque le bateau est horizontale, parcourir suivant les abscisses
            i = bateau[indice].position_x;
            while (i <= bateau[indice].position_x + bateau[indice].taille){             //Parcourir le bateau sur toute sa longueur
                if (cases_touchees.grille[i][bateau[indice].position_y] == 'X'){        //Si une de ses cases est touchées (symbole 'X')
                    bateau_touche[indice] = 1;                                          //Noter '1' dans le tableau pour dire que le bateau a été touché
                }
                i = i + 1;
            }
        } else {                                                                        //Lorque le bateau est verticale, parcourir suivant les ordonnées
            i = bateau[indice].position_y;
            while( i <= bateau[indice].position_y + bateau[indice].taille){             //Parcourir le bateau sur toute sa longueur
                if (cases_touchees.grille[bateau[indice].position_x][i] == 'X'){        //Si une de ses cases est touchées (symbole 'X')
                    bateau_touche[indice] = 1;                                          //Noter '1' dans le tableau pour dire que le bateau a été touché
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
        *indice_bateau = -1;                                                                //Retourner '-1' pour dire que tous les bateaux ont été touchés
    }else{
        do{
            indice = rand()% 5;                                                             //Générer un nombre appartenant à l'intervalle [0; 4]
        } while (bateau_touche[indice] == 1);                                               //Recommencer tant que le bateau correspondant à se nombre a été touché
        *indice_bateau = indice;
    }
}

void supp_ancienne_position(int indice_bateau, Boat *bateau, Grid *tableau_bateau){
    int i;

    if(bateau[indice_bateau].orientation == 'H'){                                           //Lorsque le bateau est horizontale
        for(i = bateau[indice_bateau].position_x;                                           //Parcourir le bateau sur toute sa longueur dans la grille de bateau
            i < bateau[indice_bateau].position_x +bateau[indice_bateau].taille; i++){
            (*tableau_bateau).grille[i][bateau[indice_bateau].position_y] = '_';            //Remplacer le caractère indiquant la présence d'un bateau (a/b/c/d/e)
        }                                                                                   //par un caractère indiquant une case vide
    }else{                                                                                  //Lorsque le bateau est verticale
        for(i = bateau[indice_bateau].position_y;                                           //Parcourir le bateau sur toute sa longueur dans la grille de bateau
            i < bateau[indice_bateau].position_y + bateau[indice_bateau].taille; i++){
            (*tableau_bateau).grille[bateau[indice_bateau].position_x][i] = '_';            //Remplacer le caractère indiquant la présence d'un bateau (a/b/c/d/e)
        }                                                                                   //par un caractère indiquant une case vide
    }
}

void nouvelle_position(int indice, Boat *bateau, Grid *tableau_bateau){
    int nb_case, i, orientation, signe;
    int tampon_x = bateau[indice].position_x;                                   //Variable permettant de sauvegarder l'ancienne valeaure du bateau en abscisse
    int tampon_y = bateau[indice].position_y;                                   //Variable permettant de sauvegarder l'ancienne valeure du bateau en ordonnée

    do {
        orientation = rand()%2;                                                 //Générer un nouvelle orientation pour le bateau à déplacer entre les deux tours
        if(orientation == 1){                                                   //Si cette orientation est horizontale
            bateau[indice].orientation = 'H';
            nb_case = rand()%3 + 1;                                             //Générer le nombre de case de déplacement du bateau entre les deux tours
            signe = rand()%2;                                                   //Générer un nombre permettant si ce déplacement sera négatif ou positif sur la grille
            if(signe == 1) {
                bateau[indice].position_x = tampon_x + nb_case;
            }else{                                                              //Affectation de la nouvelle place en x du bateau en fonction du signe
                bateau[indice].position_x = tampon_x - nb_case;
            }
        }else{                                                                  //Si cette orientation est verticale
            bateau[indice].orientation = 'V';
            nb_case = rand()%3 + 1;                                             //Générer le nombre de case de déplacement du bateau entre les deux tours
            signe = rand()%2;                                                   //Générer un nombre permettant si ce déplacement sera négatif ou positif sur la grille
            if(signe == 1) {
                bateau[indice].position_y = tampon_y + nb_case;
            }else{                                                              //Affectation de la nouvelle place en y du bateau en fonction du signe
                bateau[indice].position_y = tampon_y - nb_case;
            }
        }
                                                                                //Répeter cela tant que le bateau dépasse de la grille ou qu'il chevauche un autre bateau de la grille
    } while (app_grille(bateau, indice) == 1 || chevauchement(bateau, indice, *tableau_bateau) == 1);

    printf("Un bateau de taille %d s'est deplace de %d case(s)\nInfo :"
           " Il a desormais une orientation %c\n", (bateau[indice]).taille,nb_case, (bateau[indice].orientation));
    if(orientation == 1){                                                                                   //Replacer le bateau sur la grille selon sa nouvelle position
        for(i = bateau[indice].position_x; i < bateau[indice].position_x + bateau[indice].taille; i++){
            (*tableau_bateau).grille[i][bateau[indice].position_y] = indice + 'a';
        }
    }else{
        for(i = bateau[indice].position_y; i < bateau[indice].position_y + bateau[indice].taille; i++) {
            (*tableau_bateau).grille[bateau[indice].position_x][i] = indice + 'a';
        }
    }
}