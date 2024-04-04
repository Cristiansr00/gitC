#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Componentes.h"


/*
-----------------PROTOTIPOS DE RUTINAS------------------
*/


/*
La rutina Lista_Vacia devuelve 1 si la lista que se le pasa
como parametro esta vacia y 0 si no lo esta.
*/
int Lista_Vacia(Lista lista){
    return (lista == NULL);
}

/*Num_Elementos es una funcion a la que se le pasa un puntero a una lista 
y devuelve el numero de elementos de dicha lista.
*/
int Num_Elementos(Lista  lista){
    Lista aux = lista;
    int i = 0;
    while (lista != NULL){
        i++;
        aux = aux->sig;
    }
    return i;
}

/*
La rutina Adquirir_Componente se encarga de recibir los datos de un nuevo 
componente (codigo y texto) que se le introducen por teclado y devolverlos 
por los parametros pasados por referencia "codigo" y "texto".
*/
void Adquirir_Componente(long *codigo,char *texto){
    printf("Introduce un codigo: ");
    scanf("%ld", codigo);
    printf("Introduce un texto: ");
    scanf("%s", texto);
    
}

/*
La funcion Lista_Imprimir se encarga de imprimir por pantalla la lista 
enlazada completa que se le pasa como parametro.
*/
void Lista_Imprimir( Lista lista){
    Lista aux = lista;
    while(aux!=NULL){
        printf("c: %ld, %s\n",aux->codigoComponente, aux->textoFabricante);
        aux = aux->sig;
    }
}

/*
La funcion Lista_Salvar se encarga de guardar en el fichero binario 
"examen.dat" la lista enlazada completa que se le pasa como parametro. 
Para cada nodo de la lista, debe almacenarse en el fichero
el código y el texto de la componente correspondiente.
*/
void Lista_Salvar( Lista  lista){
    FILE * fd = fopen("examen.dat", "wb");
    if (fd == NULL){
        perror("Error al abrir el fichero");
        exit(1);
    }
    Lista aux = lista;
    while(aux!=NULL && fwrite(aux, sizeof(Componente), 1, fd) == 1){
        aux = aux->sig;
    }
}


/*
La funcion Lista_Crear crea una lista enlazada vacia
de nodos de tipo Componente.
*/
Lista Lista_Crear(){
    Lista lista = NULL;
    return lista;
}

/*
La funcion Lista_Agregar toma como parametro un puntero a una lista,
el código y el texto de un componente y  anyade un nodo al final de 
la lista con estos datos.
*/
void Lista_Agregar(Lista *lista, long codigo, char* textoFabricante){
    Lista curr, ant;
    curr = *lista;
    ant = NULL;

    while(curr != NULL){
        ant = curr;
        curr = curr->sig;
    }
    Lista nuevo = (Lista) malloc(sizeof(Componente));
    if (nuevo == NULL){
        perror("Error al crear el nuevo nodo");
        exit(1);
    }
    nuevo->codigoComponente = codigo;
    strcpy(nuevo->textoFabricante,textoFabricante);
    nuevo->sig = NULL;

    if(ant == NULL){
        *lista = nuevo;
    } else {
        ant->sig = nuevo;
    }

}

/*
Lista_Extraer toma como parametro un puntero a una Lista y elimina el
Componente que se encuentra en su ultima posicion.
*/
void Lista_Extraer(Lista *lista){
    Lista curr, ant;
    if(Lista_Vacia(*lista)){

    }else {
        curr = *lista;
        ant = NULL;
        while(curr->sig != NULL){
            ant = curr;
            curr = curr->sig;
        }
        if(ant == NULL){
            free(curr);
            *lista = NULL;
        }else{
            free(curr);
            ant->sig = NULL;
        }
    }
}

/*
Lista_Vaciar es una funcion que toma como parametro un puntero a una Lista
y elimina todos sus Componentes.
*/
void Lista_Vaciar(Lista *lista){
    Lista curr, sig;
    curr = *lista;
    while(curr != NULL){
        sig = curr->sig;
        free(curr);
        curr = sig;
    }
    *lista = NULL;
}
