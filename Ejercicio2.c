/*
2) Implementar un programa que lea de teclado una cadena terminada en el carácter '#' y 
devuelva el número de apariciones de cada una de las vocales. 
Para usar scanf hay que leer carácter a carácter porque no se sabe la longitud de la cadena.
*/

#include <stdio.h>


int main(int argc, char *argv[]){
    char caracter;
    int a=0, e=0, i=0, o=0, u=0;
    printf("Introduzca una palabra finalice con #\n");
    scanf("%c",&caracter);
    while (caracter != '#'){

        switch(caracter){

            case 'a':
                a++;
                break;
            
            case 'e':
                e++;
                break;

            case 'i':
                i++;
                break;

            case 'o':
                o++;
                break;

            case 'u':
                u++;
                break;

            default:
                break;
        }
        scanf("%c",&caracter);
    }

    printf("El numero de a = %d\n",a);
    printf("El numero de e = %d\n",e);
    printf("El numero de i = %d\n",i);
    printf("El numero de o = %d\n",o);
    printf("El numero de u = %d\n",u);



    return 0;
}