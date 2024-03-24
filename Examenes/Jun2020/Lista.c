#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

void crear(TLista *lista){
    *lista = NULL;
}

/** Muestra el contenido de la lista.
 *   - Si la lista esta vacia muestra el mensaje "Lista vacia..."
 *   - Si la lista no esta vacia la muestra en el formato:
 *       <valor>:<palo> <valor>:<palo> <valor>:<palo>
 */
void mostrar(TLista lista){
    if(lista == NULL){
        printf("Lista vacia...");
    } else {
        TLista curr = lista;
        while(curr != NULL){
            printf("%d:%c ", curr->carta.valor, curr->carta.palo);
            curr = curr->sig;
        }
        printf("\n");
    }
}

/* Inserta la carta en la lista ordenada primero por el palo y luego,
 * para las cartas del mismo palo, por el valor.
 * En ambos casos en orden ascendente.
 *
 * Podemos suponer que la carta a insertar no esta en la lista.
 */
void insertarOrdenado(TLista *lista, TCarta carta){
    TLista curr, ant;
    curr = *lista;
    ant = NULL;


    while(curr != NULL && curr->carta.palo < carta.palo){
        ant = curr;
        curr = curr->sig;
    }

    while(curr != NULL && curr->carta.palo == carta.palo && curr->carta.valor < carta.valor){
        ant = curr;
        curr = curr->sig;
    }

    TLista nuevo = (TLista)malloc(sizeof(struct TNodo));
    nuevo->carta = carta;
    nuevo->sig = curr;
    
    if(ant == NULL){
        *lista = nuevo;
    } else {
        ant->sig = nuevo;
    }
}

/* Elimina toda la memoria dinamica reservada para la lista. */
void destruir(TLista *lista){

  TLista aux;
    while(*lista != NULL){
        aux = *lista;
        *lista = (*lista)->sig;
        free(aux);
    }
}

//PARTE 2
/* Borra una carta de la lista, teniendo en cuenta que la lista esta ordenada.
 * Se puede suponer que la carta a borrar estara en la lista.
 */
void borrar(TLista *lista, TCarta carta){
    TLista curr, ant;
    curr = *lista;
    ant = NULL;

    if(*lista == NULL){
        perror("no se pude eliminar la lista está vacia");
        exit(1);
    }

    while(curr != NULL && curr->carta.palo < carta.palo){
        ant = curr;
        curr = curr->sig;
    }
    while(curr != NULL && curr->carta.palo == carta.palo && curr->carta.valor < carta.valor){
        ant = curr;
        curr = curr->sig;
    }

    if(curr == *lista){
        *lista = (*lista)->sig;
    } else {
        ant->sig = curr->sig;
    }

    free(curr);
}

/* Descarta la primera carta de la lista2 que pueda ser insertada en la lista1 
 * siguiendo el siguiente criterio:
 *
 * Para poder descartar la carta (palo, valor) de la lista2 se hara lo siguiente:
 *   - se comprueba si en la lista1 existe una carta con el mismo palo y un valor
 *     inmediatamente anterior o posterior. Es decir, la carta (palo, valor-1) o (palo, valor + 1)
 *   - si existe, la carta se elimina de lista2 y se inserta en lista1, de forma que lista1
       siga estando ordenada.
 *
 *   La funcion devuelve 1 si el jugador ha podido descartarse una carta y 0 en otro caso.
 *   En cada llamada a esta funcion el jugador se descartara una sola carta, aunque haya mas
 *   cartas descartables en la mano del jugador.
 *   Se puede suponer que las cartas de lista2 no están en lista1.
 */

int descartar(TLista *lista1, TLista *lista2){

    TLista curr = *lista2;
    TLista aux, aux_ant;

    while(curr != NULL){
        
        aux = *lista1;
        aux_ant = NULL;

        while(aux != NULL && curr->carta.palo != aux->carta.palo){
            aux_ant = aux;
            aux = aux->sig;
        }
        while(aux != NULL && aux->carta.palo == curr->carta.palo && aux->carta.valor < curr->carta.valor){
            aux_ant = aux;
            aux = aux->sig;
        }

        if((aux_ant != NULL && aux_ant->carta.valor == curr->carta.valor -1 && aux_ant->carta.palo == curr->carta.palo) 
        || ( aux != NULL && aux->carta.valor == curr->carta.valor +1 && aux->carta.palo == curr->carta.palo)){
            insertarOrdenado(lista1, curr->carta);
            borrar(lista2, curr->carta);
            return 1;
        }

        curr = curr->sig;
    }

    return 0;

}

/* Suma y devuelve el valor de todas las cartas de la lista,
 * independientemente de su palo.
 */
int sumar(TLista lista){

    int valor = 0;
    TLista aux = lista;

    while(aux != NULL){
        valor += aux->carta.valor;
        aux = aux->sig;
    }

    return valor;
}