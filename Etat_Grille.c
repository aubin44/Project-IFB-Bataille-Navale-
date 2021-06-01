//
// Created by Administrateur on 29/05/2021.
//
#include "Etat_Grille.h"
#include <stdio.h>
#include <stdlib.h>

void bateaux_restants(Grid tableau_bateau, int *bateau){
    int i,x, y;
    int nb_case = 0, nb_bateau = 0;
    for(i = 'a'; i<= 'e'; i++){                             //On utilise les caractères de marquage (a/b/c/d/e/A/B/C/D/E) placé dans le tableau contenant les bateau
        nb_case = 0;                                        //Cela nous permet de savoir combien de case ont été touchées par bateau
        for(x = 0; x < tableau_bateau.largeur; x++){
            for(y = 0; y < tableau_bateau.hauteur; y++){
                if(tableau_bateau.grille[x][y] == i){
                    nb_case = nb_case + 1;
                }
            }
        }
        if(nb_case > 0){                                    //Si le nombre de case non touchées est supérieur à 0 cela signifie que le bateau n'est pas coulé
            nb_bateau = nb_bateau + 1;
            printf("bateau%d : %d cases restantes\n", i - 'a' + 1, nb_case);
        }else if(nb_case == 0){                             //Si le nombre de case non touchées est de 0 cela signifie que le bateau est coulé
            printf("bateau%d : coule !\n", i - 'a' + 1);
        }
    }
    printf("Il reste %d bateaux a couler\n", nb_bateau);
    (*bateau) = nb_bateau;
}

void missiles_restants(Inventory missile){
    printf("Il vous reste :\n %d missile(s) d'artillerie\n %d missile(s) tactiques\n %d bombe(s)\n %d missile(s) simple\n",
           missile.nb_missile_artillery, missile.nb_missile_tactical, missile.nb_missile_bomb, missile.nb_missile_simple);
}

void check_loose(Inventory nb_missile){
    if(nb_missile.nb_missile_artillery == 0 && nb_missile.nb_missile_bomb == 0
       && nb_missile.nb_missile_simple == 0 && nb_missile.nb_missile_tactical == 0){
        printf("Vous n'avez plus de missiles. Vous avez perdu !");
        return exit(0);
    }
}