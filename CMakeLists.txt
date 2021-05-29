cmake_minimum_required(VERSION 3.19)
project(New_project_ifb C)

set(CMAKE_C_STANDARD 99)

add_executable(New_project_ifb main.c Depart_Grille.c Depart_Grille.h Execution_tir.c Execution_tir.h Etat_Grille.c Etat_Grille.h)