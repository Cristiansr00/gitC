#include <stdlib.h>
#include <stdio.h>
#include "cifrado.h"

void crearEsquemaDeCifrado (TCifrado *cf){

    *cf = NULL;

}

/* (3 puntos) funcion que pone un nodo al final de un esquema de cifrado, si es posible.
 * Se debe devolver en el ultimo parametro un valor logico que sea verdadero si ha sido posible
 * realizar la operacion. No se debe suponer que el valor de box.sig es valido*/
void insertarBox (TCifrado * cf, struct TBox box, unsigned char *ok){

    TCifrado curr, ant;
    curr = *cf;
    ant = NULL;

    while(curr != NULL){
        ant = curr;
        curr = curr->sig;
    }

    if(ant == NULL && box.esSBox){
        curr = (TCifrado) malloc(sizeof(struct TBox));

        if(curr == NULL){
            perror("Error al crear nuevo nodo");
            exit(1);
        }

        curr->esSBox = box.esSBox;
        curr->valorASumar = box.valorASumar;

        curr->sig = NULL;
        *cf = curr;
        *ok = 1;

    } else if(ant != NULL) {

        if((ant->esSBox && !box.esSBox) || (!ant->esSBox && box.esSBox)){

            curr = curr = (TCifrado) malloc(sizeof(struct TBox));

            if(curr == NULL){
                perror("Error al crear nuevo nodo");
                exit(1);
            }

            curr->esSBox = box.esSBox;

            if(ant->esSBox && !box.esSBox){
                curr->bitACambiar = box.bitACambiar;
            } else {
                curr->valorASumar = box.valorASumar;
            }
            curr->sig = NULL;

            ant->sig = curr;
            
            *ok = 1;

        }else{

            printf("No se ha podido introducir\n");
            *ok = 0;
        
        }
    } else{
        printf("No se ha podido introducir\n");
        *ok = 0;
    }

}

/* (1.5 puntos) funcion que dado un nodo y un valor, devuelve
 * el resultado de aplicar dicho nodo a dicho valor. Deberas
 * de tener en cuenta si el nodo es una SumaBox o una XORBox.
 * En el ultimo caso, necesitaras usar operadores logicos a
 * nivel de bit, como &, |, ^ o bien ~, asi como probablemente
 * usar constantes  numericas. */
unsigned char aplicarBox (struct TBox box, unsigned char valor){

    unsigned char res = 0;

    if(box.esSBox){
        res = box.valorASumar + valor;
    }else{  
        if (box.bitACambiar == 0) {
            res = valor ^ 0x01;
        } else {
            res = valor ^ 0x80;
        }
    }   
    return res;
}

/* (1.5 puntos) funcion que toma un esquema de cifrado y un valor,
 * y devuelve el resultado de aplicar dicho esquema de cifrado a
 * dicho valor, segun el metodo descrito anteriormente.*/
unsigned char aplicarEsquemaDeCifrado(TCifrado cf, unsigned char valor){
    TCifrado aux = cf;
    unsigned char res = valor;
    while(aux != NULL){
        res = aplicarBox(*aux, res);
        aux = aux->sig;
    }
    return res;
}

/* (2.5 puntos) funcion que toma un nombre de fichero, en el que se
 *  escribiran en modo binario los datos correspondientes al esquema
 *  de cifrado que se pasa como parametro, de modo que el al final el
 *  fichero unicamente contenga dichos datos. Si no se puede abrir el
 *  fichero, se debe de mostrar un mensaje de error por pantalla.*/
void escribirAFichero(char *nm, TCifrado cf){

    FILE * fd = fopen(nm, "wb");
    
    if(fd == NULL){
        perror("Error al abrir el fichero");
        exit(1);
    }
    TCifrado aux = cf;

    while(aux != NULL){
        fwrite(&aux, sizeof(struct TBox), 1, fd);
        aux=aux->sig;
    }
    fclose(fd);

}

/* (1.0 puntos) funcion que destruye un esquema de cifrado y libera la memoria que ocupa*/
void destruirEsquemaDeCifrado (TCifrado *cf){

    if(*cf == NULL){

    } else{
        TCifrado curr, ant;
        curr = (*cf)->sig;
        ant = *cf;

        while(curr != NULL){
            free(ant);
            ant = curr;
            curr = curr->sig;
        }

        free(ant);
        *cf = NULL;
    }

    
}