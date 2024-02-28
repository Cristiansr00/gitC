/*
4) Implementar un calculadora simple que realice las operaciones de suma (+), resta (-), 
multiplicación (*) y división (/) de dos números enteros y muestre por pantalla el resultado. 
El programa debe dar la opción de hacer un cálculo (el usuario introduce 'c') o terminar (usuario introduce el carácter 'q').  
El usuario introducirá por teclado la expresión en notación infija, es decir <operando 1> <Operador> <operando 2> 
(puede leer elemento a elemento o los 3 a la vez).
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int result(char *operacion, int a, int b){
    if(strcmp("+",operacion) == 0){
        return a + b;
    } else if(strcmp("-",operacion) == 0){
        return a - b;
    } else if(strcmp("*",operacion) == 0){
        return a * b;
    } else if(strcmp("/",operacion) == 0){
        return a / b;
    }
}



int main(int argc, char *argv[]){

    char caracter;
    printf("Introduzca 'c' para realizar una operación o 'q' para salir\n");
    scanf("%c",&caracter);
    while(caracter != 'q' && caracter == 'c'){
        int operando1;
        char operacion[10];
        int operando2;
        
        printf("Introduzca el primer operando\n");
        scanf("%d",&operando1);
        printf("Introduzca la operación\n");
        scanf("%s",operacion);
        printf("Introduzca el segundo operando\n");
        scanf("%d",&operando2);

        int resultado = result(operacion, operando1 ,operando2);
        printf("El resultado de la operación es %d;\n",resultado);

        printf("Introduzca 'c' para realizar una operación o 'q' para salir\n");
        scanf(" %c",&caracter);
    }
    return 0;
}