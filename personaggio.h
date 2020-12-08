//
// Created by Roberto on 07/12/2020.
//

#ifndef GIOCO_DI_RUOLO_PERSONAGGIO_H
#define GIOCO_DI_RUOLO_PERSONAGGIO_H
#define MAXLEN 50

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inventario.h"

typedef struct
{
    int inUso;
    inv_t * vettEq[8];
    int mark[8];
} tab_Equip_t;

typedef  struct nodoPg_t* link;
typedef struct node {
    char codice [MAXLEN+1];
    char nome[MAXLEN+1];
    char classe[MAXLEN+1];
    tab_Equip_t* equip;
    stat_t stat;
} pg_t;

struct nodoPg_t {
    pg_t pg;
    link next;
};

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
} tabPg_t;


tabPg_t* caricapg( tabPg_t* tabPg);
tabPg_t* inializzainventariopg(tabPg_t *tabPg);
tabPg_t* aggiungipg(tabPg_t* tabPg);
tabPg_t*  eliminaPg(tabPg_t* tabPg);

link nuovoNodo(pg_t p,link next);
link Inserimentointesta_nonordinato(link head,pg_t p);
link Inserimentoinlista_ordinata(link head,pg_t p);
void stampaListaPg(tabPg_t* tabPg);
void stampaLista(FILE* fp,link head);
void stampainfo(FILE* fp,pg_t p);
void stampainfo2(FILE* fp,pg_t p);
pg_t ricerca_per_codice(link head);
void ricerca_per_codicePg( tabPg_t*  tabPg);
void dettaglipg(tabPg_t* tabPg,tabInv_t *tabInv);
void stampaInventarioPg(FILE *fp, pg_t pg);
tabPg_t* aggiungi_rimuovi(tabPg_t *tabPg, tabInv_t *tabInv);
link aggiungiunoggetto(tabPg_t *tabPg, tabInv_t *tabInv, pg_t personaggio_damodificare);
link rimuoviunoggetto(tabPg_t *tabPg, tabInv_t *tabInv,pg_t personaggio_damodificare);
tabPg_t *calcolastat(tabPg_t *tabPg);
void stampaStat(FILE *fp, pg_t p);
tabPg_t *aggiornastat(tabPg_t *tabPg, pg_t pgchiave);

#endif //GIOCO_DI_RUOLO_PERSONAGGIO_H
