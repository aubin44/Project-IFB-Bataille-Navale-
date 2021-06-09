cmake_minimum_required(VERSION 3.19)
project(New_project_ifb C)

set(CMAKE_C_STANDARD 99)

add_executable(New_project_ifb main.c Execution_tir.c Execution_tir.h Initialisation_grille.c Initialisation_grille.h Type_de_partie.c Type_de_partie.h Sauvegarde.c Sauvegarde.h Etat_partie.c Etat_partie.h)