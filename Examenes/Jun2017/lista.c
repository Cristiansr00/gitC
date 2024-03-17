#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void existe(TLista *lista, struct Punto punto, int *ok);

void crearLista(TLista *lista)
{

    *lista = NULL;
}

void existe(TLista *lista, struct Punto punto, int *ok)
{

    TLista aux = *lista;

    if (*lista == NULL)
    {
        *ok = 0;
    }
    else
    {
        while (aux != NULL && punto.x != aux->punto.x)
        {
            aux = aux->sig;
        }

        if (aux == NULL)
        {
            *ok = 0;
        }
        else
        {
            *ok = 1;
        }
    }
}

/**
 * Inserta el punto de forma ordenada (por el valor de la abscisa x)
 * en la lista siempre que no esté repetida la abscisa.
 *  En ok, se devolverá un 1 si se ha podido insertar, y  0 en caso contrario.
 *  Nota: utiliza una función auxiliar para saber
 *   si ya hay un punto en la lista con la misma abscisa punto.x
 *
 */
void insertarPunto(TLista *lista, struct Punto punto, int *ok)
{

    existe(lista, punto, ok);
    if (*lista == NULL)
    {
        *lista = (TLista)malloc(sizeof(struct Nodo));
        if (*lista == NULL)
        {
            perror("Error al crear el nodo");
            exit(1);
        }

        (*lista)->sig = NULL;
        (*lista)->punto.x = punto.x;
        (*lista)->punto.y = punto.y;
        *ok = 1;
    }
    else
    {
        if (!*ok)
        {
            TLista curr, ant;
            curr = *lista;
            ant = NULL;

            while (curr != NULL && punto.x > curr->punto.x)
            {

                ant = curr;
                curr = curr->sig;
            }

            if (curr == NULL)
            {
                curr = (TLista)malloc(sizeof(struct Nodo));
                if (curr == NULL)
                {
                    perror("Error al crear el nuevo nodo");
                    *ok = 0;
                }

                curr->punto.x = punto.x;
                curr->punto.y = punto.y;

                curr->sig = NULL;
                ant->sig = curr;
                *ok = 1;
            }
            else if (ant == NULL)
            {
                ant = (TLista)malloc(sizeof(struct Nodo));
                if (ant == NULL)
                {
                    perror("Error al crear el nuevo nodo");
                    *ok = 0;
                }

                ant->punto.x = punto.x;
                ant->punto.y = punto.y;

                ant->sig = curr;
                *lista = ant;
                *ok = 1;
            }
            else
            {
                curr = (TLista)malloc(sizeof(struct Nodo));
                if (curr == NULL)
                {
                    perror("Error al crear el nuevo nodo");
                    *ok = 0;
                }

                curr->punto.x = punto.x;
                curr->punto.y = punto.y;

                curr->sig = ant->sig;
                ant->sig = curr;
                *ok = 1;
            }
        }
    }
}

/*
 * Elimina de la lista el punto con abscisa x de la lista.
 * En ok devolverá un 1 si se ha podido eliminar,
 * y un 0 si no hay ningún punto en la lista con abscisa x
 *
 */
void eliminarPunto(TLista *lista, float x, int *ok)
{
    struct Punto punto;
    punto.x = x;
    punto.y = 0;

    existe(lista, punto, ok);

    if (*ok)
    {
        TLista curr, ant;
        curr = *lista;
        ant = NULL;

        while (curr->punto.x != punto.x)
        {
            ant = curr;
            curr = curr->sig;
        }

        if (ant == NULL)
        {
            *lista = curr->sig;
            free(curr);
            *ok = 1;
        }
        else
        {
            ant->sig = curr->sig;
            free(curr);
            *ok = 1;
        }
    }
}

/**
 * Muestra en pantalla el listado de puntos
 */
void mostrarLista(TLista lista)
{
    TLista curr = lista;

    if (curr == NULL)
    {
        perror("La lista está vacia");
        exit(1);
    }

    printf("Lista de puntos:\n");

    while (curr != NULL)
    {
        printf("x:%.2f y:%.2f \n", curr->punto.x, curr->punto.y);
        curr = curr->sig;
    }
}

/**
 * Destruye la lista de puntos, liberando todos los nodos de la memoria.
 */
void destruir(TLista *lista)
{
    TLista curr, ant;
    ant = *lista;
    curr = ant->sig;

    while (curr != NULL)
    {
        free(ant);
        ant = curr;
        curr = curr->sig;
    }

    free(ant);
    *lista = NULL;
}

/*
 * Lee el contenido del archivo binario de nombre nFichero,
 * que contiene una secuencia de puntos de una función polinómica,
 *  y lo inserta en la lista.
 *
 */
void leePuntos(TLista *lista, char *nFichero)
{

    FILE *fd = fopen(nFichero,"rb");

    if (fd == NULL)
    {
        perror("Errror al crear el puntero");
        exit(1);
    }

    float num[2] = {0, 0};
    crearLista(lista);
    while (!feof(fd) && fread(&num, sizeof(float) * 2, 1, fd))
    {
        
        struct Punto punto;
        punto.x = num[0];
        punto.y = num[1];
        int ok;
        insertarPunto(lista, punto, &ok);
        if (ok)
        {
            printf("Insertadox:%.2f y:%.2f \n", punto.x, punto.y);
        }
    }

    fclose(fd);
}