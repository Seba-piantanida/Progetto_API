#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

#define MAXINT 2147483647

int dimPercorso = MAXINT;


typedef struct Auto{
    unsigned int autonomia;
    struct Auto* next;
} Auto;

typedef struct Stazione {
    unsigned int distanza;
    unsigned int peso;
    struct Stazione* prev;
    struct Auto* veicoli;
    struct Stazione* precedente;
    struct Stazione* successivo;
} Stazione;


Stazione* testa = NULL;
Stazione* coda = NULL;
Stazione* cache = NULL;

Stazione * creaStazione(unsigned int distanza){
    Stazione* nuova_stazione = malloc(sizeof(Stazione));
    nuova_stazione->peso = MAXINT;
    nuova_stazione->prev = NULL;
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
        printf("aggiunta\n");
        return;
    }
    Stazione* curr;
    if (stazione->distanza > (coda->distanza) / 2){
        curr = coda;
        while (curr  != NULL && curr->distanza > stazione->distanza){
            curr = curr->precedente;
        }
        
        if (curr != NULL && curr->distanza == stazione->distanza){
            printf("non aggiunta\n");
            return;

        }
        if (curr == NULL){
            testa->precedente = stazione;
            stazione->successivo = testa;
            testa = stazione;
            printf("aggiunta\n");
            return;
        }
        if (coda == curr){
            coda = stazione;
            stazione->successivo = curr->successivo;
            curr->successivo = stazione;
            stazione->precedente = curr;
            printf("aggiunta\n");
            return;
        }
        stazione->successivo = curr->successivo;
        curr->successivo = stazione;
        stazione->precedente = curr;
        stazione->successivo->precedente = stazione;

        printf("aggiunta\n");
        /*aggiungi dal fondo*/
    }
    else{
        curr = testa;
        while (curr  != NULL && curr->distanza < stazione->distanza){
            curr = curr->successivo;
        }
        if (curr != NULL && curr->distanza == stazione->distanza){
            printf("non aggiunta\n");
            return;
        }
        if (curr == NULL){
            coda->successivo = stazione;
            stazione->precedente = coda;
            coda = stazione;
            printf("aggiunta\n");
            return;
        }
        if (testa == curr){
            testa = stazione;
            stazione->precedente = curr->precedente;
            curr->precedente = stazione;
            stazione->successivo = curr;
            printf("aggiunta\n");
            return;
        }
        stazione->precedente = curr->precedente;
        curr->precedente = stazione;
        stazione->successivo = curr;
        stazione->precedente->successivo = stazione;
        
        printf("aggiunta\n");
        /*aggiungi dalla testa*/
    }
}

int demolisciStazione(unsigned int distanza){
     if (testa == NULL) {
        return false;
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
            return true;
        }
        curr = curr->successivo;
    }
    return false;

   
}

void aggiungiAuto(unsigned int stazione, unsigned int autonomia){
    if (testa != NULL && stazione->distanza > (coda->distanza) / 2){
         Stazione* curr = coda;
        if (cache != NULL && cache->distanza == stazione){
            curr = cache;
        }
        while (curr != NULL){
            if (curr->distanza == stazione){
                Auto* prev = NULL;
                Auto* temp = curr->veicoli;
                cache = curr;

                while (temp != NULL && temp->autonomia > autonomia)
                {
                    prev = temp;
                    temp = temp->next; 
                }
                if (temp == NULL){
                    Auto* nuova_auto = creaAuto(autonomia);
                    curr->veicoli = nuova_auto;
                    printf("aggiunta\n");
                    return;
                }
                Auto* nuova_auto = creaAuto(autonomia);
                if (prev == NULL){
                    nuova_auto->next = temp;
                    curr->veicoli = nuova_auto;
                    printf("aggiunta\n");
                    return;
                }
                prev->next = nuova_auto;
                nuova_auto->next = temp;
                printf("aggiunta\n");
                return;
            }
            curr = curr->precedente;
        }
        printf("non aggiunta\n");
        return;

    }else {
        Stazione* curr = testa;
        if (cache != NULL && cache->distanza == stazione){
            curr = cache;
        }
        while (curr != NULL){
            if (curr->distanza == stazione){
                Auto* prev = NULL;
                Auto* temp = curr->veicoli;
                cache = curr;

                while (temp != NULL && temp->autonomia > autonomia)
                {
                    prev = temp;
                    temp = temp->next; 
                }
                if (temp == NULL){
                    Auto* nuova_auto = creaAuto(autonomia);
                    curr->veicoli = nuova_auto;
                    printf("aggiunta\n");
                    return;
                }
                Auto* nuova_auto = creaAuto(autonomia);
                if (prev == NULL){
                    nuova_auto->next = temp;
                    curr->veicoli = nuova_auto;
                    printf("aggiunta\n");
                    return;
                }
                prev->next = nuova_auto;
                nuova_auto->next = temp;
                printf("aggiunta\n");
                return;
            }
            curr = curr->successivo;
        }
        printf("non aggiunta\n");
        return;
    }

}

int rottamaAuto(unsigned int stazione, unsigned int autonomia){
    Stazione* curr = testa;
    if (testa == NULL){
        return false;
    }
    while (curr != NULL)
    {
        if (curr->distanza == stazione){
            Auto* temp = curr->veicoli;
            if (temp == NULL){
                return false;
            }
            if (temp->autonomia == autonomia){
                curr->veicoli = curr->veicoli->next;
                free(temp);
                return true;
            }
            Auto* prev = NULL;
            while (temp != NULL){
                if (temp->autonomia == autonomia){
                    prev->next = temp->next;
                    free(temp);
                    return true;
                }
                prev = temp;
                temp = temp->next;
            }
        }
        curr = curr->successivo;
    }
    return false;

}
void reversePrint(Stazione* arrivo, Stazione* partenza){
    if (arrivo->distanza != partenza->distanza){
        reversePrint(arrivo->prev, partenza);
        printf(" %d", arrivo->distanza );
        return;
    }
    printf("%d", arrivo->distanza);
    return;
}

void pianificaPercorso(Stazione* partenza, unsigned int arrivo){
    Stazione* currSta = partenza;
    currSta->peso = 0;
    while (currSta != NULL && currSta->distanza < arrivo)
    {
        Stazione* vSta = currSta->successivo;
        while (vSta != NULL && ((currSta->veicoli->autonomia) >= (vSta->distanza - currSta->distanza)) && vSta->distanza <= arrivo)
        {
            if (vSta->peso > (currSta->peso + 1)){
                vSta->peso = currSta->peso + 1;
                vSta->prev = currSta;
            }
            vSta = vSta->successivo;
        }
        
        currSta = currSta->successivo;
    }
    if (currSta->peso >= MAXINT){
        printf("nessun percorso\n");
    }else{
        reversePrint(currSta, partenza);
        printf("\n");
    }
    currSta = partenza;
    while (currSta != NULL && currSta->distanza <= arrivo)
    {
        currSta->peso = MAXINT;
        currSta->prev = NULL;
        currSta = currSta->successivo;
    }
    return;
}

void pianificaPercorsoBW(Stazione* partenza, unsigned int arrivo){
    Stazione* currSta = partenza;
    currSta->peso = 0;
    while (currSta != NULL && currSta->distanza > arrivo)
    {
        Stazione* vSta = currSta->precedente;
        while (vSta != NULL && ((currSta->veicoli->autonomia) >= (currSta->distanza - vSta->distanza)) && vSta->distanza >= arrivo)
        {
            if (vSta->peso >= (currSta->peso + 1)){
                vSta->peso = currSta->peso + 1;
                vSta->prev = currSta;
            }
            vSta = vSta->precedente;
        }
        
        currSta = currSta->precedente;
    }
    if (currSta->peso >= MAXINT){
        printf("nessun percorso\n");
    }else{
        reversePrint(currSta, partenza);
        printf("\n");
    }
    currSta = partenza;
    while (currSta != NULL && currSta->distanza >= arrivo)
    {
        currSta->peso = MAXINT;
        currSta->prev = NULL;
        currSta = currSta->precedente;
    }
    return;

}


int main(){
    unsigned int stazione;
    unsigned int autonomia;
    int read;
    char stringa[20];
    while (scanf("%19s", stringa) != EOF)
    {
        if(!strcmp(stringa, "aggiungi-stazione"))
        {
            int distanza;
            int macchina;
            char temp;

            read = scanf(" %d%c", &distanza, &temp);
            Stazione* nuova_stazione = creaStazione(distanza);
            Auto* primaAuto = NULL;
            if (temp != '\n'){
                    do{
                        read = scanf("%d%c", &macchina, &temp);
                        primaAuto = creaListaAuto(primaAuto, macchina);
                    } while (temp != '\n');
            }
            nuova_stazione -> veicoli = primaAuto;
            aggiungiStazione(nuova_stazione);

        }
        else if (!strcmp(stringa, "demolisci-stazione"))
        {
            read = scanf(" %d", &stazione);
            if (demolisciStazione(stazione)){
                printf("demolita\n");
            }else{
                printf("non demolita\n");
            }
        }
        else if (!strcmp(stringa, "aggiungi-auto"))
        {
            read = scanf("%d %d", &stazione, &autonomia);
            aggiungiAuto(stazione, autonomia);
            if (read < 0){
                printf("errore");
            }
        }
        else if (!strcmp(stringa, "rottama-auto"))
        {
            read = scanf("%d %d", &stazione, &autonomia);
            if (rottamaAuto(stazione, autonomia)){
                printf("rottamata\n");
            }else{
                printf("non rottamata\n");
            }
        }
        else if (!strcmp(stringa, "pianifica-percorso"))
        {
            unsigned int partenza, arrivo;
            read = scanf("%d %d", &partenza, &arrivo);
            if(arrivo == partenza){
                printf("%d\n", partenza);
                /*percorso immediato*/
            }else if (partenza < arrivo)
            {
                Stazione* start = testa;
                while (start->distanza != partenza && start != NULL)
                {
                    start = start->successivo;
                }
                if (start == NULL){
                    printf("nessun percorso\n");
                }else{
                    pianificaPercorso(start, arrivo);
                }
            }else{
                Stazione* start = coda;
                while (start->distanza != partenza && start != NULL)
                {
                    start = start->precedente;
                }
                if (start == NULL){
                    printf("nessun percorso\n");
                }else{
                    pianificaPercorsoBW(start, arrivo);
                }
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;

}
/*funzia fino a 24*/