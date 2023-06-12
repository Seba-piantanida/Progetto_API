#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

#define MAXINT 2147483647

int dimPercorso = MAXINT;
char stringa[20];
/*get_charunlocked più veloce di get char va bene se non ci sono thread*/

typedef struct Auto{
    unsigned int autonomia;
    struct Auto* next;
} Auto;

typedef struct Stazione {
    unsigned int distanza;
    struct Auto* veicoli;
    struct Stazione* ragDX;
    struct Stazione* ragSX;
    struct Stazione* precedente;
    struct Stazione* successivo;
} Stazione;

typedef struct Percorso {
    unsigned int distanza;
    struct Percorso* next;
} Percorso;


Stazione* testa = NULL;
Stazione* coda = NULL;

Stazione * creaStazione(unsigned int distanza){
    Stazione* nuova_stazione = malloc(sizeof(Stazione));
    nuova_stazione->veicoli = NULL;
    nuova_stazione->distanza = distanza;
    nuova_stazione->precedente = NULL;
    nuova_stazione->successivo = NULL;
    return nuova_stazione;
}

Auto* creaAuto(unsigned int autonomia){
    Auto* nuova_auto = malloc(sizeof(Auto));
    nuova_auto -> autonomia = autonomia;
    nuova_auto -> next = NULL;
    return nuova_auto;
}

void cancellaListaAuto(Auto* lista){
    if (lista == NULL){
        return;
    }
    cancellaListaAuto(lista->next);
    free(lista);

}

void aggiungiStazione(Stazione* stazione){
    if (testa == NULL){
        testa = stazione;
        coda = stazione;
        return;
    }
    Stazione* curr;
    if (stazione->distanza > (coda->distanza) / 2){
        curr = coda;
        while (curr ->precedente != NULL && curr->precedente->distanza > stazione->distanza){
            curr = curr->precedente;
        }
        if (curr->precedente->distanza == stazione->distanza){
            printf("non aggiunta");
            return;
        }
        stazione->precedente = curr->precedente;
        stazione->successivo = curr;
        curr->precedente = stazione;
        stazione->precedente->successivo = stazione;
        printf("aggiunta");
        /*aggiungi dal fondo*/
    }
    else{
        curr = testa;
        while (curr ->successivo != NULL && curr->successivo->distanza < stazione->distanza){
            curr = curr->successivo;
        }
        if (curr->successivo->distanza == stazione->distanza){
            printf("non aggiunta");
            return;
        }
        stazione ->successivo = curr->successivo;
        stazione->precedente = curr;
        curr->successivo = stazione;
        stazione->successivo->precedente = stazione;
        printf("aggiunta");
        /*aggiungi dalla testa*/
    }
}

int demolisciStazione(unsigned int distanza){
     if (testa == NULL) {
        return;
    }

    Stazione* curr = testa;

    while (curr != NULL) {
        if (curr->distanza == distanza) {
            if (curr == testa && curr == coda) {
                testa = NULL;
                coda = NULL;
            } else if (curr == testa) {
                testa = curr->successivo;
                testa->precedente = NULL;
            } else if (curr == coda) {
                coda = curr->precedente;
                coda->successivo = NULL;
            } else {
                curr->precedente->successivo = curr->successivo;
                curr->successivo->precedente = curr->precedente;
            }
            cancellaListaAuto(curr->veicoli);
            free(curr);
            return;
        }
        curr = curr->successivo;
    }

   
}

void aggiungiAuto(unsigned int stazione, unsigned int autonomia){

}

int rottamaAuto(unsigned int stazione, unsigned int autonomia){
    Stazione* temp = testa;
    for(;temp->successivo != NULL; temp = temp->successivo){
        if (temp->distanza = stazione){
            /*rimuovi auto*/
            return true;
        }
    }
    return false;

}

void pianificaPercorso(unsigned int partenza, unsigned int arrivo){

}

Auto* creaListaAuto(Auto* lista, int autonomia){
    Auto* nuova_auto = creaAuto(autonomia);
    if (lista == NULL || lista->autonomia < autonomia){
        nuova_auto -> next = lista;
        return nuova_auto;
    }

    Auto* curr = lista;
    while (curr -> next != NULL && curr->next->autonomia > autonomia)
    {
        curr = curr ->next;
    }
    nuova_auto -> next = curr->next;
    curr->next = nuova_auto;
    return lista;
}

int main(){
    unsigned int stazione;
    unsigned int autonomia;
    while (scanf("%s ", stringa) != EOF)
    {
        if(strcmp(stringa, "aggiungi-stazione "))
        {
            int distanza;
            int macchina, i = 0;
            char temp;

            scanf("%d%c", &distanza, &temp);
            Stazione* nuova_stazione = creaStazione(distanza);
            Auto* primaAuto = NULL;
            if (temp != "\n"){

                    do{
                        scanf("%d%c", &macchina, &temp);
                        primaAuto = creaListaAuto(primaAuto, macchina);
                    } while (temp != '\n');
            }
            nuova_stazione -> veicoli = primaAuto;
            aggiungiStazione(nuova_stazione);

        }
        else if (strcmp(stringa, "demolisci-stazione "))
        {
            scanf("%d", &stazione);
            if (demolisciStazione(stazione)){
                printf("demolita");
            }else{
                printf("non demolita");
            }
        }

        else if (strcmp(stringa, "aggiungi-auto "))
        {
            scanf("%d %d", &stazione, &autonomia);
            aggiungiAuto(stazione, autonomia);
        }

        else if (strcmp(stringa, "rottama-auto "))
        {
            scanf("%d %d", &stazione, &autonomia);
            if (rottamaAuto(stazione, autonomia)){
                printf("rottamata");
            }else{
                printf("non rottamata");
            }
        }

        else if (strcmp(stringa, "pianifica-percorso "))
        {
            
        }
        else
        {
            return 0;
        }
        
    }
    
    return 0;
}