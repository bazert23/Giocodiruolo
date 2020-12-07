cmake_minimum_required(VERSION 3.15)
project(Gioco_di_ruolo C)

set(CMAKE_C_STANDARD 99)

add_executable(Gioco_di_ruolo main.c personaggio.c personaggio.h inventario.c inventario.h)