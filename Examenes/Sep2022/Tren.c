/*
 * Examen Septiembre 2022 PSC - todos los grupos.
 * Implementación Tren.c
*/

#include "Tren.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/// @brief Inicializa el tren creado en el Principal que tiene maximoVagones (Vagon *tren) con todos los vagones vacío. 
/// @param tren Array que representa el tren. 
/// @param maximoVagones Número de vagones que tiene el tren (tamaño del array). 
/// 0.25 pts 
void inicializarTren(Vagon * tren, int maximoVagones){
    for(int i = 0; i < maximoVagones; i++){
        tren[i] = NULL;
    }
} 


/// @brief Inserta los datos de un nuevo pasajero. Sí el asiento está libre se lo asigna y si está ocupado ignora la petición. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente, en el que se debe insertar. 
/// @param numeroVagon Vagón en el que se quiere sentar el pasajero. 
/// @param numeroAsiento Asiento dentro del vagón en el que se quiere sentar el pasajero. 
/// @param nombre Nombre del pasajero. 
/// @return Si el asiento ya está ocupado, devuelve -1, si no, devuelve 0. 
/// 1.75 pts 
int entraPasajero(Vagon * tren, unsigned numeroVagon, unsigned numeroAsiento, char * nombre){

    Vagon aux, ant;
    aux = tren[numeroVagon];
    ant = NULL;

    if(aux == NULL || numeroAsiento < aux->num){
        printf("Entra");
        Vagon nuevo = (Vagon) malloc(sizeof(struct Asiento));
        if(nuevo == NULL){
            perror("Error al crear el vagon");
            exit(1);
        }
        nuevo->num = numeroAsiento;
        strcpy(nuevo->nombre, nombre);
        nuevo->sig = aux;

        tren[numeroVagon] = nuevo;

        return 0;

    } else {
        
        while(aux != NULL && numeroAsiento > aux->num){

            ant = aux;
            aux = aux->sig;
        }

        if( aux!= NULL && aux->num == numeroAsiento){
            return -1;
        }

        Vagon nuevo = (Vagon) malloc(sizeof(struct Asiento));
        
        if (nuevo == NULL){
            perror("Errro al crear un nuevo asiento");
            return -1;
        }


        nuevo->num = numeroAsiento;
        strcpy(nuevo->nombre, nombre);
        nuevo->sig = aux;

        ant->sig = nuevo;

        return 0;
    }
} 
 
/// @brief Muestra por pantalla los vagones ocupados mostrando en cada línea los datos de un pasajero. Por ejemplo: 
/* 
Vagon 0:  
Asiento 2, Carlos García 
Asiento 4, Ismael Canario 
Vagon 2: 
Asiento 1, Macarena Sol 
*/ 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param maximoVagones Máximo de vagones que tiene el tren. 
/// 0.75 pt 
void imprimeTren(Vagon * tren, unsigned maximoVagones){
    Vagon curr;

    for(int i = 0; i<maximoVagones; i++){
        printf("Pasajeros del vagon: %d:\n", i);
        curr = tren[i];
        while(curr != NULL){
            printf("Pasajero %d, %s\n", curr->num, curr->nombre);
            curr = curr->sig;
        }
    }
} 
 
/// @brief El pasajero abandona el tren (es eliminado de la estructura).  
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param numeroVagon Vagón en el que se está el pasajero que abandona el tren. 
/// @param numeroAsiento Asiento en el que se está el pasajero que abandona el tren. 
/// @return Devuelve 0 si el pasajero abandona el tren y -1 si no había pasajero en el vagón y asiento indicados. 
/// 1.5 pts 
int salePasajero(Vagon * tren, unsigned numeroVagon, unsigned numeroAsiento){

    Vagon curr = tren[numeroVagon];
    Vagon ant = NULL;
    while( curr != NULL && curr->num < numeroAsiento){
        ant = curr;
        curr = curr->sig;
    }

    if(curr == NULL || curr->num != numeroAsiento){
        printf("El pasajero no se encuentra en el asiento");
        return -1;

    } else {

        if(tren[numeroVagon]->num == curr->num){
            free(curr);
            tren[numeroVagon] = curr->sig;
        } else {
            ant->sig = curr->sig;
            free(curr);
        }   
        return 0;
    }

} 
 
/// @brief Intercambia dos pasajeros. Para ello es suficiente intercambiar el NOMBRE del viajero que está en el asiento \p numeroAsiento1 del vagón\p numeroVagon1, con el del viajero que está en el asiento \p numeroAsiento2 del vagón \p numeroVagon2. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param numeroVagon1 Vagón en el que se está el pasajero 1 que quiere cambiarse de sitio. 
/// @param numeroAsiento1 Asiento en el que se está el pasajero 1 que quiere cambiarse de sitio. 
/// @param numeroVagon2 Vagón en el que se está el pasajero 2 que quiere cambiarse de sitio. 
/// @param numeroAsiento2 Asiento en el que se está el pasajero 2 que quiere cambiarse de sitio. 
/// @return Si algún asiento no está ocupado, devuelve -1. Si se puede realizar el cambio, devuelve 0. 
/// 1.75 pts 
int intercambianAsientos(Vagon * tren, unsigned numeroVagon1, unsigned numeroAsiento1,unsigned numeroVagon2, unsigned numeroAsiento2){

    Vagon as1, as2;
    as1 = tren[numeroVagon1];
    as2 = tren[numeroVagon2];

    if(as1 == NULL || as2 == NULL){
        return -1;
    }

    while(as1 != NULL && as1->num < numeroAsiento1){
        as1 = as1->sig;
    }
    
    if(as1 != NULL && as1->num == numeroAsiento1){


        while(as2 != NULL && as2->num < numeroAsiento2){    

            as2 = as2->sig;
        }

        if(as2 != NULL && as2->num == numeroAsiento2){

            char * aux = malloc(strlen(as1->nombre)+1);

            if(aux == NULL){
                return -1;
            }
            strcpy(aux, as1->nombre);

            strcpy(as1->nombre, as2->nombre);
            strcpy(as2->nombre, aux);
            
            free(aux);

            return 0;
        } else {

            return -1;
        }

    } else {
        return -1;
    }

} 
 
/// @brief El tren llega a la última parada y bajan todos los pasajeros del tren. El tren debe quedar vacío. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param maximoVagones Maximo de vagones que tiene el tren. 
/// 1 pt 
void ultimaParada(Vagon * tren, unsigned maximoVagones){

    for(int i = 0; i < maximoVagones ; i++){
        
        if(tren[i] != NULL){
            Vagon curr, sig;
            curr = tren[i];
            sig = NULL;

            while(curr != NULL){
                sig = curr->sig;
                free(curr);
                curr = sig;
            }
            tren[i] = NULL;
        }
    }
} 
 
/// @brief Guarda en fichero de TEXTO los datos de los pasajeros en el tren. El formato del fichero de texto será el siguiente, una primera línea con el siguiente texto: 
// Vagon;Asiento;Nombre 
// Tras esta línea, incluirá una línea por cada pasajero, ordenados por vagón primero y luego por número de asiento.  
// 0;2;Carmen Garcia 
// 0;3;Pepe Perez 
// 1;5;Adela Gamez 
// 1;7;Josefa Valverde 
/// @param filename Nombre del fichero en el que se van a almacenar los datos de los pasajeros del tren. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param maximoVagones Máximo de vagones que tiene el tren. 
/// 1.5 pts 
void almacenarRegistroPasajeros(char *filename, Vagon * tren, unsigned maximoVagones){

    FILE * fd = fopen(filename, "wt");

    if(fd == NULL){
        perror("Fichero no se ha abierto correctamente");
        exit(1);
    }
    
    fprintf(fd, "Vagon;Asiento;Nombre\n");

    for(int i = 0; i < maximoVagones ; i++){
        if(tren[i] != NULL){
            Vagon curr;
            curr = tren[i];
            while(curr != NULL){
                fprintf(fd, "%d;%d;%s\n", i, curr->num, curr->nombre);
                curr = curr->sig;
            }
        }
    }
    fclose(fd);

}
 
/// @brief Algunas estaciones están automatizadas y proporcionan un fichero con los pasajeros que van a entrar en un vagón en su parada. 
// Esta función carga los pasajeros que están en el fichero BINARIO filename en el  
// vagón numeroVagon. Se asume que los pasajeros almacenados en el fichero no van a  
// sentarse en asientos previamente ocupados.  
// El fichero binario almacena la información de cada pasajero con la siguiente  
// estructura:  
// - Un entero con el número de asiento. 
// - La cadena de caracteres con el nombre. 
/// @param filename Nombre del fichero que contiene los datos de los pasajeros del vagon. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param numeroVagon Vagon del que se van a importar los pasajeros.  
/// 1.5 pts 
void importarPasajerosVagon(char *filename, Vagon * tren,unsigned numeroVagon){

    FILE * fd = fopen(filename, "rb");

    if(fd == NULL){
        perror("No se ha podido abrir el fichero");
        exit(1);
    }

    char * nombre;
    char * nombre2;
    int numeroasiento;

    while(fread(&numeroasiento, sizeof(int), 1, fd) == 1){
        nombre = (char *) malloc(100);
        if(nombre == NULL){
            perror("Error al reservar memoria");
            exit(1);
        }
        fread(nombre, sizeof(char), 100, fd);
        if(nombre2 == NULL){
            perror("Error al reservar memoria");
            exit(1);
        }
        entraPasajero(tren, numeroVagon, numeroasiento, nombre);
        free(nombre);
    }

    fclose(fd);

}

