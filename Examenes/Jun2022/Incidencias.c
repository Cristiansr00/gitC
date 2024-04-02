/*
 ============================================================================
 Name        : Main2022.c
 Authors     : JB,
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Incidencias.h"

// Contador del número de incidencias, se inicializa a 0.
int contId;
int prioridad(ListaIncidencias *array, int id, int t);

void inicializarListaIncidencias(ListaIncidencias *array, int t){
    for(int i = 0; i < t; i++){
        array[i] = NULL;
    }
    contId=0;
}

// Se inserta una nueva incidencia con la prioridad y descripción dada. Asumimos que no van a insertar una duplicada,
// y que el array tiene longitud para almacenar la prioridad dada. Esta función devuelve el id de la incidencia generada.
//Recuerda que el array ya esta creado en el main.
// 1.75 pts.
int insertarIncidencia(ListaIncidencias *array, int prioridad, char *descripcion){
    
    ListaIncidencias curr = array[prioridad];
    ListaIncidencias ant = NULL;

    while(curr != NULL){
        ant = curr;
        curr = curr->siguiente;
    }

    curr = (ListaIncidencias) malloc(sizeof(Incidencia));

    if(curr == NULL){
        perror("Error al crear un nuevo nodo");
        exit(1);
    }

    curr->id = contId++;
    strcpy(curr->descripcion, descripcion);
    curr->puntuacion = -1;
    curr->siguiente = NULL;

    if(ant == NULL){
        array[prioridad] = curr;
    } else {
        ant->siguiente = curr;
    }

    return curr->id;
}

// Muestra las incidencias por orden de prioridad, primero las más prioritarias. Se debe mostrar la prioridad, su descripción, 
//y su evaluación.
// [Prioridad0 – id0] Descripción1 Sin Evaluar
// [Prioridad0 – id1] Descripción2 Evaluada: 3
// [Prioridad1 – id2] Descripción3 Evaluada: 4
// t es el tamaño del array.
// 1.0 pt.
void mostrarIncidencias(ListaIncidencias *array, int t){
    for(int i = 0; i < t; i++){
        ListaIncidencias curr = array[i];
        while(curr != NULL){
            printf("[Prioridad%d - id%d] %s ",i , curr->id, curr->descripcion);
            if(curr->puntuacion == -1){
                printf("Sin Evaluar\n");
            } else {
                printf("Evaluada: %d\n", curr->puntuacion);
            }
            curr = curr->siguiente;
        }
    }
}

// Libera toda la memoria y deja el array de incidencias vacío. Reinicia contId a 0.
// t es el tamaño del array.
// 1 pt.
void destruirIncidencias(ListaIncidencias *array, int t){

    ListaIncidencias curr, sig;
    for (int i = 0 ; i < t ; i++){
        curr = array[i];
        while(curr != NULL){
            sig = curr->siguiente;
            free(curr);
            curr = sig;
        }
        array[i] = NULL;
    }
    contId = 0;
}

int prioridad(ListaIncidencias *array, int id, int t){

    for(int i = 0; i < t; i++){
        ListaIncidencias curr = array[i];
        while(curr != NULL && curr->id != id){
            curr = curr->siguiente;
        }
        if(curr->id == id){
            return i;
        }
    }

}

// Cambiar prioridad a incidencia existente. Se recomienda hacer una función auxiliar que devuelva la prioridad de una incidencia
//dado su id.
// t es el tamaño del array.
// 1.75 pt.
void cambiarPrioridad(ListaIncidencias *array, int id, int nuevaPrioridad, int t){
    int prio = prioridad(array, id, t);

    ListaIncidencias curr = array[prio];
    ListaIncidencias ant = NULL;

    while(curr != NULL && curr->id != id){
        ant = curr;
        curr = curr->siguiente;
    }

    if(curr->id == id){
        if(ant == NULL){
            array[prio] = curr->siguiente;
        } else {
            ant->siguiente = curr->siguiente;
        }
    }

    curr->siguiente = NULL;

    ListaIncidencias curr2 = array[nuevaPrioridad];
    ListaIncidencias ant2 = NULL;
    
    while(curr2 != NULL){
        ant2 = curr2;
        curr2 = curr2->siguiente;
    }

    if(ant2 == NULL){
        array[nuevaPrioridad] = curr;
    } else {
        ant2->siguiente = curr;
    }
}

// Establecer la evaluación con valor valorEvaluacion a la incidencia con id existente.
// t es el tamaño del array.
// 0.5 pt.
void evaluarIncidencia(ListaIncidencias *array, int id, int valorEvaluacion, int t){

    ListaIncidencias curr;
    for(int i = 0; i < t; i++){
        curr = array[i];
        while(curr != NULL){
            if(curr->id == id){
                curr->puntuacion = valorEvaluacion;
                return;
            }
            curr = curr->siguiente;
        }
    }

}

// Guarda en un fichero de texto los datos de las incidencias almacenadas en la lista de incidencias. El formato del fichero de texto será el siguiente, primero tendrá una cabecera con una descripción de los campos. Tras esta cabecera, una línea por cada incidencia, ordenadas por prioridad primero y luego por antigüedad (las más antiguas primero). En caso de no estar evaluada una incidencia, el campo valor será -1;

// Prioridad;Descripcion;Puntacion;
// 0;Puerta 002 no cierra correctamente;-1;
// 0;Puerta 004 no cierra correctamente;5;
// 9;Puerta 904 no cierra correctamente;100;

// t es el tamaño del array.
// 1.75 pts.
void guardarRegistroIncidencias(char *filename, ListaIncidencias *array, int t){

    FILE * fd = fopen(filename, "wt");
    if(fd == NULL){
        perror("Error al abrir el ficheor");
        exit(1);
    }
    for(int i = 0; i < t ; i++){
        ListaIncidencias curr = array[i];
        while(curr != NULL){
            fprintf(fd,"%d;%s;%d\n",i,curr->descripcion,curr->puntuacion);
            curr = curr->siguiente;
        }
    }
    fclose(fd);
}

// Lee de fichero binario los datos de incidencias y los carga para su uso. El array puede no estar vario, recuerda antes borrar 
//todas las incidencias existentes.
// Cada incidencia es almacenada en el fichero con la siguiente estructura:
//- Un entero con la prioridad de la incidencia.
//- Un entero con el tamaño del campo descripción.
//- La cadena de caracteres con la descripción, incluido el carácter terminador '\0'.
//- Un entero con la puntuación.
// Se asume que las incidencias están guardadas por antigüedad, siendo las primeras las más antiguas.
// t es el tamaño del array.
// 2.0 pts.
void cargarRegistroIncidencias(char *filename, ListaIncidencias *array, int t){

    FILE * fd = fopen(filename, "rb");
    if(fd == NULL){
        perror("Error al abrir el fichero");
        exit(1);
    }

    int prio = 0;
    int tam = 0;
    char *c = NULL; // Allocate memory for c
    int p = 0;
    while(!feof(fd) && fread(&prio, sizeof(int), 1, fd)){
        fread(&tam, sizeof(int), 1, fd);
        c = malloc(tam + 1); // Allocate memory for c
        if(c == NULL){
            perror("Error al asignar memoria");
            exit(1);
        }
        fread(c, sizeof(char), tam + 1, fd); // Read the description
        fread(&p, sizeof(int), 1, fd);
        insertarIncidencia(array, p, c);
        free(c); 
    }
    fclose(fd);
}