//
// Created by Roberto on 07/12/2020.
//

#include "personaggio.h"
tabPg_t* caricapg( tabPg_t* tabPg)
{
    FILE* filepg;
    pg_t pgprovvissorio;
    // leggo i personaggi e li includo in una lista di personaggi
    filepg=fopen("pg.txt","r");
    if(filepg==NULL)
    {
        printf("Errore in apertura del file");
        exit(-1);
    }

    tabPg->headPg=NULL;

    while(fscanf(filepg,"%s %s %s %d %d %d %d %d %d \n", pgprovvissorio.codice, pgprovvissorio.nome,pgprovvissorio.classe, &pgprovvissorio.stat.hp,
                 &pgprovvissorio.stat.mp,&pgprovvissorio.stat.atk,&pgprovvissorio.stat.def,&pgprovvissorio.stat.mag,&pgprovvissorio.stat.spr)!=EOF)
    {
        // tabPg->headPg=Inserimentointesta_nonordinato(tabPg->headPg,pgprovvissorio);
        tabPg->headPg=Inserimentoinlista_ordinata(tabPg->headPg,pgprovvissorio);
    }
    // chiudo il file
    fclose(filepg);
    stampaLista(stdout,tabPg->headPg);
    return  tabPg;
}

tabPg_t* aggiungipg(tabPg_t* tabPg) {

    /*if (tabPg->headPg == NULL)
    {
        printf("Errore: la lista e' vuota");
    }*/
    pg_t pgprovvisoriotastiera;
    printf("Inserisci il codice: \n");
    scanf("%s",pgprovvisoriotastiera.codice);
    printf("Inserisci il nome: \n");
    scanf("%s",pgprovvisoriotastiera.nome);
    printf("Inserisci la classe: \n");
    scanf("%s",pgprovvisoriotastiera.classe);
    printf("Inserisci  gli hp: \n");
    scanf("%d",&pgprovvisoriotastiera.stat.hp);
    printf("Inserisci gli mp: \n");
    scanf("%d",&pgprovvisoriotastiera.stat.mp);
    printf("Inserisci i punti atk: \n");
    scanf("%d",&pgprovvisoriotastiera.stat.atk);
    printf("Inserisci i punti def : \n");
    scanf("%d",&pgprovvisoriotastiera.stat.def);
    printf("Inserisci i punti mag : \n");
    scanf("%d",&pgprovvisoriotastiera.stat.mag);
    printf("Inserisci i punti spr: \n");
    scanf("%d",&pgprovvisoriotastiera.stat.spr);
    tabPg->headPg=Inserimentoinlista_ordinata(tabPg->headPg,pgprovvisoriotastiera);
    stampaLista(stdout,tabPg->headPg);
    return tabPg;

}
tabPg_t* eliminaPg(tabPg_t* tabPg)
{

    pg_t pgchiave= ricerca_per_codice(tabPg->headPg);
    link x,p;
    if(strcmp(pgchiave.codice,"-1")==0)
    {
        printf("Errore: Codice non presente");
        exit(-1);
    }
    else
    if (tabPg->headPg==NULL)
        return NULL;

    for(x=tabPg->headPg,p=NULL;
        x!=NULL;
        p=x,x=x->next)
    {
        if((strcmp(x->pg.codice,pgchiave.codice)==0))
        {
            if(x==tabPg->headPg)
                tabPg->headPg=x->next;
            else
                p->next=x->next;
            free(x);
            break;
        }
    }
    stampaLista(stdout,tabPg->headPg);
    return tabPg;
}
tabPg_t* inializzainventariopg(tabPg_t *tabPg) {
    link x=malloc(sizeof(*x));
    int j;
    if(x==NULL)
        exit(-1);
    else {
        for (x = tabPg->headPg; x != NULL; x = x->next) {
            x->pg.equip= malloc(sizeof(tab_Equip_t*));
            x->pg.equip->inUso= (int) malloc(sizeof(int));
            x->pg.equip->inUso=0;
            printf("%d\n",x->pg.equip->inUso);
            for(j=0;j<8;j++) {
                x->pg.equip->vettEq[j] = malloc(sizeof(tabInv_t *));
                x->pg.equip->mark[j] = 0;
            }

        }
    }
    return tabPg;
}
link Inserimentointesta_nonordinato(link head,pg_t p)
{
    head=nuovoNodo(p,head);
    return head;

}

int comparaCodice(char codice1[MAXLEN+1],char codice2[MAXLEN+1]) {
    return  strcmp(codice1,codice2);
}

link Inserimentoinlista_ordinata(link head,pg_t pg)
{

    link p = NULL, x = NULL;

    if(head == NULL || comparaCodice(head->pg.codice,pg.codice) > 0)
        return nuovoNodo(pg, head);
    for (x=head->next, p=head; x!=NULL && comparaCodice(pg.codice, x->pg.codice) > 0; p=x, x=x->next);
    p->next = nuovoNodo(pg, x);
    return head;
}



link nuovoNodo(pg_t p,link next)
{
    link x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    else
    {
        x->pg =p;
        x->next=next;
    }
    return x;
}
void stampaListaPg(tabPg_t* tabPg)
{
   stampaLista(stdout,tabPg->headPg);
}
void stampaLista(FILE* fp,link head)
{
    if(head==NULL)
        return ;
    stampainfo(fp,head->pg);
    stampaLista(fp,head->next);
}
void ricerca_per_codicePg( tabPg_t*  tabPg)
{
    pg_t pchiave= ricerca_per_codice(tabPg->headPg);
    if(strcmp(pchiave.codice,"-1")==0)
        printf("Personaggio non trovato\n");
    else
    stampainfo(stdout,pchiave);
}
pg_t ricerca_per_codice(link head)
{
    char codicedacercare[6+1];
    pg_t vuoto;
    strcpy(vuoto.codice,"-1");

    printf("Che codice cerchi?");
    scanf("%s",codicedacercare);

    link x;
    for(x=head; x!=NULL && x->next!=NULL;x=x->next)
    {
        if((strcmp(codicedacercare,x->pg.codice)==0))
            return x->pg;
    }

    return  vuoto;

}

void stampainfo(FILE* fp,pg_t p)
{
    fprintf(fp,"%s %s %s %d %d %d %d %d %d \n", p.codice, p.nome,p.classe, p.stat.hp,
            p.stat.mp,p.stat.atk,p.stat.def,p.stat.mag,p.stat.spr);
}
