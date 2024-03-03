#include <stdio.h>
#include <stdlib.h>
#include "gestion_memoria.h"

void crear(T_Manejador *manejador)
{
    *manejador = (T_Manejador)malloc(sizeof(struct T_Nodo));

    if (manejador != NULL)
    {
        (*manejador)->inicio = 0;
        (*manejador)->fin = 999;
        (*manejador)->sig = NULL;
    }
}

void destruir(T_Manejador *manejador)
{
    T_Manejador aux = (*manejador);
    do
    {
        aux = aux->sig;
        free(*manejador);
        *manejador = aux;
    } while (aux != NULL);
}

void obtener(T_Manejador *manejador, unsigned tam, unsigned *dir, unsigned *ok)
{
    T_Manejador aux, curr;
    curr = *manejador;
    aux = NULL;

    while (curr != NULL && tam > (curr->fin - curr->inicio + 1))
    {
        aux = curr;
        curr = curr->sig;
    }

    if (curr == NULL)
    {
        *ok = 0;
    }
    else
    {
        *ok = 1;
        *dir = curr->inicio;
        // Si el nodo tiene exactamente el mismo tamaño
        if (tam == (curr->fin - curr->inicio + 1))
        {
            // Si está al principio
            if (aux == NULL)
            {
                *manejador = aux->sig;
                free(curr);
            }
            else if (aux->sig == NULL)
            { // Si está al final
                aux->sig = NULL;
                free(curr);
            }
            else
            { // Está en medio
                aux->sig = curr->sig;
                free(curr);
            }
        }
        else
        {
            curr->inicio = curr->inicio + tam;
        }
    }
}

void mostrar(T_Manejador manejador)
{
    T_Manejador aux = manejador;
    printf("Mostrando el contenido...\n");
    while (aux != NULL)
    {
        printf("Nodo: %d - %d;\n", aux->inicio, aux->fin);
        aux = aux->sig;
    }
}

void devolver(T_Manejador *manejador, unsigned tam, unsigned dir)
{
    T_Manejador curr, aux;
    curr = *manejador;
    aux = NULL;

    while (curr != NULL && dir > curr->fin)
    {
        aux = curr;
        curr = curr->sig;
    }

    if (aux == NULL)
    {
        if (dir + tam == curr->inicio)
        { // Es el primero vamos a comprobar si ademas el segundo es consecutivo
            curr->inicio = dir;
        }
        else
        {
            *manejador = (T_Manejador)malloc(sizeof(struct T_Nodo));
            if (manejador != NULL)
            {
                (*manejador)->inicio = dir;
                (*manejador)->fin = dir + tam - 1;
                (*manejador)->sig = curr;
            }
        }
    }
    else if (curr == NULL)
    {
        if (dir - 1 == aux->fin)
        {
            aux->fin = dir + tam - 1;
        }
        else
        {
            T_Manejador nuevo = (T_Manejador)malloc(sizeof(struct T_Nodo));
            if (nuevo != NULL)
            {
                (nuevo)->inicio = dir;
                (nuevo)->fin = dir + tam - 1;
                (nuevo)->sig = NULL;
                aux->sig = nuevo;
            }
        }
    }
    else
    {
        if ((dir + tam == curr->inicio) && (dir - 1 == aux->fin))
        {
            aux->fin = curr->fin;
            aux->sig = curr->sig;
            free(curr);
        }
        else if (dir + tam == curr->inicio)
        { // Es el primero vamos a comprobar si ademas el segundo es consecutivo
            curr->inicio = dir;
        }
        else if (dir - 1 == aux->fin)
        {
            aux->fin = dir + tam - 1;
        }
        else
        {
            T_Manejador nuevo = (T_Manejador)malloc(sizeof(struct T_Nodo));
            if (nuevo != NULL)
            {
                (nuevo)->inicio = dir;
                (nuevo)->fin = dir + tam - 1;
                (nuevo)->sig = curr;
                aux->sig = nuevo;
            }
        }
    }
}