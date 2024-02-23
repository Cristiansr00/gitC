/*1) Implementar la función int esPrimo(int n) que dado un entero n devuelve
1 si es primo y 0 en otro caso. Implementa un método main que pida al usuario un número,
le pase como argumento ese número a la función esPrimo,
y muestre por pantalla una frase indicado si el número es o no primo.*/

#include <stdio.h>
#include <math.h>

#define true 1
#define false 0

int esPrimo(int n){
    if (n <= 1){
        return true;
    } else {
        for(int i = 2; i < n ; i++){
            if(n%i == 0){
                return false;
            }
        }
        return true;
    }
}

int main( int argc, char *argv[] )  {
    int numero;

    printf("Introduce un numero para comprobar si es primo:\n");
    scanf("%d", &numero);
    if(esPrimo(numero)) printf("El numero es primo\n"); else printf("El numero no es primo\n");
    fflush(stdout);
   return 0;
}