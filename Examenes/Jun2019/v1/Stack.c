/*
 * Stack.c
 *
 *  Created on: 11 jun. 2019
 *      Author: galvez
 */
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// Creates an empty stack.
T_Stack create()
{
    T_Stack res = NULL;
    return res;
}

// Returns true if the stack is empty and false in other case.
int isEmpty(T_Stack q)
{
    return q == NULL;
}

// Inserts a number into the stack.
void push(T_Stack *pq, int operand)
{
    T_Stack curr, ant;
    curr = *pq;
    ant = NULL;

    while (curr != NULL)
    {
        ant = curr;
        curr = curr->next;
    }

    curr = (T_Stack)malloc(sizeof(struct Node));
    if (curr == NULL)
    {
        perror("Error al crear un nuevo nodo");
        exit(1);
    }
    curr->number = operand;
    curr->next = NULL;

    (*pq == NULL) ? (*pq = curr) : (ant->next = curr);
}

// "Inserts" an operator into the stack and operates.
// Returns true if everything OK or false in other case.
int pushOperator(T_Stack *pq, char operator)
{

    int op1, op2;
    if (pop(pq, &op2) && pop(pq, &op1))
    {
        switch (operator)
        {
        case '+':
            push(pq, op1 + op2);
            break;
        case '-':
            push(pq, op1 - op2);
            break;
        case '*':
            push(pq, op1 * op2);
            break;
        case '/':
            push(pq, op1 / op2);
            break;

        default:
            return 0;
            break;
        }
        return 1;
    } else{
        return 0;
    }
}

// Puts into data the number on top of the stack, and removes the top.
// Returns true if everything OK or false in other case.
int pop(T_Stack *pq, int *data)
{

    T_Stack curr, ant;
    curr = *pq;
    ant = NULL;

    if (*pq == NULL)
    {
        perror("Error lista vacia no se pudo completar el pop");
        return 0;
    }

    while (curr->next != NULL)
    {
        ant = curr;
        curr = curr->next;
    }

    *data = curr->number;

    if (ant == NULL)
    {
        free(curr);
        *pq = NULL;
    }
    else
    {
        free(curr);
        ant->next = NULL;
    }
    return 1;
}

// Frees the memory of a stack and sets it to empty.
void destroy(T_Stack *pq)
{

    T_Stack curr, ant;
    curr = (*pq)->next;
    ant = *pq;

    while(curr != NULL){
        free(ant);
        ant = curr;
        curr->next = curr;
    }
    free(ant);
    *pq = NULL;
}
