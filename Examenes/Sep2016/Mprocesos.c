#include <stdlib.h>
#include <stdio.h>
#include "Mprocesos.h"


void Crear(LProc *lroundrobin){
    *lroundrobin = NULL;
}

void AnadirProceso(LProc *lroundrobin, int idproc){
    LProc aux = (LProc) malloc(sizeof(struct T_Nodo));

    if(aux == NULL){
        perror("Error al introducir un nuevo nodo");
        exit(1);
    }

    if((*lroundrobin) == NULL){
        aux->pid = idproc;
        aux->sig = aux;

        *lroundrobin = aux;
    } else {
        aux->pid = idproc;
        aux->sig = (*lroundrobin)->sig;
        (*lroundrobin)->sig = aux;

        *lroundrobin = aux;
    }
}

void EjecutarProcesos(LProc lroundrobin){

    if(lroundrobin == NULL){
        printf("No hay procesos en la lista\n");
        return;
    } else {
        LProc aux = lroundrobin;
        printf("Ejecutando procesos...\n");
        do{
            aux = aux->sig;
            printf("Ejecutando proceso %d\n", aux->pid);
        } while(aux != lroundrobin);
    }
}


void EliminarProceso(int id, LProc *lista){
    LProc curr, aux;
    curr = (*lista)->sig;
    aux = *lista;

    if ((*lista) == NULL){
        printf("La lista esta vacia");
    } else {
        while(curr->pid != id){
            aux = curr;
            curr = curr->sig;
        }
        // Suponemos que lo hemos encontrado
        aux->sig = curr->sig;
        if (curr == *lista) {
            *lista = aux;
        }
        free(curr);
    }
}

void EscribirFichero (char * nomf, LProc *lista){
    FILE *fd = fopen(nomf,"wb");
    if(fd == NULL){
        perror("Error al abrir el fichero");
        exit(1);
    }

    if((*lista) == NULL){
        printf("La lista esta vacia");
    }else {
        LProc curr, sig;
        curr = (*lista)->sig;
        sig = curr->sig;
        (*lista)->sig = NULL;
        int n = 0;
        //vaciamos la lista y liberamos todo el espacio creado
        while(curr != NULL){
            n = fwrite(&(curr->pid),sizeof(curr->pid),1,fd);
            free(curr);
            curr = sig;
            if(sig != NULL){
                sig = sig->sig;
            }
        }   
        fclose(fd);
        (*lista) = NULL;
    }
}

void LeerFichero(char * nomf, LProc *lista){

    FILE * fd = fopen(nomf,"rb");
    if(fd == NULL){
        perror("El fichero no se ha podido abrir");
        exit(1);
    }

    int aux = 0;

    while(!feof(fd) && fread(&aux, sizeof(aux), 1, fd)){
        AnadirProceso(lista, aux);
    }

    fclose(fd);
}