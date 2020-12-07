//
// Created by Roberto on 07/12/2020.
//

#ifndef GIOCO_DI_RUOLO_INVENTARIO_H
#define GIOCO_DI_RUOLO_INVENTARIO_H
#define MAXLEN 50
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct {
    char nome[MAXLEN+1];
    char tipo[MAXLEN+1];
    stat_t stateq;
} inv_t;

typedef  struct {
    int nInv;
    inv_t* vettInv;
} tabInv_t;
tabInv_t* caricastruttura(tabInv_t* tabInv);
void stampaInventario(FILE *fp, tabInv_t* tabInv);
void stampaOggetto(tabInv_t* tabInv);
void ricercaoggetto(tabInv_t* tabInv);
inv_t* ricerca_per_codice_oggetto( tabInv_t *tabInv);
inv_t* ricerca_per_codice_oggetto2( tabInv_t *tabInv);
void stampainfoOggetto(tabInv_t *tabInv, inv_t* inv );

#endif //GIOCO_DI_RUOLO_INVENTARIO_H
