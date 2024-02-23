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