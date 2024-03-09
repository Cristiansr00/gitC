#include <stdio.h>
#include <stdlib.h>
#include "arbolbb.h"

void crear(T_Arbol* arbol){

    *arbol = NULL;

}
// Destruye la estructura utilizada y libera la memoria.
void destruir(T_Arbol* arbol){

    if((*arbol) != NULL){
        destruir(&((*arbol)->izq));
        destruir(&((*arbol)->der));
        free((*arbol));
        *arbol = NULL;
    }

}
// Inserta num en el árbol. Si ya está insertado, no hace nada
void insertar(T_Arbol* arbol,unsigned num){
    if((*arbol) == NULL ){

        (*arbol) = (T_Arbol) malloc(sizeof(struct T_Nodo));

        if((*arbol) == NULL){
            perror("Error al crear el nuevo nodo");
            exit(1);
        }

        (*arbol)->dato = num;
        (*arbol)->izq = NULL;
        (*arbol)->der = NULL;

    } else if(num > (*arbol)->dato){

        insertar(&((*arbol)->der), num);

    } else if (num < (*arbol)->dato){

        insertar(&((*arbol)->izq), num);

    }
    
}
// Muestra el contenido del árbol en InOrden
void mostrar(T_Arbol arbol){

    if(arbol != NULL){
        mostrar(arbol->izq);
        printf("%d\n", arbol->dato);
        mostrar(arbol->der);
    }

}
// Guarda en disco el recorrido inOrden del árbol
void salvar(T_Arbol arbol, FILE* fichero){
    if(fichero == NULL){
        perror("Error el fichero no está abierto");
        exit(1);
    }

    if(arbol != NULL){
        salvar(arbol->izq, fichero);
        fwrite(&(arbol->dato), sizeof(arbol->dato), 1, fichero);
        salvar(arbol->der, fichero);
    }

}

// Guarda en fichero de texto el recorrido inOrden del árbol
void salvarTexto(T_Arbol arbol, FILE* fichero){

    if(fichero == NULL){
        perror("Error el fichero no está abierto");
        exit(1);
    }

    if(arbol != NULL){
        salvarTexto(arbol->izq, fichero);
        fprintf(fichero, "%d\n", arbol->dato);
        salvarTexto(arbol->der, fichero);
    }

}