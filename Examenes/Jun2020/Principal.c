/*
 ============================================================================
 Name        : Principal.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

/* PARTE 3
 * Dado un fichero f, ya abierto en modo texto, lee una linea de ese fichero
 * y guarda las cartas en la lista que se pasa como parametro.
 *
 * El formato de cada linea es: <num_cartas> <carta1> <carta2> ... <cartan>
 *
 * donde el primer valor es el numero de cartas que se almacenaran en la lista.
 * Este valor no se almacena en la lista.
 *
 * Cada carta se representa por el valor de la carta, un espacio y
 * la letra B, C, E o O, representando el palo.
 *
 * Ejemplo de linea con 5 cartas:      5 2 C 1 E 1 O 6 B 4 B
 *
 * Para el ejemplo, se crearia una lista con las cartas 2:C 1:E 1:O 6:B y 4:B
 *
 * Debe suponerse que la lista se ha creado previamente. Los datos se guardaran en lista
 * de forma ordenada, primero por el palo y luego, para el mismo palo, por el valor.
 * En los dos casos en orden ascendente.
 */
void leerLinea(FILE *f, TLista *lista){

	int num_cartas;
	fscanf(f,"%d",&num_cartas);

	TCarta carta;
	for (int i = 0; i < num_cartas; i++){
		fscanf(f,"%d %c ",&carta.valor,&carta.palo);
		insertarOrdenado(lista,carta);
	}

}

/* PARTE 3
 * Dado el nombre de un fichero de texto que contiene tres lineas, cada una
 * con el formato descrito anteriormente:  <num_cartas> <carta1> <carta2> ... <cartan>
 *
 * Leer la informacion del fichero y generar tres listas de cartas del siguiente modo:
 * El contenido de la primera linea se almacena en mazo, el de la segunda en
 * jugador1 y el de la tercera en jugador2.
 *
 * Debe suponerse que las listas se han creado previamente. Las cartas se almacenaran
 * en las listas correspondientes de forma ordenada, primero por el palo y luego,
 * para el mismo palo, por el valor.
 */
void crearDesdeFichero(char *nombre, TLista *mazo, TLista *jugador1, TLista *jugador2){

	FILE *f = fopen(nombre,"r");
	if (f == NULL){
		printf("Error al abrir el fichero\n");
		exit(1);
	}

	leerLinea(f,mazo);
	leerLinea(f,jugador1);
	leerLinea(f,jugador2);

	fclose(f);

}

int main(void) {
	setvbuf(stdout,NULL,_IONBF,0);
	TLista mazo, jugador1, jugador2;

	//Crea las listas mazo, jugador1 y jugador2
	crear(&mazo);
	crear(&jugador1);
	crear(&jugador2);

	//Creamos el mazo con las cartas 3:O 1:O 2:O 4:O 4:B 3:C 6:B 3:E 2:C 1:E 1:C 10:O*/
	//PARTE 1 y PARTE 2 - Comentar lo siguiente para probar Parte 3
	// TCarta carta;

	// carta.palo = 'O';
	// carta.valor = 3;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'O';
	// carta.valor = 1;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'O';
	// carta.valor = 2;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'O';
	// carta.valor = 4;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'B';
	// carta.valor = 4;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'C';
	// carta.valor = 3;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'B';
	// carta.valor = 6;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'E';
	// carta.valor = 3;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'C';
	// carta.valor = 2;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'E';
	// carta.valor = 1;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'C';
	// carta.valor = 1;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'O';
	// carta.valor = 10;
	// insertarOrdenado(&mazo,carta);

	// carta.palo = 'B';
	// carta.valor = 1;
	// insertarOrdenado(&jugador1,carta);

	// carta.palo = 'B';
	// carta.valor = 3;
	// insertarOrdenado(&jugador1,carta);

	// carta.palo = 'C';
	// carta.valor = 4;
	// insertarOrdenado(&jugador1,carta);

	// carta.palo = 'E';
	// carta.valor = 5;
	// insertarOrdenado(&jugador1,carta);

	// carta.palo = 'O';
	// carta.valor = 5;
	// insertarOrdenado(&jugador2,carta);

	// carta.palo = 'E';
	// carta.valor = 4;
	// insertarOrdenado(&jugador2,carta);

	// carta.palo = 'O';
	// carta.valor = 8;
	// insertarOrdenado(&jugador2,carta);

	// carta.palo = 'O';
	// carta.valor = 12;
	// insertarOrdenado(&jugador2,carta);
	//FIN PARTE 1 Y PARTE 2 - Comentar hasta aqui para probar Parte 3

	/* PARTE 3 - Carga los datos desde fichero*/
	crearDesdeFichero("cartas.txt", &mazo, &jugador1, &jugador2);

	//Muestra los datos cargados
	printf("Mazo Inicial: ");
	mostrar(mazo);
	printf("Jugador 1: ");
	mostrar(jugador1);
	printf("Jugador 2: ");
	mostrar(jugador2);
	printf("\n");

	//PARTE 2
	
	int d1,d2;

	printf("---------------------------------------------------\n");
	printf("Los jugadores empiezan a descartarse cartas:\n\n");
	do{
		d1 = descartar(&mazo,&jugador1);
		if (d1 > 0) {
			printf("Jugador 1 descarta una carta. Le quedan por descartar: ");
			mostrar(jugador1);
		}
		d2 = descartar(&mazo,&jugador2);
		if (d2 > 0) {
			printf("Jugador 2 descarta una carta. Le quedan por descartar: ");
			mostrar(jugador2);
		}
	}while(d1 > 0 || d2 >0);
	printf("\nLos jugadores ya no pueden descartarse mas cartas\n");
	printf("---------------------------------------------------\n\n");

	printf("Mazo despu�s de descartar: ");
	mostrar(mazo);
	printf("Jugador 1 despues de descartar todas las cartas posibles: ");
	mostrar(jugador1);
	printf("Jugador 2 despues de descartar todas las cartas posibles: ");
	mostrar(jugador2);

	int suma1 = sumar(jugador1);
	int suma2 = sumar(jugador2);

	if (suma1 < suma2){
		printf("Jugador 1 gana");
	}else if (suma2 < suma1){
		printf("Jugador 2 gana");
	}else{
		printf("Empate");
	}

	destruir(&mazo);
	destruir(&jugador1);
	destruir(&jugador2);

	return 0;
}

/* Salida Parte 1:
Mazo Inicial: 4:B 6:B 1:C 2:C 3:C 1:E 3:E 1:O 2:O 3:O 4:O 10:O
Jugador 1: 1:B 3:B 4:C 5:E
Jugador 2: 4:E 5:O 8:O 12:O
*/

/* Salida Partes 2 y 3.
Mazo Inicial: 4:B 6:B 1:C 2:C 3:C 1:E 3:E 1:O 2:O 3:O 4:O 10:O
Jugador 1: 1:B 3:B 4:C 5:E
Jugador 2: 4:E 5:O 8:O 12:O

---------------------------------------------------
Los jugadores empiezan a descartarse cartas:

Jugador 1 descarta una carta. Le quedan por descartar: 1:B 4:C 5:E
Jugador 2 descarta una carta. Le quedan por descartar: 5:O 8:O 12:O
Jugador 1 descarta una carta. Le quedan por descartar: 1:B 5:E
Jugador 2 descarta una carta. Le quedan por descartar: 8:O 12:O
Jugador 1 descarta una carta. Le quedan por descartar: 1:B

Los jugadores ya no pueden descartarse mas cartas
---------------------------------------------------

Mazo despu�s de descartar: 3:B 4:B 6:B 1:C 2:C 3:C 4:C 1:E 3:E 4:E 5:E 1:O 2:O 3:O 4:O 5:O 10:O
Jugador 1 despues de descartar todas las cartas posibles: 1:B
Jugador 2 despues de descartar todas las cartas posibles: 8:O 12:O
Jugador 1 gana
*/
