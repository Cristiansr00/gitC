/*
3) Implementar un programa que lea de teclado dos cadenas (o dos palabras) y las compare carácter a carácter. 
Devolverá 1 si las dos cadenas son iguales y 0 en otro caso. [Parámetros por referencia] Cuando las cadenas no 
sean iguales devolverá  la posición del primer carácter en el que difieren, siendo 0 la posición del primer carácter.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

int numero(char *str1, char *str2, int *dif){
    for(int i = 0; i < min(strlen(str1),strlen(str2)); i++ ){
        if(str1[i] != str2[i]){
            *dif = i;
            return 0;
        }
    }
    if(strlen(str1) != strlen(str2)){
        return min(strlen(str1),strlen(str2));
    }
    return 1;
}


int main(int argc, char *argv[]){

    char cad1[20], cad2[20];
    printf("Escriba una cadena de texto para comparar");
    scanf("%s",&cad1);
    printf("Escriba una segunda cadena de texto para comparar");
    scanf("%s",&cad2);
    int difieren;
    int res = numero(cad1,cad2,&difieren);
    if(res){
        printf("Las cadenas son iguales");
    } else {
        printf("Las cadenas difieren en la posición %d",difieren);
    }
    return 0;
}