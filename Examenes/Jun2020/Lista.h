/*
 * Lista.h
 */

#ifndef _LISTA_H_
#define _LISTA_H_

struct TCarta{
	char palo; //'B', 'C', 'E', 'O'
	int valor; //entre 1 y 12
};
typedef struct TCarta TCarta;

typedef struct TNodo *TLista;
struct TNodo{
	TCarta carta;
	TLista sig;
};

/** Crea una lista vacia */
void crear(TLista *lista);

/** Muestra el contenido de la lista.
 *   - Si la lista esta vacia muestra el mensaje "Lista vacia..."
 *   - Si la lista no esta vacia la muestra en el formato:
 *       <valor>:<palo> <valor>:<palo> <valor>:<palo>
 */
void mostrar(TLista lista);

/* Inserta la carta en la lista ordenada primero por el palo y luego,
 * para las cartas del mismo palo, por el valor.
 * En ambos casos en orden ascendente.
 *
 * Podemos suponer que la carta a insertar no esta en la lista.
 */
void insertarOrdenado(TLista *lista, TCarta carta);

/* Elimina toda la memoria dinamica reservada para la lista. */
void destruir(TLista *lista);

//PARTE 2
/* Borra una carta de la lista, teniendo en cuenta que la lista esta ordenada.
 * Se puede suponer que la carta a borrar estara en la lista.
 */
void borrar(TLista *lista, TCarta carta);

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

int descartar(TLista *lista1, TLista *lista2);

/* Suma y devuelve el valor de todas las cartas de la lista,
 * independientemente de su palo.
 */
int sumar(TLista lista);

#endif /* _LISTA_H_ */
