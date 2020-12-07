//
// Created by Roberto on 07/12/2020.
//

#include "inventario.h"
tabInv_t* caricastruttura(tabInv_t* tabInv) {

    int i;
    tabInv=malloc(sizeof(tabInv_t));
    FILE* fileinventario;
    fileinventario=fopen("inventario.txt","r");
    if(fileinventario==NULL)
    {
        printf("File non presente");
        exit(1);
    }
    fscanf(fileinventario,"%d",&tabInv->nInv);
    tabInv->vettInv= malloc(tabInv->nInv * sizeof(inv_t));
    for(i=0;i<tabInv->nInv;i++)
    {
        fscanf(fileinventario,"%s %s %d %d %d %d %d %d ", tabInv->vettInv[i].nome,tabInv->vettInv[i].tipo,&tabInv->vettInv[i].stateq.hp,
               &tabInv->vettInv[i].stateq.mp,&tabInv->vettInv[i].stateq.atk,&tabInv->vettInv[i].stateq.def,&tabInv->vettInv[i].stateq.mag,&tabInv->vettInv[i].stateq.spr);
    }
    fclose(fileinventario);
    stampaInventario(stdout,tabInv);
    return tabInv;
}
void stampaInventario(FILE *fp, tabInv_t* tabInv) {

    int i;
    for(i=0;i<tabInv->nInv;i++)
    {
        fprintf(fp,"%s %s %d %d %d %d %d %d\n", tabInv->vettInv[i].nome,tabInv->vettInv[i].tipo,tabInv->vettInv[i].stateq.hp,
                tabInv->vettInv[i].stateq.mp,tabInv->vettInv[i].stateq.atk,tabInv->vettInv[i].stateq.def,tabInv->vettInv[i].stateq.mag,tabInv->vettInv[i].stateq.spr);
    }

}
void stampaOggetto(tabInv_t* tabInv)
{
    inv_t* inv = ricerca_per_codice_oggetto2(tabInv);
    if(inv!=NULL) stampainfoOggetto(tabInv,inv);
    else printf("Oggetto assente in inventario");

}


void stampainfoOggetto(tabInv_t *tabInv, inv_t* inv )
{
    int i;
    int trovato=0;

    for(i=0;i<tabInv->nInv;i++) {
        if (strcmp(tabInv->vettInv[i].nome, inv->nome) == 0) {
            trovato = 1;
            printf("Nome oggetto :%s\n", inv->nome);
            printf("Tipo oggetto : %s\n", inv->tipo);
            printf("HP: %d\n", inv->stateq.hp);
            printf("MP: %d\n", inv->stateq.mp);
            printf("ATK: %d\n", inv->stateq.atk);
            printf("DEF: %d\n", inv->stateq.def);
            printf("MAG: %d\n", inv->stateq.mag);
            printf("SPR: %d\n", inv->stateq.spr);

        }
    }
    if(!trovato)
    printf("Oggetto non presente in inventario");
}
void ricercaoggetto(tabInv_t* tabInv)
{
    inv_t* inv = ricerca_per_codice_oggetto2(tabInv);
    if(inv!=NULL) stampainfoOggetto(tabInv,inv);
    else printf("Oggetto assente in inventario");
}

inv_t* ricerca_per_codice_oggetto( tabInv_t *tabInv) {

    int i;
    char nomeoggetto[MAXLEN+1];
    printf("Che oggetto vuoi aggiungere  o eliminare dall'equipaggiamento del personaggio?");
    scanf("%s",nomeoggetto);
    for(i=0;i<tabInv->nInv;i++)
    {
        if(strcmp(tabInv->vettInv[i].nome,nomeoggetto)==0)
            return &tabInv->vettInv[i];
    }
    return NULL; //OCCHIO ERRORE
    //rNULLeturn ;
}
inv_t* ricerca_per_codice_oggetto2( tabInv_t *tabInv) {

    int i;
    char nomeoggetto[MAXLEN+1];
    printf("Che oggetto  ti interessa dell'inventario?");
    scanf("%s",nomeoggetto);
    for(i=0;i<tabInv->nInv;i++)
    {
        if(strcmp(tabInv->vettInv[i].nome,nomeoggetto)==0)
            return &tabInv->vettInv[i];
    }
    return NULL; //OCCHIO ERRORE
    //rNULLeturn ;
}