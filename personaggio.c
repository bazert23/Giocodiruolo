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
   // stampainfo(stdout,pchiave);
    {
        stampainfo2(stdout,pchiave);
        //stampaStat(stdout,pchiave);
    }
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
void stampainfo2(FILE* fp,pg_t p)
{
    fprintf(fp,"%s %s %s\n", p.codice, p.nome,p.classe);
}
void stampaInventarioPg(FILE *fp, pg_t pg)
{
    int i;
    int j=0;
    i=0;


    while(j<8 &&i<pg.equip->inUso ) {
        if (pg.equip->vettEq[j] != NULL) {
            fprintf(fp, "%s %s %d %d %d %d %d %d\n", pg.equip->vettEq[j]->nome, pg.equip->vettEq[j]->tipo,
                    pg.equip->vettEq[j]->stateq.hp,
                    pg.equip->vettEq[j]->stateq.mp, pg.equip->vettEq[j]->stateq.atk,
                    pg.equip->vettEq[j]->stateq.def,
                    pg.equip->vettEq[j]->stateq.mag, pg.equip->vettEq[j]->stateq.mag);
            i++;
        }
        j++;
    }
}
void dettaglipg(tabPg_t* tabPg,tabInv_t *tabInv) {
    pg_t pchiave = ricerca_per_codice(tabPg->headPg);
    if (strcmp(pchiave.codice, "-1") == 0)
        printf("Personaggio non trovato\n");
    else
    {
        stampainfo2(stdout, pchiave);
        tabPg=aggiornastat(tabPg,pchiave);
       // tabPg=calcolastat(tabPg,tabInv);
       // stampaStat(stdout,pchiave);
        stampaInventarioPg(stdout,pchiave);
    }

}
tabPg_t* aggiungi_rimuovi(tabPg_t *tabPg, tabInv_t *tabInv) {

    int scelta;
    char personaggio[MAXLEN+1];

    printf("Premi 1 per aggiungere un oggetto all'equipaggiamento del personaggio\n");
    printf("Premi 2 per eliminare un oggetto dall'equipaggiamento del personaggio\n");

    scanf("%d",&scelta);
    switch (scelta)
    {
        /*aggigiungioggetto();*/
        case 1:  printf("Aggiungi\n");
            pg_t personaggio_damodificare=ricerca_per_codice(tabPg->headPg);
                if(strcmp(personaggio_damodificare.codice,"-1")==0)
                    printf("Personaggio non trovato\n");
                else {
                    tabPg->headPg = aggiungiunoggetto(tabPg, tabInv, personaggio_damodificare);
                }
            break;
            /*eliminaoggetto();*/
        case 2:  printf("Elimina\n");
            pg_t personaggio_damodificarer=ricerca_per_codice(tabPg->headPg);
            if(strcmp(personaggio_damodificarer.codice,"-1")==0)
                printf("Personaggio non trovato\n");
            else {
                tabPg->headPg = rimuoviunoggetto(tabPg, tabInv, personaggio_damodificarer);
            }
            break;
        default: printf("Errore");
            break;

    }
    return  tabPg;

}
link aggiungiunoggetto(tabPg_t *tabPg, tabInv_t *tabInv, pg_t personaggio_damodificare) {


    inv_t* oggetto_da_aggiungere=ricerca_per_codice_oggetto(tabInv);
    if(oggetto_da_aggiungere!=NULL) {
        int k = 0;

        for (k = 0; k < 8; k++) {
            if (personaggio_damodificare.equip->mark[k] == 0) {
                if (personaggio_damodificare.equip->vettEq[k] != NULL) {
                    personaggio_damodificare.equip->vettEq[k] = oggetto_da_aggiungere;
                    personaggio_damodificare.equip->mark[k] = 1;
                    personaggio_damodificare.equip->inUso++;
                    break;
                } else {
                    personaggio_damodificare.equip->vettEq[k] = malloc(sizeof(inv_t));
                    personaggio_damodificare.equip->vettEq[k] = oggetto_da_aggiungere;
                    personaggio_damodificare.equip->mark[k] = 1;
                    personaggio_damodificare.equip->inUso++;
                    break;
                }

                personaggio_damodificare.equip->inUso++;
            }
        }

        /*else
        {
            printf("Inventario pieno");
        }*/
        stampainfo2(stdout, personaggio_damodificare);
        stampaInventarioPg(stdout, personaggio_damodificare);
    }
    else printf("Oggetto non trovato\n");

    return tabPg->headPg;
}


link rimuoviunoggetto(tabPg_t *tabPg, tabInv_t *tabInv,pg_t personaggio_damodificare) {

    int i;
    int j;
    inv_t* oggetto_da_rimuovere=ricerca_per_codice_oggetto(tabInv);
    if(oggetto_da_rimuovere!=NULL) {

        if (personaggio_damodificare.equip->inUso > 0) {
            // personaggio_damodificare.equip->vettEq[personaggio_damodificare.equip->inUso] = oggetto_da_rimuovere;
            for (i = 0; i < personaggio_damodificare.equip->inUso; i++) {
                if (strcmp(personaggio_damodificare.equip->vettEq[i]->nome, oggetto_da_rimuovere->nome) == 0) {
                    personaggio_damodificare.equip->vettEq[i] = NULL;
                    //personaggio_damodificare.equip->vettEq[i]= malloc(sizeof(inv_t));
                    personaggio_damodificare.equip->mark[i] = 0;
                    //strcpy(personaggio_damodificare.equip->vettEq[i]->nome,"vuoto");
                }
            }
            personaggio_damodificare.equip->inUso--;


        } else {
            printf("Inventario vuoto");
        }
        stampainfo2(stdout, personaggio_damodificare);
        stampaInventarioPg(stdout, personaggio_damodificare);
    }
    else printf("Oggetto non trovato\n");
    return tabPg->headPg;

}

tabPg_t *aggiornastat(tabPg_t *tabPg, pg_t pgchiave)
{
    int i=0,j=0;

    while(j<8 &&i<pgchiave.equip->inUso ) {
        if (pgchiave.equip->vettEq[j] != NULL) {
            pgchiave.stat.hp+=pgchiave.equip->vettEq[j]->stateq.hp;
            pgchiave.stat.mp+=pgchiave.equip->vettEq[j]->stateq.mp;
            pgchiave.stat.atk+=pgchiave.equip->vettEq[j]->stateq.atk;
            pgchiave.stat.def+=pgchiave.equip->vettEq[j]->stateq.def;
            pgchiave.stat.mag+=pgchiave.equip->vettEq[j]->stateq.mag;
            pgchiave.stat.spr+=pgchiave.equip->vettEq[j]->stateq.spr;
            i++;
        }
        j++;
    }
    stampaStat(stdout,pgchiave);
    return tabPg;
}

tabPg_t *calcolastat(tabPg_t *tabPg) {

    pg_t pgchiave= ricerca_per_codice(tabPg->headPg);
    if(strcmp(pgchiave.codice,"-1")==0)
        printf("Personaggio non trovato\n");
    else {
        int i = 0, j = 0;


        while (j < 8 && i < pgchiave.equip->inUso) {
            if (pgchiave.equip->vettEq[j] != NULL) {
                pgchiave.stat.hp += pgchiave.equip->vettEq[j]->stateq.hp;
                pgchiave.stat.mp += pgchiave.equip->vettEq[j]->stateq.mp;
                pgchiave.stat.atk += pgchiave.equip->vettEq[j]->stateq.atk;
                pgchiave.stat.def += pgchiave.equip->vettEq[j]->stateq.def;
                pgchiave.stat.mag += pgchiave.equip->vettEq[j]->stateq.mag;
                pgchiave.stat.spr += pgchiave.equip->vettEq[j]->stateq.spr;
                i++;
            }
            j++;
        }


        stampaStat(stdout, pgchiave);
    }
    return tabPg;
}
void stampaStat(FILE *fp, pg_t p) {

    int standard = 0;
    if (p.stat.hp > 0) {
        fprintf(fp, "HP:%d\n", p.stat.hp);
    } else printf("HP: %d\n", standard);

    if (p.stat.mp > 0) {
        fprintf(fp, "MP:%d\n", p.stat.mp);
    } else printf("MP: %d", standard);

    if (p.stat.atk > 0) {
        fprintf(fp, "ATK:%d\n", p.stat.atk);
    } else printf("ATK: %d", standard);


    if (p.stat.def > 0) {
        fprintf(fp, "DEF:%d\n", p.stat.def);
    } else printf("DEF: %d", standard);

    if (p.stat.mag > 0) {
        fprintf(fp, "MAG:%d\n", p.stat.mag);
    } else printf("MAG: %d", standard);
    if (p.stat.spr > 0) {
        fprintf(fp, "SPR:%d\n", p.stat.spr);
    } else printf("SPR: %d", standard);
}