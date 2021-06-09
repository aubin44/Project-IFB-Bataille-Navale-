#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "Initialisation_grille.h"
#include "Type_de_partie.h"
#include "Sauvegarde.h"


int main(){
    Grid grille_de_jeu, grille_bateaux;
    Boat bateau[5];
    Inventory stuff;
    grille_de_jeu.hauteur = 10;     //Initialisation de la taille des grilles de jeu
    grille_de_jeu.largeur = 10;
    grille_bateaux.hauteur = 10;
    grille_bateaux.largeur = 10;
    int Coo_X, Coo_Y;
    int i;
    int check2, mode;
    char rep, sauvegarde;
    srand(time(0));

    bateau[0].taille = 5;           //Initialisation de la taille des 5 bateaux
    bateau[1].taille = 4;
    bateau[2].taille = 3;
    bateau[3].taille = 3;
    bateau[4].taille = 2;

    printf("Que choisissez vous ?\n - C : Charger une ancienne partie\n - N : Nouvelle partie\n - Q : Quitter\n");
    fflush(stdin);
    rep = getchar();
    rep = toupper(rep);
    if(rep == 'C'){

        lancement_mode_sauvegarde(stuff, mode, grille_bateaux, sauvegarde, Coo_X, Coo_Y, grille_de_jeu);

    }else if( rep == 'N') {

        init_grille(&grille_bateaux);
        init_grille(&grille_de_jeu);

        for (i = 0; i < 5; i++) {
            do {
                genere_bateau(&bateau, i, grille_bateaux);

            } while (app_grille(bateau, i) == 1 || chevauchement(bateau, i, grille_bateaux) == 1);
            /*printf("Le bateau de taille %d et d'orientation %c se trouve en (%d,%c)\n", bateau[i].taille,
                   bateau[i].orientation, bateau[i].position_x + 1, 'A'+bateau[i].position_y);*/                //Verif code

            placement_bateaux(bateau, i, &grille_bateaux);

        }
        /*show_grid(grille_bateaux);*/                      //Vérif code

        lancement_nouvelle_partie(grille_de_jeu, grille_bateaux, bateau, check2, stuff, rep, Coo_X, Coo_Y, sauvegarde);

    }else if(rep == 'Q'){
        printf("A bientot pour une prochaine partie");
        return 0;
    }
    return 0;
}


