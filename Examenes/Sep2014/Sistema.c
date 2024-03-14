#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sistema.h"


void EliminarHebras(LHebra *lh);

void Crear(LSistema *l){
    *l = NULL;
}
//Inserta un proceso por orden de llegada.
void InsertarProceso ( LSistema *ls, int numproc){

    LSistema aux, ant;
    aux = *ls;
    ant = NULL;

    if(aux == NULL){
        *ls = (LSistema) malloc(sizeof(struct Nodo));
        if ( *ls==NULL ){
            perror("Error al almacenar el nuevo proceso");
            exit(1);
        }
        (*ls)->pid = numproc;
        (*ls)->sig = NULL;
        (*ls)->h = NULL;
    }else {
        while( aux!=NULL){
            ant = aux;
            aux = aux->sig;
        }
        
        aux = (LSistema) malloc(sizeof(struct Nodo));
        if ( aux==NULL ){
            perror("Error al almacenar el nuevo proceso");
            exit(1);
        }

        aux->pid = numproc;
        aux->sig = NULL;
        aux->h = NULL;

        ant->sig = aux;
    }
}
//Inserta una hebra en el proceso numproc teniendo en cuenta el orden de prioridad (mayor a menor)
void InsertarHebra (LSistema *ls, int numproc, char *idhebra, int priohebra){
    LSistema aux = *ls;
    
    while(aux != NULL && aux->pid != numproc){
        aux = aux->sig;
    }

    if(aux == NULL){
        perror("No se ha encontrado el proceso que buscabas");
        exit(1);
    }

    LHebra h = aux->h;
    LHebra ant = NULL;

    if( aux->h == NULL ){
        aux->h = (LHebra) malloc(sizeof(struct Hebra));
        if(aux->h == NULL){
            perror("No se ha podido crear la hebra correctamente");
            exit(1);
        }
        aux->h->idhebra = (char *) malloc(sizeof(char)*strlen(idhebra));
        if(aux->h->idhebra == NULL){
            perror("No se ha podido crear la hebra correctamente");
            exit(1);
        }
        strcpy(aux->h->idhebra,idhebra);
        aux->h->prio = priohebra;
        aux->h->sig = NULL;

    } else if( h->prio <= priohebra){
        LHebra h = (LHebra) malloc(sizeof(struct Hebra));
        if(h == NULL){
            perror("Error al crear una nueva hebra");
            exit(1);
        }
        h->idhebra = (char *) malloc(sizeof(char)*strlen(idhebra));
        if(h->idhebra == NULL){
            perror("Error al crear una nueva hebra");
            exit(1);
        }
        strcpy(h->idhebra,idhebra);
        h->prio = priohebra;
        h->sig = aux->h;

        aux->h = h;


    } else {
        while(h != NULL && h->prio > priohebra ){
            ant = h;
            h = h->sig;
        }
        if (h == NULL){
            h = (LHebra) malloc(sizeof(struct Hebra));
            if(h == NULL){
                perror("Error no se ha podido crear la hebra correctamente");
                exit(1);
            }
            h->idhebra = (char *) malloc(sizeof(char)*strlen(idhebra));
            if(h->idhebra == NULL){
                perror("Error no se ha podido crear la hebra correctamente");
                exit(1);
            }
            strcpy(h->idhebra,idhebra);
            h->prio = priohebra;
            h->sig = NULL;

            ant->sig = h;
        } else {
            LHebra nueva = (LHebra) malloc(sizeof(struct Hebra));
            if(nueva == NULL){
                perror("Error no se ha podido crear la hebra correctamente");
                exit(1);
            }
            nueva->idhebra = (char *) malloc(sizeof(char)*strlen(idhebra));
            if(nueva->idhebra == NULL){
                perror("Error no se ha podido crear la hebra correctamente");
                exit(1);
            }
            strcpy(nueva->idhebra,idhebra);
            nueva->prio = priohebra;
            nueva->sig = h;

            ant->sig = nueva;
        }
    }

}
//Muestra el contenido del sistema
void Mostrar (LSistema ls){

    LSistema curr = ls;
    LHebra hebra = NULL;
    while(curr != NULL){
        printf("P %d : ",curr->pid);
        hebra = curr->h;
        while(hebra != NULL){
            printf("%s->%d, ",hebra->idhebra,hebra->prio);
            hebra = hebra->sig;
        }
        printf("\n");
        curr = curr->sig;
    }
}
//Elimina del sistema el proceso con número numproc liberando la memoria de éste y de sus hebras.
void EliminarProc (LSistema *ls, int numproc){
    LSistema curr = *ls;
    LSistema ant = NULL;
    if(curr != NULL){
        while (curr != NULL && numproc != curr->pid) {
            ant = curr;
            curr = curr->sig;
        }
        EliminarHebras(&curr->h);
        ant->sig = curr->sig;
        free(curr);

        if(curr == *ls){
            (*ls) = NULL;
        }
    }
    
}
//Destruye toda la estructura liberando su memoria
void Destruir (LSistema *ls){
     LSistema curr, sig;
    sig = *ls;
    curr = NULL;

    while(sig != NULL){
        curr = sig;
        sig = sig->sig;
        EliminarHebras(&curr->h);
        free(curr);
    }
    free(curr);
    (*ls) = NULL;
}

void EliminarHebras(LHebra *lh){
    LHebra curr, ant;
    curr = *lh;
    ant = NULL;
    if(*lh != NULL){
        while(curr != NULL){
            ant = curr;
            curr = curr->sig;
            free(ant->idhebra);
            free(ant);
        }
        (*lh) = NULL;
    }
}