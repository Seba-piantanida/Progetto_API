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

Stazione * creaStazione(unsigned int distanza, int a){
    Stazione* nuova_stazione = malloc(sizeof(Stazione));
    nuova_stazione->distanza = distanza;
    nuova_stazione->precedente = NULL;
    nuova_stazione->successivo = NULL;
    return nuova_stazione;
}

void aggiungiStazione(Stazione* stazione){
    if (stazione->distanza > (coda->distanza) / 2){
        /*aggiungi dal fondo*/
    }
    else{
        /*aggiungi dalla testa*/
    }
}

void demolisciStazione(unsigned int stazione){

}

void aggiungiAuto(unsigned int stazione, unsigned int autonomia){

}

void rottamaAuto(unsigned int stazione, unsigned int autonomia){

}

void pianificaPercorso(unsigned int partenza, unsigned int arrivo){

}

int main(){
    unsigned int stazione;
    unsigned int autonomia;
    
    while (scanf("%s ", stringa) != EOF)
    {
        if(strcmp(stringa, "aggiungi-stazione "))
        {
            int distanza;
            int macchine[10], i = 0;
            char temp;

            scanf("%d", &distanza);
            do
            {
                scanf("%d%c", &macchine[i], &temp);
                i ++;
            } while (temp != '\n');
            
            


        }
        else if (strcmp(stringa, "demolisci-stazione "))
        {
            scanf("%d", &stazione);
            demolisciStazione(stazione);
        }
        else if (strcmp(stringa, "aggiungi-auto "))
        {
            scanf("%d %d", &stazione, &autonomia);
            aggiungiAuto(stazione, autonomia);
        }
        else if (strcmp(stringa, "rottama-auto "))
        {
            scanf("%d %d", &stazione, &autonomia);
            rottamaAuto(stazione, autonomia);
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