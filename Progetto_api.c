#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

char stringa[20];
/*get_charunlocked più veloce di get char va bene se non ci sono thread*/

typedef struct StazioneServizio {
    unsigned int distanza;
    struct StazioneServizio* precedente;
    struct StazioneServizio* successivo;
} StazioneServizio;

StazioneServizio* testa;
StazioneServizio* coda;

StazioneServizio * creaStazione(unsigned int distanza, int a){
    StazioneServizio* nuova_stazione = malloc(sizeof(StazioneServizio));
    nuova_stazione->distanza = distanza;
    nuova_stazione->precedente = NULL;
    nuova_stazione->successivo = NULL;
    return nuova_stazione;
}

void aggiungiStazione(StazioneServizio* stazione){
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

        }
        else if (strcmp(stringa, "pianifica-percorso "))
        {
            /* code */
        }
        else
        {
            return;
        }
        
    }
    
    return 0;
}