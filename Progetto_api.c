#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

#define MAXINT 2147483647

int dimPercorso = MAXINT;

/*get_charunlocked più veloce di get char va bene se non ci sono thread*/

typedef struct Auto{
    unsigned int autonomia;
    struct Auto* next;
} Auto;

typedef struct Stazione {
    unsigned int distanza;
    struct Auto* veicoli;
    struct Stazione* precedente;
    struct Stazione* successivo;
} Stazione;

typedef struct Percorso {
    unsigned int distanza;
    unsigned int profondita;
    struct Percorso* next;
} Percorso;

void stampaPercorso(Percorso* percorso){
    
    while (percorso != NULL)
    {
        printf("%d ", percorso->distanza);
        Percorso* prev = percorso;
        percorso = percorso->next;
        free(prev);
    }
    
}

Percorso* creaNodoPercorso(unsigned int distanza, unsigned int profondita){
    Percorso* nuovoNodo = malloc(sizeof(Percorso));
    nuovoNodo->distanza = distanza;
    nuovoNodo->profondita = profondita;
    nuovoNodo->next = NULL;
    return nuovoNodo;
}

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
        return;
    }
    Stazione* curr;
    if (stazione->distanza > (coda->distanza) / 2){
        curr = coda;
        while (curr ->precedente != NULL && curr->precedente->distanza > stazione->distanza){
            curr = curr->precedente;
        }
        if (curr->precedente->distanza == stazione->distanza){
            printf("non aggiunta\n");
            return;
        }
        stazione->precedente = curr->precedente;
        stazione->successivo = curr;
        curr->precedente = stazione;
        stazione->precedente->successivo = stazione;
        printf("aggiunta\n");
        /*aggiungi dal fondo*/
    }
    else{
        curr = testa;
        while (curr ->successivo != NULL && curr->successivo->distanza < stazione->distanza){
            curr = curr->successivo;
        }
        if (curr->successivo->distanza == stazione->distanza){
            printf("non aggiunta\n");
            return;
        }
        stazione ->successivo = curr->successivo;
        stazione->precedente = curr;
        curr->successivo = stazione;
        stazione->successivo->precedente = stazione;
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
    Stazione* curr = testa;
    while (curr != NULL){
        if (curr->distanza == stazione){
            Auto* prev = NULL;
            Auto* temp = curr->veicoli;
            while (temp->autonomia > autonomia && temp != NULL)
            {
                prev = temp;
                temp = temp->next; 
            }
            if (temp->next->autonomia == autonomia){
                printf("non aggiunta\n");
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
    }
    printf("non aggiunta\n");
    return;

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

Percorso* pianificaPercorso(Stazione* partenza, unsigned int arrivo, int index){
    if(index >= dimPercorso){
        return NULL;
    }
    if((partenza->distanza + partenza->veicoli->autonomia) >= arrivo){
            /*trovato arrivo*/
            dimPercorso = index;
            return creaNodoPercorso(partenza->distanza, 0);

        }
    Stazione* start = partenza;
    Percorso* percorso = NULL;
    unsigned int profondita = MAXINT;
    while (start != NULL)
    {
        
        Percorso* temp = pianificaPercorso(start, arrivo, index + 1);
        if (temp != NULL && temp->profondita < profondita){
            profondita = temp->profondita;
            Percorso* nuovoNodo = creaNodoPercorso(partenza->distanza, profondita +1);
            nuovoNodo->next = temp;
            if (percorso == NULL){
                percorso = nuovoNodo;
            }else{
                Percorso* prev = percorso;
                temp = percorso;
                while (temp != NULL){
                    prev = temp;
                    temp = temp->next;
                    free(prev);
                }
                percorso = nuovoNodo;
            }
        }

        start = start->successivo;
    }
    return percorso;
    

}


int main(){
    unsigned int stazione;
    unsigned int autonomia;
    char stringa[20];
    while (scanf("%19s", stringa) != EOF)
    {
        if(!strcmp(stringa, "aggiungi-stazione"))
        {
            int distanza;
            int macchina, i = 0;
            char temp;

            scanf(" %d%c", &distanza, &temp);
            Stazione* nuova_stazione = creaStazione(distanza);
            Auto* primaAuto = NULL;
            if (temp != '\n'){

                    do{
                        scanf("%d%c", &macchina, &temp);
                        primaAuto = creaListaAuto(primaAuto, macchina);
                    } while (temp != '\n');
            }
            nuova_stazione -> veicoli = primaAuto;
            aggiungiStazione(nuova_stazione);

        }
        else if (!strcmp(stringa, "demolisci-stazione"))
        {
            scanf(" %d", &stazione);
            if (demolisciStazione(stazione)){
                printf("demolita\n");
            }else{
                printf("non demolita\n");
            }
        }

        else if (!strcmp(stringa, "aggiungi-auto"))
        {
            scanf("%d %d", &stazione, &autonomia);
            aggiungiAuto(stazione, autonomia);
        }

        else if (!strcmp(stringa, "rottama-auto"))
        {
            scanf("%d %d", &stazione, &autonomia);
            if (rottamaAuto(stazione, autonomia)){
                printf("rottamata\n");
            }else{
                printf("non rottamata\n");
            }
        }

        else if (!strcmp(stringa, "pianifica-percorso"))
        {
            unsigned int partenza, arrivo;
            scanf("%d %d", &partenza, &arrivo);
            if(arrivo == partenza){
                /*percorso immediato*/
            }else if (partenza < arrivo)
            {
                Stazione* start = testa;
                while (start->distanza != partenza && start != NULL)
                {
                    start = start->successivo;
                }
                if (start == NULL){
                    printf("percorso non trovato\n");
                }else{
                
                    Percorso* percorso = pianificaPercorso(start, arrivo, 0);
                    if (percorso != NULL){
                        printf("percorso trovato: ");
                        stampaPercorso(percorso);
                    }else
                    {
                        printf("percorso non trovato\n");
                    }
                }
            }
            
            dimPercorso = MAXINT;
        }
        else
        {
            return 0;
        }
        
    }
    
    return 0;
}