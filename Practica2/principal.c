#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "arbolbb.h"

void crearFicheroAleatorios(char *nombreFich, int TAM)
{
	FILE *fd = fopen(nombreFich, "wb");
	
	if (fd == NULL){
		perror("Error al abrir el fichero en modo escritura");
		exit(1);
	}
	int random = 0;

	srand (time(NULL));

	for (int i = 0; i < TAM; i++){
		random = rand()%TAM;
		fwrite(&random,sizeof(random),1,fd);
	}
	fclose(fd);
}

void mostrarFicheroAleatorios(char *nombreFich)
{
	FILE *fd = fopen(nombreFich, "rb");

	if(fd == NULL){
		perror("Error al abrir la escritura del fichero");
		exit(1);
	}
	
	int numero = 0;
	while(!feof(fd) && fread(&numero, sizeof(numero), 1, fd)){
		printf("%d ",numero);
	}

	fclose(fd);
}

void cargaFichero(char* nfichero, T_Arbol* miarbol)
{
	FILE *fd = fopen(nfichero,"rb");
	
	if(fd == NULL){
		perror("Error al abrir el fichero y cargarlo");
		exit(1);
	}
	int num = 0;
	while(!feof(fd) && fread(&num,sizeof(num),1,fd)){
		insertar(miarbol,num);
	}

}

int main(int argc, char **argv)
{
	int TAM;
	char nombreFich[30];

	setvbuf(stdout, NULL, _IONBF, 0);
	printf("Introduzca nombre fichero:\n");
	scanf("%s", nombreFich);

	printf("Introduzca tamaño:\n");
	scanf("%d", &TAM);

	crearFicheroAleatorios(nombreFich, TAM);
	mostrarFicheroAleatorios(nombreFich);

	printf ("\n Ahora lo cargamos en el arbol\n");
	T_Arbol miarbol;
	crear (&miarbol);
	cargaFichero(nombreFich,&miarbol);
	printf ("\n Y lo mostramos ordenado\n");
	mostrar(miarbol);

	printf("\n Ahora lo guardamos ordenado\n");
	FILE * fich;
	fich = fopen (nombreFich, "wb");
	if(fich==NULL){
		perror("main: error al abrir el fichero en modo wb");
	}else{
		salvar (miarbol, fich);
		fclose (fich);
		printf("\n Y lo mostramos ordenado\n");
		mostrarFicheroAleatorios(nombreFich);
	}
	destruir (&miarbol);

}













































