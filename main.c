#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inventario.h"
#include "personaggio.h"
#define MAX 30
#define MAXLEN 50

typedef enum { r_caricapg,r_caricaoggetti,r_aggiungipg, r_eliminapg,r_ricerca,r_modifica,r_calcolastat,r_ricercaoggetto,r_stampapg,r_oggetto,r_fine,r_err} comando_e;
void menuParola(tabPg_t* tabPg,tabInv_t* tabInv);
void Tolower(char cmd[MAX+1]);
comando_e leggicomando();

int main() {

// il main è il modulo client contiene l'interfaccia utente/ menu

    setbuf(stdout,0);
    //FILE* fileinventario;
    tabPg_t* tabPg;
    tabInv_t* tabInv;
    menuParola(tabPg,tabInv);
    return 0;

}

void menuParola(tabPg_t* tabPg, tabInv_t* tabInv)
{

    comando_e codiceComando;

    int continua=1;
    while(continua)
    {
        codiceComando=leggicomando();
        switch (codiceComando)
        {

            case r_caricapg:    tabPg=caricapg(tabPg);
                                tabPg=inializzainventariopg(tabPg);
                break;

            case r_caricaoggetti: tabInv=caricastruttura(tabInv);
                break;

            case r_aggiungipg:    tabPg=aggiungipg(tabPg);
                break;

            case r_eliminapg: tabPg=eliminaPg(tabPg);
                break;

            case r_ricerca: ricerca_per_codicePg(tabPg);
                break;


            case r_modifica: /*tabPg=aggiungi_rimuovi(tabPg,tabInv);*/
                break;

            case r_calcolastat: /*tabPg=calcolastat(tabPg,tabInv);*/
                break;

            case r_ricercaoggetto: ricercaoggetto(tabInv);
                break;

            case r_stampapg:  stampaListaPg(tabPg);
            break;
            case r_oggetto: stampaOggetto(tabInv);
            break;

            case r_fine:
                continua=0;
                break;
            case r_err :
            default: printf("Comando Errato\n");

        }
    }
}



comando_e leggicomando()
{
    comando_e comando;
    char cmd[MAX+1];
    char* tabella[r_err]={"caricapg","caricaoggetti","aggiungipg","eliminapg","ricerca","modifica","calcolastat","ricercaoggetto","stampalistapg","stampaoggetto","fine"};
    printf("Comando (caricapg/caricaoggetti/aggiungipg/eliminapg/ricerca");
    printf("/modifica/calcolastat/ricercaoggetto/stampalistapg/stampaoggetto/fine): ");
    scanf("%s",cmd);
    Tolower(cmd);
    comando=r_caricapg;
    while(comando<r_err && strcmp(cmd,tabella[comando])!=0)
        comando++;

    return comando;
}

void Tolower(char cmd[MAX+1])
{
    int i=0;
    for(i=0; cmd[i]!='\0';i++)
    {
        cmd[i] = tolower(cmd[i]);
    }
}
